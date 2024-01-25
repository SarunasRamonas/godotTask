extends Node2D
var click_position = Vector2(0,0)
var rgb_dummy = Vector3(0,0,0)

# Called when the node enters the scene tree for the first time.
func _ready():
	click_position = Vector2(position.x, position.y)
	
	# Initialize RGB Shader

	
	#pass # Replace with function body.

func _physics_process(delta):
	if	Input.is_action_just_pressed("left_click"):
		click_position = get_global_mouse_position()
		
	var target_position = click_position - position
	
	var format_string = "Mouse clicked on: %s position"
	var actual_string = format_string % [target_position]
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	$ComponentDataContainer/VBoxContainer/Label2.text = $VLC_Api.get_status()
	var ShaderNode = $PanelContainer/VBoxContainer/Visualization
	var RGBShader = ShaderNode.material as ShaderMaterial
	_set_random_rgb_dummy()
	RGBShader.set_shader_parameter("PixelColorV3", rgb_dummy)
	#pass


func _on_video_player_gui_input(event):
	if (event.is_pressed()):
		$VideoPlayerPanel/VBoxContainer/VideoPlayer._pause_play_video()	
		var project_path = ProjectSettings.globalize_path("res://")
		project_path =  project_path + ("VideoTest.mp4")
		var rgb_vector = $VLC_Api.get_RGB_values("VideoTest.avi",10,100, 100)
		print(project_path)
		
		
		#var actual_string = Status_string % [$VLC_Api.get_RGB_values("",0,500,500).x]
		#$VideoPlayerPanel/VBoxContainer/VBoxContainer/Label_VideoSec2.text = actual_string

func _set_random_rgb_dummy():
	rgb_dummy.x = randf_range(0,1)
	rgb_dummy.y = randf_range(0,1)
	rgb_dummy.z = randf_range(0,1)
