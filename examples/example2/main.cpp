#include "egg/Window.hpp"
#include "egg/Shader.hpp"
#include "egg/VertexBuffer.hpp"
#include "egg/VertexBufferLayout.hpp"
#include "egg/VertexArray.hpp"
#include "egg/Texture.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

void main()
{
    Window window(1000, 1000, "Example 2");

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    Shader shader(
        "example2/shaders/example2.vert",
        "example2/shaders/example2.frag");

    shader.use();

    Texture texture("example2/textures/container.jpg");

    shader.setUniform1i("texture1", 0);

    VertexArray va;

    float vertices[] = {

        -0.5f, +0.5f, +0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, +0.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, +0.0f, 1.0f, 0.0f,
        +0.5f, +0.5f, +0.0f, 1.0f, 1.0f,
    
    };

    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout vbl;
    vbl.push(0, 3, GL_FLOAT);
    vbl.push(1, 2, GL_FLOAT);

    va.addBuffer(vb, vbl);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    ImVec4 clearColor = ImVec4(0.2f, 0.3f, 0.3f, 1.0f);

    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    shader.setUniformMatrix4fv("u_ViewMatrix", 1, false, glm::value_ptr(viewMatrix));

    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
    glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(45.0f), 
        (float)width/(float)height, 
        0.1f, 
        100.0f
    );
    shader.setUniformMatrix4fv("u_ProjectionMatrix", 1, false, glm::value_ptr(projectionMatrix));

    while (!window.shouldClose())
    {
        window.pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        static float colorIntensity = 1.0f;
        static glm::vec3 cratePosition(0.0f);
        static glm::vec3 crateRotation(0.0f);

        {
            ImGui::Begin("Hello, world!");
            ImGui::Text("This is some useful text."); 

            ImGui::SliderFloat("Color Intensity", &colorIntensity, 0.0f, 1.0f);

            ImGui::ColorEdit3("Background Color", (float*)&clearColor);
            ImGui::DragFloat3("Position", glm::value_ptr(cratePosition), 0.1f, -10.0f, 10.0f);
            ImGui::DragFloat3("Rotation", glm::value_ptr(crateRotation), 5.0f, -360.0f, 360.0f, "%.1f deg");

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        const float pi = glm::pi<float>();
        
        modelMatrix = glm::rotate(modelMatrix, (pi / 180.0f) * crateRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, (pi / 180.0f) * crateRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, (pi / 180.0f) * crateRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        modelMatrix = glm::translate(glm::mat4(1.0f), cratePosition) * modelMatrix;

        shader.setUniform1f("colorIntensity", colorIntensity);
        shader.setUniformMatrix4fv("u_ModelMatrix", 1, false, glm::value_ptr(modelMatrix));

        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.swapBuffers();
    }
}