//#include "BadGL_main.hpp"
#include <cstddef>
#include <stdio.h>
#include "BadGL_window.hpp"
#include "glad/gl.h"
#include <array>
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
    window.initialzeWindow(400,400, "Test");
    //window.initialzeWindow(dimensions.width,dimensions.height, "Test");

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
 
    glLinkProgram(shaderProgram);

    // Create VAO/VBO
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);


    //create and bind verts and attributes
    std::array<float, 9> vertices = {
        0.5f, 0.5f,0.f,
        0.5f, -0.5f,0.0f,
        -0.5f, -0.5f,0.0f

 

    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindVertexArray(VAO);


    while(window.isOpen())
    {
        ScreenDimensions dim = window.getDimensions();
        glViewport(0, 0, dim.width, dim.height);  // <<— Important!
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Use the shader program
        //glUseProgram(This->_shaderProgram);
                // Use the shader program
        glUseProgram(shaderProgram);

        // Bind the VAO
        // Bind the VAO
        //glBindVertexArray(This->_VAO);
        
        // Draw the triangle
        //This->_shader_functions.every_loop_function(This, &shaders);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLE_STRIP,0,vertices.size()/3);

        // Swap front and back buffers
        window.SwapBuffers();

        // Poll for and process events
        glfwPollEvents();  // Ensure This is called to handle window events

    }
    printf("BadGL Has Been Loaded!\n");
}