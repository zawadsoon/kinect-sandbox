//
// Created by Marcin Zawada on 29.11.17.
//

#ifndef PROJECT_CLOUD_H
#define PROJECT_CLOUD_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Cloud {

public:
    Cloud(int x, int y);
    ~Cloud();
    void draw(glm::mat4 pv);
    void genPointArray(GLfloat * pointsArray);
    void update(void * depthArray);
    void setRotXSpeed(float);

private:
    int cols, rows, bufferSize;
    float rotXSpeed = 0.0f, rotX = 0.0f;
    int16_t * depthArray;
    glm::mat4 modelMatrix, mvp, rot;
    GLuint mvp_handle, color_handle, positionHandle;
    GLuint program;
    GLuint pointsVertexBuffer;
    GLfloat * pointsVertexBufferData;

};

#endif //PROJECT_CLOUD_H
