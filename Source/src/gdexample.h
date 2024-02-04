#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/node.hpp>
#include <string>

namespace godot {
    /**
    *    FFMpeg_Comp class integrates FFMpeg with Godot for video processing.
    *    It inherits from Godot's Node class that provides ability to have this component as Godot element in the scene
    */
    class FFMpeg_Comp : public Node {
        GDCLASS(FFMpeg_Comp, Node)

    private:
        // Holds the status message of the last operation
        String Status = "Empty";
        
        // Stores YUV color values of specific pixel.
        Vector3 YUV_values;
        
        // Dimensions of the video frame
        int width, height;

        // Array to store RGB values of a specific row
        unsigned char* rgbRow;

        // Array to store RGB values of a specific column
        unsigned char* rgbColumn;

    protected:
        /*
         *    Method to bind methods for use in GDScript
        */
        static void _bind_methods();

    public:
        // Constructor
        FFMpeg_Comp();

        // Destructor
        ~FFMpeg_Comp();

        /*
         *    Helper method to clamp integer values 
         *    @value:    value to clamp
         *    @return:   clamped value to the range [0, 255]
        */
        void _process(double delta) override;

        /*
         *    Method to fetch RGB and YUV values of a pixel at a specific location in a frame. It selects a frame
         *    @path_video_file:    video file path with video name in it
         *    @frameNumber:        selected frame number
         *    @x:                  horizontal location in frame
         *    @y:                  vertical location in frame
         *    @return:             Vector3 of RGB value at a specific location
        */
        Vector3 get_RGB_values(const godot::String path_video_file, int frameNumber, int x, int y);

        /*
         *    Method to get YUV values of a specific pixel selected by get_RGB_values method
         *    @return:   YUV values
        */
        Vector3 get_YUV_values();

        /*
         *    Method to get all pixels in a specific line as RGB values 
         *    @bool:     normalize values [0-1], by default [0-255]
         *    @return:   pixel array
        */        
        godot::Array get_line_pixels_as_RGB(bool normalized = false);

        /*
         *    Method to get all pixels in a specific column as RGB values 
         *    @bool:     normalize values [0-1], by default [0-255]
         *    @return:   pixel array
        */    
        godot::Array get_column_pixels_as_RGB(bool normalized = false);


		
    private:
        /*
         *    Initializes FFMpeg library for processing
        */
        void initLibVLC();

        /*
         *    Helper method to clamp integer values 
         *    @value:    value to clamp
         *    @return:   clamped value to the range [0, 255]
        */
		int clamp(int value);
        
    
    };
} // namespace godot

#endif // GDEXAMPLE_H
