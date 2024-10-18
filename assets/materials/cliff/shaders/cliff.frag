#version 330 core

in vec3 vertexPosition;
in vec2 textureCoordinates;

out vec4 FragColor;

uniform sampler2D u_AlbedoMap;
uniform sampler2D u_NormalMap;
uniform sampler2D u_MetallicMap;
uniform sampler2D u_RoughnessMap;
uniform sampler2D u_AOMap;

void main()
{
    vec4 albedo = texture(u_AlbedoMap, textureCoordinates);
    vec4 normal = texture(u_NormalMap, textureCoordinates);
    vec4 metallic = texture(u_MetallicMap, textureCoordinates);
    vec4 roughness = texture(u_RoughnessMap, textureCoordinates);
    vec4 ao = texture(u_AOMap, textureCoordinates);

    // Example of combining colors
    FragColor = albedo; // Replace this with your actual shading logic
}