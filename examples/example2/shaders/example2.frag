#version 330 core

in vec3 vertexPosition;
in vec2 texturePostion;

out vec4 FragColor;

uniform float colorIntensity;
uniform sampler2D texture1;

void main()
{
    FragColor = colorIntensity * texture(texture1, texturePostion);
}