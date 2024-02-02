extends Node2D

# Class variables
var click_position = Vector2(0,0)
var cursor_offset = Vector2(50,78)

var row
var col 

# Begin Play
func _ready():
	pass
	
# Called every tick.
func _process(delta):
	pass


func _cursor_on_video_player(event):
	# If Cursor pressed
	if (event.is_pressed()):
		if ($video_player_panel/video_player.stream_position < 8.0) :
			# Print Pixel Location
			click_position = get_global_mouse_position() - cursor_offset
			$godot_info_panel/tex_godot_info/label_pixel_loc.text = "Pixel location: " + str(click_position)
		
			# Print Video duration and Frame Number
			$godot_info_panel/tex_godot_info/label_duration.text = "Video Duration: "+ str($video_player_panel/video_player.stream_position)
			$godot_info_panel/tex_godot_info/label_duration2.text = "Video Frame: " + str( int($video_player_panel/video_player.stream_position * 30))
		
			# Get Selected Pixel's RGB values
			var path_of_video = ProjectSettings.globalize_path("res://") + "VideoTest1.avi"
			var pixelRGB = $ffmpeg_comp_info/FFMpeg_Comp.get_RGB_values(path_of_video, int($video_player_panel/video_player.stream_position * 30), click_position.x,click_position.y)
			# Get Selected Pixel's YUV values
			var YUV = $ffmpeg_comp_info/FFMpeg_Comp.get_YUV_values()
		
			# Print YUV
			$ffmpeg_comp_info/tex_panel/label_YUV.text = " Y: " + str(YUV.x) + "\n U: " + str(YUV.y) + "\n V: " + str(YUV.z)
			# Print Selected Pixel's RGB
			$ffmpeg_comp_info/tex_panel/label_RGB.text = " R: " + str(pixelRGB.x) + "\n G: " + str(pixelRGB.y) + "\n B: " + str(pixelRGB.z)
		
			# Update Selected Pixel's Color Shader
			$data_vis_panel/tex_pixel_vis.material.set_shader_parameter("PixelColorV3", rgb_normalize(pixelRGB))
		
			# Fetch Pixel Row RGB values normalized
			row = $ffmpeg_comp_info/FFMpeg_Comp.get_line_pixels_as_RGB(false)
			$ffmpeg_comp_info/tex_panel/label_RGB5.text = "Fetched lines as RGB: " + str(row.size())
			# Fetch Pixel Columen RGB values normalized
			col = $ffmpeg_comp_info/FFMpeg_Comp.get_column_pixels_as_RGB(true)
			$ffmpeg_comp_info/tex_panel/label_RGB6.text = "Fetched columns as RGB: " + str(col.size())

func _on_h_slider_value_changed(value):
	if row != null:
		if row[value] != null:
			var new_color = row[value * 5]
			$data_vis_panel/tex_pixel_vis2.material.set_shader_parameter("PixelColorV3",row[value * 5])
			$data_vis_panel/tex_vis.material.set_shader_parameter("color1",row[value * 5])


func _on_v_slider_value_changed(value):
	if col != null:
		if col[value] != null:
			var new_color = col[value]
			$data_vis_panel/tex_pixel_vis3.material.set_shader_parameter("PixelColorV3",col[value])
			$data_vis_panel/tex_vis.material.set_shader_parameter("color2",row[value * 5])

			
func _on_check_button_toggled(toggled_on):
	$video_player_panel/video_player.paused = toggled_on


# Close button
func _on_button_exit_pressed():
	quit()

# ESC to close a program
func _input(event):
	if event is InputEventKey:
		if event.pressed and event.keycode == KEY_ESCAPE:
			quit();


# Helpers

# Convert RGB values (from 0 to 255) to float for Vector3 (from 0 to 1)
func rgb_normalize(rgb):
	return Vector3(rgb.x/255.0, rgb.y/255.0, rgb.z/255.0)

func quit():
	get_tree().quit()




