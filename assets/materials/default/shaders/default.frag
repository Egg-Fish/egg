#version 330 core

in vec3 vertexPosition;
in vec2 textureCoordinates;

out vec4 FragColor;

uniform sampler2D u_AlbedoMap;
uniform sampler2D u_NormalMap;
uniform sampler2D u_MetallicMap;
uniform sampler2D u_RoughnessMap;
uniform sampler2D u_AmbientOcclusionMap;

void main()
{
    FragColor = texture(u_AlbedoMap, textureCoordinates);
}