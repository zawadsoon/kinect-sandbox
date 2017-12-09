//
// Created by Marcin Zawada on 13.11.17.
//
#include "UtilsShader.h"
#include <iostream>
#include <fstream>
#include <vector>

std::string UtilsShader::ReadShaderFromFile(const char *file){
    std::string shaderCode;
    std::ifstream shaderStream(file, std::ios::in);
    if(shaderStream.is_open()){
        std::string line = "";
        while(getline(shaderStream, line))
            shaderCode += "\n" + line;

        shaderStream.close();
    } else {
        std::cout<<"Cant open file: "<<file<<std::endl;
    }
    return shaderCode;
}

void UtilsShader::CompileShader(GLuint *shaderID, std::string shaderCode, const char *shaderFile){

    //Compile shader
    std::cout<<"Compiling shader: "<<shaderFile;
    char const *shaderSourcePointer = shaderCode.c_str();
    glShaderSource(*shaderID, 1, &shaderSourcePointer, NULL);
    glCompileShader(*shaderID);

    //Test shader
    GLint Result = GL_FALSE;
    int InfoLogLength;

    glGetShaderiv(*shaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(*shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if(InfoLogLength > 0){
        std::vector<char> shaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(*shaderID, InfoLogLength, NULL, &shaderErrorMessage[0]);
        std::cout<<&shaderErrorMessage[0]<<std::endl;
    }
}

GLuint UtilsShader::LoadShaders(const char *vertexShaderFile, const char *fragmentShaderFile) {

    //prepare shaders
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragemntShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    //read shaders code from files
    std::string vertexShaderCode = UtilsShader::ReadShaderFromFile(vertexShaderFile);
    std::string fragmentShaderCode = UtilsShader::ReadShaderFromFile(fragmentShaderFile);
    //std::cout << "vertex shader: " << vertexShaderCode << std::endl;
    //std::cout <<  "fragment shader: " << fragmentShaderCode << std::endl;

    //compile shaders code
    UtilsShader::CompileShader(&vertexShaderID, vertexShaderCode, vertexShaderFile);
    UtilsShader::CompileShader(&fragemntShaderID, fragmentShaderCode, fragmentShaderFile);

    //creating program
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragemntShaderID);

    std::cout<<"Linking program"<<std::endl;
    glLinkProgram(programID);

    //test program
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    glGetProgramiv(programID, GL_LINK_STATUS, &Result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        std::cout<<&ProgramErrorMessage[0]<<std::endl;
    }

    //detach and delete shaders
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragemntShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragemntShaderID);

    return programID;
}