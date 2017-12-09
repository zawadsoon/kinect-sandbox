//
// Created by Marcin Zawada on 13.11.17.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GLWindowUtils.h"

float rotate_speed = 0.0f;
float look_far = 3.0f;

void initGLFW(){

    if(!glfwInit()){
        std::cout<<"Failed to initialize GLFW"<<std::endl;
        exit(-1);
    }

    std::cout<<"GLFW initialized"<<std::endl;

}

GLFWmonitor * setupGLMonitor(int monitorNumber){

    GLFWmonitor * monitor;

    int count;
    GLFWmonitor ** monitors = glfwGetMonitors(&count);
    std::cout<<"Available monitors: "<<count<<std::endl;

    if (count <= (monitorNumber * 1)){
        monitor = monitors[monitorNumber];
    } else {
        monitor = monitors[0];
    }

    /*
    //Pobranie szczegółów erkanu nie działa ze względu na specyfikę moje linuxa :C
    const GLFWvidmode * mode = glfwGetVideoMode(monitor);
    std::cout<<"monitor width: "<<mode->width<<", heigth: "<<mode->height<<std::endl;
    */

    return monitor;
}

GLFWwindow * setupGLWindow(GLFWmonitor * monitor, int width, int height, glfw_key_callback callback){

    //setup window features
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window;
    window = glfwCreateWindow(width, height, "Virtual Sandbox", NULL, NULL);

    if(window == NULL){
        std::cout<<"Failed to open GLFW window. If you have intel GPU, the are not 3.3 compatible, try version 2.1"<<std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;

    if(glewInit() != GLEW_OK){
        std::cout<<"Failed to initialize GLFW"<<std::endl;
        exit(-1);
    }

    glfwSetWindowMonitor(window, monitor, 0, 0, width, height, 30);

    //http://www.glfw.org/docs/latest/input_guide.html
    glfwSetKeyCallback(window, callback);

    std::cout<<"GLFW window opened"<<std::endl;

    return window;
}

