#include "Camera.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream>


egg::Camera::Camera(glm::vec3 worldPosition,
               glm::vec3 worldFront,
               glm::vec3 worldUp)
{
    this->worldPosition = worldPosition;
    this->worldFront = worldFront;
    this->worldUp = worldUp;
}

glm::mat4 egg::Camera::getViewMatrix()
{
    return glm::lookAt(worldPosition, worldPosition + worldFront, worldUp);
}

glm::mat4 egg::Camera::getProjectionMatrix(unsigned int viewWidth, unsigned int viewHeight)
{
    return glm::perspective(45.0f, (float)viewWidth/(float)viewHeight, 0.1f, 100.0f);
}