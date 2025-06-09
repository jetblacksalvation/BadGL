#ifndef BADGL_WINDOW
#define BADGL_WINDOW

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <stdexcept>

struct ScreenDimensions
{
    int width = 0,height=0;
};

class BadWindow
{
private:
    GLFWwindow * Window;
    ScreenDimensions Dimensions = {};
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
        Dimensions = ScreenDimensions{width,height};

        //zero is primary
        GLFWmonitor **monitor = glfwGetMonitors(&monitor_num);
        this->Window = glfwCreateWindow( width,  height, title, monitor[monitor_num], share);
  
        //GLFWmonitor mon;

        glfwMakeContextCurrent(Window);
        //window = glfwCreateWindow(800, 600, "Shin Megami Tensei", NULL, NULL);
        if (!Window) {
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
        if(this->Window)
            return !glfwWindowShouldClose(this->Window);
        else
        {
            throw (std::runtime_error("window is null"));
            return 0;
        }
    }
    void closeWindow()
    {
        glfwSetWindowShouldClose(this->Window, true);
    }
    ScreenDimensions getDimensions()
    {
        return Dimensions;
    }
    void SwapBuffers()
    {
        glfwSwapBuffers(Window);
    }
};

#endif