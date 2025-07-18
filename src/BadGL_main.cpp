#include <cstddef>
#include <initializer_list>
#include <stdio.h>
#include "BadGL_window.hpp"
#include "glad/gl.h"
#include <vector>
#include <iostream>

static GLuint compile_glsl_string(GLenum type, GLchar* const source)
{
    GLuint shader;
    if (!source)
        return 0;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
           GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
        }
    return shader;
}


int main(void)
{

    BadWindow window{};
    ScreenDimensions dimensions = window.getMonitorDimensions();
    //window.initialzeWindow(400,400, "Test");
    window.initialzeWindow(dimensions.width,dimensions.height, "Test");
    std::cout<<"Window Dimensions => "<<dimensions.width<<", "<<dimensions.height<<std::endl;
    GLint vertexShader = compile_glsl_string(GL_VERTEX_SHADER,(char* )R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    varying highp vec3 color;
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        color = vec3(1,1,1);
    }
    )");
    GLint fragShader = compile_glsl_string(GL_FRAGMENT_SHADER,(char*)R"(
    #version 330 core
    out vec4 FragColor;
    varying lowp vec3 color;
    void main()
    {
        FragColor = vec4(color, 1.0f); // Change to red for testing
    }
    )");
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    GLuint VAO =0,VBO=0;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    std::vector<float> square= {
        0,0,0,
        -.5f,.5f,0,
        0.f,.5f,0,
        //other part
    };
    glBufferData(GL_ARRAY_BUFFER,square.size()*sizeof(float),square.data(),GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    while(window.isOpen())
    {
        glClearColor(0.5f,0.5f,0.5f,1.0f);
        glClear(GL_DEPTH_TEST|GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,square.size()/3);
        window.SwapBuffers();
        glfwPollEvents();  // Ensure This is called to handle window events

    }
}