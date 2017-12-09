//
// Created by Marcin Zawada on 29.11.17.
//

#include "Cloud.h"
#include "Settings.h"
#include "UtilsShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Cloud::Cloud(int x, int y){
    //Assigning x, y values
    this->cols = x;
    this->rows = y;

    //Stworznie tablicy z ilością elementów cols * rows * 3
    //Ponieważ width * height * 3 [x,y,z coordinates]
    this->bufferSize = this->cols * this->rows * 3;

    this->pointsVertexBufferData = new GLfloat[this->bufferSize];
    std::cout<<"buffer size: "<<this->bufferSize * sizeof(this->bufferSize)<<std::endl;

    //Wypełnienie tablicy startowymi danymi
    this->genPointArray(this->pointsVertexBufferData);

    glGenBuffers(1, &this->pointsVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->pointsVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->bufferSize * sizeof(this->bufferSize), this->pointsVertexBufferData, GL_DYNAMIC_DRAW);

    //generowanie programu
    this->program = UtilsShader::LoadShaders("shaders/simple.vert", "shaders/simple.frag");

    //get mvp and color handler
    this->mvp_handle = glGetUniformLocation(this->program, "MVP");
    this->color_handle = glGetUniformLocation(this->program, "color");
    this->positionHandle = glGetAttribLocation(this->program, "vPosition");

    glUniform4f(this->color_handle, .5f, .5f, .5f, 1.0f);
    std::cout<<"cloud generated"<<std::endl;
}

Cloud::~Cloud() {
    delete[] this->pointsVertexBufferData;
}

void Cloud::update(void * data){

    this->depthArray = (int16_t *) data;

    for(int i = 0, m = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols*3; j+=3, m++){
            this->pointsVertexBufferData[i*this->cols*3+j+2] = (float) this->depthArray[m];
        }
    }

    glGenBuffers(1, &this->pointsVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->pointsVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->bufferSize * sizeof(this->bufferSize), this->pointsVertexBufferData, GL_DYNAMIC_DRAW);

}

void Cloud::draw(glm::mat4 pv){
    glUseProgram(this->program);

    this->rot = glm::rotate(3.14f, glm::vec3(0,0,1)) * glm::rotate(this->rotX, glm::vec3(0,1,0));
    this->modelMatrix = glm::mat4(1.0) * this->rot;

    this->mvp = pv * this->modelMatrix;
    glUniformMatrix4fv(this->mvp_handle, 1, GL_FALSE, &this->mvp[0][0]);

    glEnableVertexAttribArray(this->positionHandle);
    glBindBuffer(GL_ARRAY_BUFFER, this->pointsVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glDrawArrays(GL_POINTS, 0, this->bufferSize / 3);
    glDisableVertexAttribArray(this->positionHandle);

    this->rotX += this->rotXSpeed;
}

/**
 * Generowanie bufora przechowującego wierzchołki
 * [x,y,z,x,y,z...]
 * gdzie x i y rozciągnięte są od -1 do 1,
 * ilość punktów między tymi koordynatami to szerokość okna dla x i wysokość okna dla y
 */
void Cloud::genPointArray(GLfloat * pointsArray){
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols*3; j+=3){
            //To mapowanie jest bardzo wolne i powinno być robione w shaderach,
            //Ale tutaj robimy to tylko raz na potrzeby generowania bufora
            pointsArray[i*this->cols*3+j]   = ksb::map(j, 0, this->cols*3 - 3, -1, 1);
            pointsArray[i*this->cols*3+j+1] = ksb::map(i, 0, this->rows - 1, -1, 1);
            pointsArray[i*this->cols*3+j+2] = 0.0f;
        }
    }
}

void Cloud::setRotXSpeed (float s) {
    this->rotXSpeed = s;
}