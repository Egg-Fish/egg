#version 330 core

in vec3 vertexPosition;
in vec3 vertexColor;

out vec4 FragColor;

uniform float colorIntensity;

void main()
{
    FragColor = colorIntensity * vec4(vertexColor.xyz, 1.0);
}