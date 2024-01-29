shader_type canvas_item;

uniform vec3 PixelColorV3 = vec3(0,0,0);
uniform sampler2D my_texture_1D; // Uniform for the 1D texture

void vertex() {
	// Called for every vertex the material is visible on.
}

void fragment() {
	//vec4 pixelColorV4 = vec4(PixelColorV3.x, PixelColorV3.y, PixelColorV3.z, 1.0);
	//COLOR = pixelColorV4;
    float texCoord = UV.x; // Assuming the texture coordinates are set up along the x-axis
    vec4 color = texture(my_texture_1D, vec2(texCoord, 0.5));
    // Use the color as needed in your shader
    COLOR = color;
	
}

//void light() {
	// Called for every pixel for every light affecting the CanvasItem.
	// Uncomment to replace the default light processing function with this one.
//}
