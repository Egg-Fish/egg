#ifndef EGG_CAMERA_H
#define EGG_CAMERA_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace egg
{
    class Camera
    {
    private:
        glm::vec3 worldPosition;
        glm::vec3 worldFront;
        glm::vec3 worldUp;
        glm::vec3 worldRight;

    public:
        Camera(
            glm::vec3 worldPosition,
            glm::vec3 worldFront = glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix(unsigned int viewWidth, unsigned int viewHeight);
    };
}

#endif