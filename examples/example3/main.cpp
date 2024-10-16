#include "egg.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>

void main()
{
    gl::Window window(1000, 1000, "Example 3!!!");

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    gl::Shader shader(
        "example3/shaders/example3.vert",
        "example3/shaders/example3.frag");

    shader.use();

    gl::Texture texture("example3/textures/container.jpg");

    shader.setUniform1i("texture1", 0);

    egg::Camera camera(
        glm::vec3(0.0f, 0.0f, 3.0f));

    glm::mat4 viewMatrix = camera.getViewMatrix();
    glm::mat4 projectionMatrix = camera.getProjectionMatrix(window.getWidth(), window.getHeight());

    shader.setUniformMatrix4fv("u_ViewMatrix", 1, false, glm::value_ptr(viewMatrix));
    shader.setUniformMatrix4fv("u_ProjectionMatrix", 1, false, glm::value_ptr(projectionMatrix));

    gl::VertexArray va;

    float vertices[] = {
        // Position          // UV
        -0.5f, +0.5f, +0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, +0.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, +0.0f, 1.0f, 0.0f,
        +0.5f, +0.5f, +0.0f, 1.0f, 1.0f};

    gl::VertexBuffer vb(vertices, sizeof(vertices));

    gl::VertexBufferLayout vbl;
    vbl.push(0, 3, GL_FLOAT);
    vbl.push(1, 2, GL_FLOAT);

    va.addBuffer(vb, vbl);

    unsigned int indices1[] = {0, 1, 2};
    unsigned int indices2[] = {0, 2, 3};

    gl::ElementBuffer eb1(indices1, sizeof(indices1));
    egg::Mesh mesh1(va, eb1);

    gl::ElementBuffer eb2(indices2, sizeof(indices2));
    egg::Mesh mesh2(va, eb2);

    ImVec4 clearColor = ImVec4(0.2f, 0.3f, 0.3f, 1.0f);

    float crateVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    gl::VertexArray crateVA;
    gl::VertexBuffer crateVB(crateVertices, sizeof(crateVertices));
    gl::VertexBufferLayout crateVBL;
    crateVBL.push(0, 3, GL_FLOAT);
    crateVBL.push(1, 2, GL_FLOAT);
    crateVA.addBuffer(crateVB, crateVBL);
    
    egg::Mesh crateMesh(crateVA);

    std::vector<egg::Mesh *> meshes;
    meshes.push_back(&mesh1);
    meshes.push_back(&mesh2);
    meshes.push_back(&crateMesh);

    while (!window.shouldClose())
    {
        glEnable(GL_DEPTH_TEST);
        window.pollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static float colorIntensity = 1.0f;
        static glm::vec3 cratePosition(0.0f);
        static glm::vec3 crateRotation(0.0f);

        static bool meshSelection[] = {false, false, true};
        {
            ImGui::Begin("Hello, world!");
            ImGui::Text("This is some useful text.");

            ImGui::SliderFloat("Color Intensity", &colorIntensity, 0.0f, 1.0f);

            ImGui::ColorEdit3("Background Color", (float *)&clearColor);
            ImGui::DragFloat3("Position", glm::value_ptr(cratePosition), 0.1f, -10.0f, 10.0f);
            ImGui::DragFloat3("Rotation", glm::value_ptr(crateRotation), 5.0f, -360.0f, 360.0f, "%.1f deg");

            if (ImGui::TreeNode("Meshes"))
            {
                ImGui::Selectable("Mesh 1", &meshSelection[0]);
                ImGui::Selectable("Mesh 2", &meshSelection[1]);
                ImGui::Selectable("Crate", &meshSelection[2]);
                ImGui::TreePop();
            }

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int i = 0; i < meshes.size(); i++)
        {
            if (meshSelection[i])
            {
                egg::Mesh *m = meshes[i];
                m->bind();
                std::cout << m->getCount() << std::endl;
                glDrawElements(GL_TRIANGLES, m->getCount(), GL_UNSIGNED_INT, nullptr);
            }
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.swapBuffers();
    }
}