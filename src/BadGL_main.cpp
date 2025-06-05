//#include "BadGL_main.hpp"
#include <cstddef>
#include <stdio.h>
#include "BadGL_main.hpp"
#include "BadGL_window.hpp"
#include "glad/gl.h"

static GLuint compile_glsl_string(GLenum type, GLchar* const source)
{
    GLuint shader;
    if (!source)
        return 0;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    return shader;
}

int main(void)
{
    BadWindow window(800,800,"bruh");
    GLint vertexShader = compile_glsl_string(GL_VERTEX_SHADER,(char* )R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 vertexColor;
    varying highp vec3 color;
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        color = vertexColor;
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
    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //      0.0f,  0.5f, 0.0f,
    //      0.5f, -0.5f, 0.0f,
    // };
    float vertices[] = {
             0.3f,  0.5f, 0.0f,  // top right
             0.5f,  0.0f, 0.0f,  // middle right
             0.3f, -0.5f, 0.0f,  // bottom right
            -0.3f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.0f, 0.0f,  // middle left
            -0.3f,  0.5f, 0.0f   // top left 
    };
    // Create VAO/VBO
    unsigned int VAO, VBO;
    unsigned int   EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    unsigned int indices[] = {
        0, 5, 4, // first triangle
        0, 4, 1, // second triangle
        1, 4, 3, // third triangle
        1, 3, 2  // forth triangle
    };


    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    while(window.isOpen())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        //glUseProgram(This->_shaderProgram);
                // Use the shader program
        glUseProgram(shaderProgram);

        // Bind the VAO
        glBindVertexArray(VAO);
        // Bind the VAO
        //glBindVertexArray(This->_VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        // Draw the triangle
        //This->_shader_functions.every_loop_function(This, &shaders);

        
        // Swap front and back buffers
        window.SwapBuffers();

        // Poll for and process events
        glfwPollEvents();  // Ensure This is called to handle window events

    }
    printf("BadGL Has Been Loaded!\n");
}