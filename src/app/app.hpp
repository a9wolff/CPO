#ifndef PROJET_APP_HPP
#define PROJET_APP_HPP

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <chrono>

#include "utils.hpp"
#include "imgui_render/render.hpp"

#define FPS 144


namespace app {

    int start_app()
    {
        GLFWwindow* window;

        //Initialize GLFW library
        if(!glfwInit())
        {
            std::cout << "Error while initializing GLFW.\n";
            return -1;
        }

        //OpenGL version 4.6
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //Create window
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(1600, 800, "Data visualization", nullptr, nullptr);

        //Check error
        if(!window)
        {
            glfwTerminate();
            return -1;
        }

        //Window current context + callbacks
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        //Capture mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        //Initialize GLEW library
        if(glewInit() != GLEW_OK)
        {
            std::cout << "Error while initializing GLEW.\n";
            return -1;
        }

        //Print info (to be removed)
        std::cout << glGetString(GL_VERSION) << '\n';

        //Initialize ImGui library
        imgui_render::init(window);


        //Loop until user closes the window
        while(!glfwWindowShouldClose(window))
        {
            //Measure time to render frame
            auto t0 = std::chrono::steady_clock::now();

            //Process keyboard input
            processInput(window);

            //Clear window
            glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);


            /* Render */

            imgui_render::render();

            /* End Render */


            //Swap buffers
            glfwSwapBuffers(window);

            //Poll events
            glfwPollEvents();

            //Measure time to render frame
            auto t1 = std::chrono::steady_clock::now();

            //Calculate time to render frame
            std::chrono::duration<float> delta(t1 - t0);

            //Sleep to reach targeted framerate
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/FPS) - std::chrono::duration_cast<std::chrono::milliseconds>(delta));

        }

        //Terminate ImGui library
        imgui_render::terminate();

        //Destroy window
        glfwDestroyWindow(window);

        //Terminate GLFW library
        glfwTerminate();

        return 0;
    }

} //namespace app


#endif //PROJET_APP_HPP
