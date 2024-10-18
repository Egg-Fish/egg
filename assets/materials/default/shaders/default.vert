#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoords;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform sampler2D u_HeightMap;

out vec3 vertexPosition;
out vec2 textureCoordinates;

void main()
{
    float heightValue = texture(u_HeightMap, aTextureCoords).r;
    float displacement = (heightValue - 0.5) * 2.0;

    vec3 displacedPosition = aPosition + aNormal * (displacement * 0.1);
    vec4 worldPosition = u_ModelMatrix * vec4(displacedPosition, 1.0);

    gl_Position = u_ProjectionMatrix * u_ViewMatrix * worldPosition;

    vertexPosition = pos;
    textureCoordinates = aTextureCoords;
}