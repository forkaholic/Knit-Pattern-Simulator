#version 330 core

uniform float gScale;
out vec4 FragColor;

void main() {
	FragColor = vec4(gScale * 1.0, gScale * 0.5 * 1.0, 1.0, 1.0);
}
