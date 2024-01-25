shader_type canvas_item;

uniform vec3 PixelColorV3 = vec3(0,0,0);

void vertex() {
	// Called for every vertex the material is visible on.
}

void fragment() {
	vec4 pixelColorV4 = vec4(PixelColorV3.x, PixelColorV3.y, PixelColorV3.z, 1.0);
	COLOR = pixelColorV4;
	
}

//void light() {
	// Called for every pixel for every light affecting the CanvasItem.
	// Uncomment to replace the default light processing function with this one.
//}
