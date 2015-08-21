#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>


//This class handles the compilation, linking, and usage of a GLSL shader program.
//Reference: http://www.opengl.org/wiki/Shader_Compilation

namespace taengine {
    class GLSLProgram
    {
    public:
        GLSLProgram();
        ~GLSLProgram();

        void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void compileShadersFromSource(const char* vertexSource, const std::string& vertexShaderFileName,
			const char* fragmentSource, const std::string& fragmentShaderFileName);

        void linkShaders();

        void addAttribute(const std::string& attributeName);

        GLint getUniformLocation(const std::string& uniformName);

        void use();

        void unuse();

		void dispose();
    private:

        GLuint m_programID;

        GLuint m_vertexShaderID;
        GLuint m_fragmentShaderID;

        int m_numAttributes;

		void compileShader(const char* source, const std::string& shaderName, GLuint id);
    };
}

#endif // GLSLPROGRAM_H
