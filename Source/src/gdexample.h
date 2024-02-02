#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/node.hpp>
#include <string>

namespace godot {

    class FFMpeg_Comp : public Node {
        GDCLASS(FFMpeg_Comp, Node)

    private:
        godot::String Status = "Empty";

        godot::Vector3 YUV_values;

        int width;
        unsigned char* rgbRow;

        int height;
        unsigned char* rgbColumn;

    protected:
        static void _bind_methods();

    public:
        FFMpeg_Comp();
        ~FFMpeg_Comp();

        void _process(double delta) override;

        Vector3 get_RGB_values(const godot::String path_video_file, int frameNumber, int x, int y);

        Vector3 get_YUV_values();
        
        godot::Array get_line_pixels_as_RGB(bool normalized = false);
        
        godot::Array get_column_pixels_as_RGB(bool normalized = false);


		
    private:
        void initLibVLC();
		int clamp(int value);
        
    
};
} // namespace godot

#endif // GDEXAMPLE_H
