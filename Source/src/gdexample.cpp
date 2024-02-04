#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <iostream>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/pixdesc.h> // For av_get_pix_fmt_name
}

using namespace godot;
// Bind Godot methods for use in GDScript
void FFMpeg_Comp::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_RGB_values", "path_video_file", "frameNumber", "x", "y"), &FFMpeg_Comp::get_RGB_values);
    ClassDB::bind_method(D_METHOD("get_YUV_values"), &FFMpeg_Comp::get_YUV_values);
    ClassDB::bind_method(D_METHOD("get_column_pixels_as_RGB", "normalized"), &FFMpeg_Comp::get_column_pixels_as_RGB);
    ClassDB::bind_method(D_METHOD("get_line_pixels_as_RGB", "normalized"), &FFMpeg_Comp::get_line_pixels_as_RGB);
    
}

FFMpeg_Comp::FFMpeg_Comp() {
    // Constructor
}

FFMpeg_Comp::~FFMpeg_Comp() {
    // Destructor - Cleanup allocated resources
    delete[] rgbRow; // freeing rgbRow after use to avoid memory leaks
    delete[] rgbColumn;
}

void FFMpeg_Comp::initLibVLC(){
    // Initialize any libraries here (currently placeholder)
}

void FFMpeg_Comp::_process(double delta) {
    // Process method for repeated actions (placeholder)
}

// Returns the stored YUV values of a specific pixel
Vector3 FFMpeg_Comp::get_YUV_values(){
    // YUV values set by get_RGB_values method
    return YUV_values;
}

// Fetches all pixels in a specific line as RGB values
godot::Array FFMpeg_Comp::get_line_pixels_as_RGB(bool normalized)
{
    godot::Array vectorArray;
    godot::Vector3 rgbVector;

    // Iterates over height to get RGB values for each pixel in the column
    for (int i = 0; i < width; ++i) {
        // Calculate the index in the rgbRow array
        int index = i * 3;

        // Extract RGB values
        float r = static_cast<float>(rgbRow[index]);
        float g = static_cast<float>(rgbRow[index + 1]);
        float b = static_cast<float>(rgbRow[index + 2]);
        

        godot::Vector3 rgbVector(r / 255.0f, g / 255.0f, b / 255.0f);
        

        // Add the Vector3 to the array
        vectorArray.push_back(rgbVector);
    }

    // Ensure you free the allocated memory for rgbRow when it's no longer needed
    // delete[] rgbRow;

    return vectorArray;
}

// Extracts RGB values from a specific frame and pixel position
godot::Array FFMpeg_Comp::get_column_pixels_as_RGB(bool normalized)
{
    godot::Array vectorArray;
    godot::Vector3 rgbVector;
    for (int i = 0; i < height; ++i) {
        // Calculate the index in the rgbColumn array
        int index = i * 3;

        // Extract RGB values
        float r = static_cast<float>(rgbColumn[index]);
        float g = static_cast<float>(rgbColumn[index + 1]);
        float b = static_cast<float>(rgbColumn[index + 2]);
        
        godot::Vector3 rgbVector(r / 255.0f, g / 255.0f, b / 255.0f);

        // Add the Vector3 to the array
        vectorArray.push_back(rgbVector);
    }

    return vectorArray;
}


