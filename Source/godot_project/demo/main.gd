extends Node2D

var click_position = Vector2(0,0)
var cursor_offset = Vector2(26,31)

var frame_row = []
var frame_column = []

var rgb_dummy = Vector3(0,0,0)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass
	#click_position = Vector2(position.x, position.y)
	#if	Input.is_action_just_pressed("left_click"):

	
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	#$ComponentDataContainer/VBoxContainer/Label2.text = $VLC_Api.get_status()
	
	pass

# Player Pressed on Video
func _on_video_player_gui_input(event):
	if (event.is_pressed()):
		# Pause or Play Video
		click_position = get_global_mouse_position() - cursor_offset
		$VideoPlayerPanel/VBoxContainer/VideoPlayer._pause_play_video()	
		
		var pixelRGB = $VLC_Api.get_RGB_values("", 10, 50,50)
		
		$ComponentDataContainer/VBoxContainer/Label2.text = "Status: %s" % [$VLC_Api.get_Status()]
		$VideoPlayerPanel/VBoxContainer/VBoxContainer/Label_CursorLocation.text = "Cursor position: %s" % [click_position]
		
		# 

func _set_random_rgb_dummy():
	rgb_dummy.x = randf_range(0,1)
	rgb_dummy.y = randf_range(0,1)
	rgb_dummy.z = randf_range(0,1)

func _update_vis_shader(row:Array, column:Array):
	frame_row = row
	frame_column = column
	
	# Add Row
	var image = Image.new()
	var width = row.size()
	image.create(width, 1, false, Image.FORMAT_RGB8)
	
	image.lock()
	for i in range(width):
		image.set_pixel(i, 0, row[i])
	image.unlock()

	var texture = ImageTexture.new()
	texture.create_from_image(image)

	var material = ShaderMaterial.new()
	
	var ShaderNode = $PanelContainer/VBoxContainer/Visualization
	var RGBShader = ShaderNode.material as ShaderMaterial
	RGBShader.set_shader_parameter("my_texture_1D", row)
	
	
