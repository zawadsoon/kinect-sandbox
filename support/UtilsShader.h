//
// Created by Marcin Zawada on 13.11.17.
//

#ifndef UTILSSHADER_H
#define UTILSSHADER_H

#include <GL/glew.h>
#include <iostream>

class UtilsShader {

    public:
        static std::string ReadShaderFromFile(const char *file);
        static GLuint LoadShaders(
                const char *vertexShaderFile, const char *fragmentShaderFile);

    private:
        static void CompileShader(
                GLuint *shaderID, std::string shaderCode, const char *shaderFile);
};


#endif //UTILSSHADER_H