Vector3 FFMpeg_Comp::get_RGB_values(const godot::String path_video_file, int frameNumber, int x, int y) {

    CharString path = path_video_file.utf8();
    const char* filePath = path.get_data();
    
    // Open Input file and allocate format context
    AVFormatContext* pFormatContext = avformat_alloc_context();
    if (avformat_open_input(&pFormatContext, filePath, NULL, NULL) != 0) {
        Status="ERROR: Could not open video file.";
        return godot::Vector3(0,0,0);
    }

    // Retrieve stream information
    if (avformat_find_stream_info(pFormatContext, NULL) < 0) {
        Status="ERROR: Could not get stream info.";
        return godot::Vector3(0,0,0);
    }

    AVCodecParameters* pCodecParameters = nullptr;
    int videoStreamIndex = -1;

    // Find the first video stream
    for (unsigned int i = 0; i < pFormatContext->nb_streams; i++) {
        AVCodecParameters* pLocalCodecParameters = pFormatContext->streams[i]->codecpar;
        const AVCodec* pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

        if (pLocalCodec == nullptr) {
            Status="ERROR: Unsupported codec!";
            continue;
        }

        if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            pCodecParameters = pLocalCodecParameters;
            break;
        }
    }

    if (videoStreamIndex == -1) {
        Status="ERROR: File does not contain a video stream!";
        return godot::Vector3(0,0,0);
    }

    const AVCodec* pCodec = avcodec_find_decoder(pCodecParameters->codec_id);
    AVCodecContext* pCodecContext = avcodec_alloc_context3(pCodec);
    avcodec_parameters_to_context(pCodecContext, pCodecParameters);

    if (avcodec_open2(pCodecContext, pCodec, NULL) < 0) {
        Status= "ERROR: Could not open codec.";
        return godot::Vector3(0,0,0);
    }

    AVFrame* pFrame = av_frame_alloc();
    AVPacket* pPacket = av_packet_alloc();

    int currentFrameNumber = 0; // Initialize frame number
    bool frameFound = false;
    godot::Vector3 rgb(0, 0, 0);
    av_seek_frame(pFormatContext, videoStreamIndex, frameNumber, AVSEEK_FLAG_FRAME);

    // Read frames
    while (av_read_frame(pFormatContext, pPacket) >= 0 && !frameFound) {
        if (pPacket->stream_index == videoStreamIndex) {
            if (avcodec_send_packet(pCodecContext, pPacket) == 0) {
                while (avcodec_receive_frame(pCodecContext, pFrame) == 0) {
                    currentFrameNumber++;
                    if (currentFrameNumber == frameNumber) {
                        
                        // Y component
                        const unsigned char yComponent = pFrame->data[0][pFrame->linesize[0]*y + x];

                        // U, V components 
                        x /= 2;
                        y /= 2;
                        const unsigned char u = pFrame->data[1][pFrame->linesize[1]*y + x];
                        const unsigned char v = pFrame->data[2][pFrame->linesize[2]*y + x];

                        YUV_values = godot::Vector3(yComponent,u, v);
                        
                        // RGB conversion
                        const unsigned char r = yComponent + 1.402*(v-128);
                        const unsigned char g = yComponent - 0.344*(u-128) - 0.714*(v-128);
                        const unsigned char b = yComponent + 1.772*(u-128);
                        
                        rgb = godot::Vector3(r, g, b);
                        frameFound = true;
                        break;


                        
						
                    }
                }
            }
        }
        av_packet_unref(pPacket);
    }

    // Fetch RGB line
    // Assuming y is the row you're interested in, and it is already defined in your code
    width = pFrame->width; // Get the width of the frame to iterate over all x coordinates

    // Allocate memory for RGB row (3 components per pixel)
    rgbRow = new unsigned char[width * 3];

    for (int x = 0; x < width; x++) {
        // Y component
        const unsigned char yComponent = pFrame->data[0][pFrame->linesize[0] * y + x];

        // For U, V components, considering chroma subsampling, x and y might need to be divided by 2
        int chromaX = x / 2;
        int chromaY = y / 2;
        const unsigned char u = pFrame->data[1][pFrame->linesize[1] * chromaY + chromaX];
        const unsigned char v = pFrame->data[2][pFrame->linesize[2] * chromaY + chromaX];

        // RGB conversion
        int r = yComponent + 1.402 * (v - 128);
        int g = yComponent - 0.344 * (u - 128) - 0.714 * (v - 128);
        int b = yComponent + 1.772 * (u - 128);

        // Clamping to 0 - 255
        r = r > 255 ? 255 : r < 0 ? 0 : r;
        g = g > 255 ? 255 : g < 0 ? 0 : g;
        b = b > 255 ? 255 : b < 0 ? 0 : b;

        // Store the RGB values in the rgbRow array
        rgbRow[x * 3 + 0] = (unsigned char)r;
        rgbRow[x * 3 + 1] = (unsigned char)g;
        rgbRow[x * 3 + 2] = (unsigned char)b;
    }

    // Now, rgbRow contains the RGB values for the entire row y of the frame.

    // Assuming x is the column you're interested in
    height = pFrame->height; // Get the height of the frame to iterate over all y coordinates

    // Allocate memory for RGB column (3 components per pixel, for each pixel in the column)
    rgbColumn = new unsigned char[height * 3];

    for (int y = 0; y < height; y++) {
        // Y component
        const unsigned char yComponent = pFrame->data[0][pFrame->linesize[0] * y + x];

        // Considering chroma subsampling, x and y might need to be divided by 2 for U, V components
        int chromaX = x / 2;
        int chromaY = y / 2;
        const unsigned char u = pFrame->data[1][pFrame->linesize[1] * chromaY + chromaX];
        const unsigned char v = pFrame->data[2][pFrame->linesize[2] * chromaY + chromaX];

        // RGB conversion
        int r = yComponent + 1.402 * (v - 128);
        int g = yComponent - 0.344 * (u - 128) - 0.714 * (v - 128);
        int b = yComponent + 1.772 * (u - 128);

        // Clamping to 0 - 255
        r = r > 255 ? 255 : r < 0 ? 0 : r;
        g = g > 255 ? 255 : g < 0 ? 0 : g;
        b = b > 255 ? 255 : b < 0 ? 0 : b;

        // Store the RGB values in the rgbColumn array
        int index = y * 3; // Calculate the index in the rgbColumn array
        rgbColumn[index + 0] = (unsigned char)r;
        rgbColumn[index + 1] = (unsigned char)g;
        rgbColumn[index + 2] = (unsigned char)b;
    }

    // Now, rgbColumn contains the RGB values for the entire column x of the frame.

    

    
    // Clean up
    av_frame_free(&pFrame);
    av_packet_free(&pPacket);
    avcodec_free_context(&pCodecContext);
    avformat_close_input(&pFormatContext);

    return rgb;
}

int FFMpeg_Comp::clamp(int value) {
    return std::max(0, std::min(value, 255));
}