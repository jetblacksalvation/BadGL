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
    const GLFWvidmode * Mode = NULL;
public:
    BadWindow()
    {
        if(!glfwInit())
        {
            puts("GLFW failed to Init.\n");
            return;
        }

    }
    BadWindow(int width, int height, const char * title,
        int monitor_num = 0, GLFWwindow * share = NULL)
    {
        if(!glfwInit())
        {
            puts("GLFW failed to Init.\n");
            return;
        }
    initialzeWindow(width,height,title,monitor_num,share);
        //glOrtho();
        //glViewport(0, 0, width/2, height/2);
    };
    void initialzeWindow(int width, int height, const char * title,
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
        int monitor_count = 0;
        GLFWmonitor **monitor = glfwGetMonitors(&monitor_count);
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
        Mode = glfwGetVideoMode(monitor[monitor_num]);

        puts("GLAD initialized, version: ");
        printf("%i\n",version);
    }
    /*
        If default initialized, getDimensions will raise an exception. This function will not.
        getDimensions gets the dimensions of the window, not the screen.
        if the window isn't initialized via iniitalize window, getDimensions will segfault.
    */
    ScreenDimensions getMonitorDimensions(int monitor_num = 0)
    {
        int monitor_count = 0;

        GLFWmonitor **monitor = glfwGetMonitors(&monitor_count);
        const GLFWvidmode * mode = glfwGetVideoMode(monitor[monitor_num]);
        
        return {mode->width, mode->height};
    }
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