// Guard to prevent multiple inclusions of the header
#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

// Include Godot Node class header for creating custom nodes
#include <godot_cpp/classes/node.hpp> 

// Include OpenCV library for image processing
#include <opencv2/opencv.hpp>

#include <vlc.hpp>

namespace godot {

	class VLC_Api : public Node {

	// Godot Macro
	GDCLASS(VLC_Api, Node)

	private:
		double time_passed;
		double speed;
		String status;

	protected:
		// Function to bind methods and properties for Godot's scripting API
		static void _bind_methods();

	public:
		VLC_Api();
		~VLC_Api();

		// The same as Godot process
		void _process(double delta) override;

		// Helper functions
		bool is_file_exists(std::string filename_with_path);

		void set_speed(const double p_speed);
		double get_speed() const;
		String get_status() const;

		Vector3 get_RGB_values(const godot::String path_video_file, int frameNumber, int x, int y);

		Vector3 convert_Vec3b_to_Vector3(const cv::Vec3b& vec);

	};

}

#endif