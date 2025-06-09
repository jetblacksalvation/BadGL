#ifndef BADGL_SHADERS
#define BADGL_SHADERS
/*
    Will be Included in BadWindow
*/
#include "glad/gl.h"
#include <cstddef>
/*
    https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml

GLuint glCreateShader(	GLenum shaderType);

Parameters
shaderType ->
Specifies the type of shader to be created. 
    Must be one of GL_COMPUTE_SHADER, GL_VERTEX_SHADER, 
        GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, 
        GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.

*/
enum BadShaderTypes : GLenum
{
    ComputeShader  = GL_COMPUTE_SHADER, 
    VertexShader   = GL_VERTEX_SHADER, 
    TessEvalShader = GL_TESS_EVALUATION_SHADER, 
    GeometryShader = GL_GEOMETRY_SHADER,  
    FragmentShader = GL_FRAGMENT_SHADER,
    TessControlShader = GL_TESS_CONTROL_SHADER
};

class BadShader
{
    public:
    BadShader(BadShaderTypes type, GLchar* const source) : Type(type), Source(source)
    {
        
    }
    BadShader()
    {

    }
    private:
    void CompileShader(GLchar* const source)
    {
        GLuint shader;
        if (!source)
            return;
        shader = glCreateShader(this->Type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        ShaderId = shader;
    };
    BadShaderTypes Type;
    GLchar* const Source = NULL;
    bool Initialized = false;
    // I like being able to crate a variable and initialize it later sometimes, so im keeping this here.
    GLint ShaderId = 0;//opengl gives GLint back when compiling the shader.
    //Passs ShaderId to freinds.
};

class BadProgram
{
    public:


    private:

};


#endif