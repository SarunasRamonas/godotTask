extends VideoStreamPlayer

var click_position = Vector2(0,0)
var bVideoPlay = bool(true)
var VideoTimeLabel
var StatusLabel

# Called when the node enters the scene tree for the first time.
func _ready():	
	VideoTimeLabel = get_node("../VBoxContainer/Label_VideoSec")
	StatusLabel = get_node("../VBoxContainer/Label_VideoSec2")
	#pass # Replace with function body.

func _pause_play_video():
	paused = bVideoPlay
	bVideoPlay = !bVideoPlay
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	#pass
	#if	Input.is_action_just_pressed("left_click"):
	#	click_position = get_global_mouse_position()
	#	_pause_play_video()
	
	# Video Data
	# Video Current Time
	var format_string = "Time: %.1f sec"
	var actual_string = format_string % [stream_position]
	VideoTimeLabel.text = actual_string
	

