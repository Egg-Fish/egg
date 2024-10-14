#include "egg/Window.hpp"
#include "egg/Shader.hpp"
#include "egg/VertexBuffer.h"
#include "egg/VertexBufferLayout.h"
#include "egg/VertexArray.hpp"
#include "egg/Texture.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

void main()
{
    Window window(600, 600, "Example 2");

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

    Texture texture(
        "example2/textures/container.jpg"
    );

    shader.setUniform1i(
        "texture1", 0
    );

    VertexArray va;

    float vertices[] = {

        +0.0f, +0.5f, +0.0f, 0.5f, 1.0f,
        +0.5f, -0.5f, +0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, +0.0f, 0.0f, 0.0f

    };

    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout vbl;
    vbl.push(0, 3, GL_FLOAT);
    vbl.push(1, 2, GL_FLOAT);

    va.addBuffer(vb, vbl);

    ImVec4 clearColor = ImVec4(0.2f, 0.3f, 0.3f, 1.0f);

    while (!window.shouldClose())
    {
        window.pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        static float colorIntensity = 1.0f;
        {
            ImGui::Begin("Hello, world!");
            ImGui::Text("This is some useful text."); 

            ImGui::SliderFloat("Color Intensity", &colorIntensity, 0.0f, 1.0f);

            ImGui::ColorEdit3("Background Color", (float*)&clearColor);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        shader.setUniform1f("colorIntensity", colorIntensity);

        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.swapBuffers();
    }
}