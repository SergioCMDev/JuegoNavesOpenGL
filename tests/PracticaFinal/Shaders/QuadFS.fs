#version 330 core

in vec2 texCoord;
uniform sampler2D quadTexture;

out vec4 FragColor; 

void main() {
	FragColor = texture(quadTexture, texCoord);
	//FragColor = vec4(vec3(1.0,0.0,0.0), 1.0);
}