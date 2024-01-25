#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>

#include <iostream>

using namespace godot;
using namespace cv;

void VLC_Api::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_speed"), &VLC_Api::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &VLC_Api::set_speed);
	ClassDB::bind_method(D_METHOD("get_RGB_values"), &VLC_Api::get_RGB_values);

	ClassDB::bind_method(D_METHOD("get_status"), &VLC_Api::get_status);

	ClassDB::add_property("VLC_Api", PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_speed", "get_speed");
}

VLC_Api::VLC_Api() {
	time_passed = 0.0;
	status = "Status: idle";
}

VLC_Api::~VLC_Api() {
	// Add cleanup here.
}

void VLC_Api::_process(double delta) {
}

void VLC_Api::set_speed(const double p_speed) {
	speed = p_speed;
}

double VLC_Api::get_speed() const {
	return speed + 100;
}

godot::String VLC_Api::get_status() const{
	return status;
}

Vector3 convertVec3bToVector3(const cv::Vec3b& vec) {
	// Assuming vec is in BGR format and you want RGB in godot::Vector3
	float r = vec[2] / 255.0f; // Red channel
	float g = vec[1] / 255.0f; // Green channel
	float b = vec[0] / 255.0f; // Blue channel

	return godot::Vector3(r, g, b);
}

bool is_file_exists(std::string filename_with_path){
	struct stat buffer;
	// c_str() to convert std::string to const char*
	return (stat(filename_with_path.c_str(), &buffer) != 0);
}

Vector3 VLC_Api::get_RGB_values(const godot::String path_video_file, int frameNumber, int x, int y) {
	// Convert godot::String to std::string
	godot::CharString charString = path_video_file.utf8();
	std::string stdStringPath = charString.get_data();


	// Convert std::string to cv::String
	//cv::String cvString = stdString;

	// Initialize the VideoCapture object with the video file path
	cv::VideoCapture cap("C:/Projects/GoDotProjects/godot-cpp-template/demo/VideoTest.mp4");
	cap.open("C:/Projects/GoDotProjects/godot-cpp-template/demo/VideoTest.mp4");
	
	// Check if the video file has been opened successfully
	if (!cap.isOpened()) {
		status = "Error opening video file";
		return Vector3();
	}else
	status = "Is Opened";

	cap.set(cv::CAP_PROP_POS_FRAMES, frameNumber);

	cv::Mat frame;
	if (!cap.read(frame)) {
		//status = "Unable to read the frame.";
		return convertVec3bToVector3(cv::Vec3b());
		//return cv::Vec3b();
	}

	// Check if coordinates are within the frame dimensions
	if (x >= 0 && x < frame.cols && y >= 0 && y < frame.rows) {
		return convertVec3bToVector3(frame.at<cv::Vec3b>(y, x));
	} else {
		status = "Coordinates are out of bounds.";
		return convertVec3bToVector3(cv::Vec3b());
	}

	return Vector3(1.0,2.0,3.0);
}
