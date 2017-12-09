//
// Created by Marcin Zawada on 13.11.17.
//

#ifndef TUTORIALS_GLWINDOWUTILS_H
#define TUTORIALS_GLWINDOWUTILS_H

#include <GLFW/glfw3.h>

extern float rotate_speed;
extern float look_far;

typedef void (*glfw_key_callback)(GLFWwindow * window, int key, int scancode, int action, int mods);

GLFWwindow * setupGLWindow(GLFWmonitor * monitor, int width, int height, glfw_key_callback callback);
GLFWmonitor * setupGLMonitor(int monitorNumber);
void initGLFW();
void key_callback(
        GLFWwindow * window, int key, int scancode,
        int action, int mods);

#endif //TUTORIALS_GLWINDOWUTILS_H
