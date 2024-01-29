extends Button


# Called when the node enters the scene tree for the first time.
func _ready():
	pressed.connect(self._button_pressed)
	pass # Replace with function body.

func _button_pressed() :
	var Animation_Player = get_node("../../VideoPlayer")
	#Animation_Player.stop()
	Animation_Player._pause_play_video()
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
