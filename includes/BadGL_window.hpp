#ifndef BADGL_WINDOW
#define BADGL_WINDOW

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <csignal>
#include <exception>
#include <stdexcept>

struct ScreenDimensions
{
    int width = 0,height=0;
};

class BadWindow
{
private:
    GLFWwindow * window;
    ScreenDimensions dimensions = {};
public:
    BadWindow(int width, int height, const char * title,
        int monitor_num = 0, GLFWwindow * share = NULL)
    {
        if(!glfwInit())
        {
            puts("GLFW failed to Init.\n");
            return;
        }
        puts("GLFW Loaded\n");
        dimensions = ScreenDimensions{width,height};

        //zero is primary
        GLFWmonitor **monitor = glfwGetMonitors(&monitor_num);
        this->window = glfwCreateWindow( width,  height, title, monitor[monitor_num], share);
  
        //GLFWmonitor mon;

        glfwMakeContextCurrent(window);
        //window = glfwCreateWindow(800, 600, "Shin Megami Tensei", NULL, NULL);
        if (!window) {
            puts("Failed to create GLFW window");
            glfwTerminate();
            return;
        }
        int version = gladLoadGL(glfwGetProcAddress);

        if (version == 0) {
            puts("Failed to initialize GLAD");
            return;
        }
        puts("GLAD initialized, version: ");
        printf("%i\n",version);
        //glOrtho();
        //glViewport(0, 0, width/2, height/2);
    };
    bool isOpen()
    {
        if(this->window)
            return !glfwWindowShouldClose(this->window);
        else
        {
            throw (std::runtime_error("window is null"));
            return 0;
        }
    }
    void closeWindow()
    {
        glfwSetWindowShouldClose(this->window, true);
    }
    ScreenDimensions getDimensions()
    {
        return dimensions;
    }
    void SwapBuffers()
    {
        glfwSwapBuffers(window);
    }
};

#endif