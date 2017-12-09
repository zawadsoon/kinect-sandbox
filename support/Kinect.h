//
// Created by Marcin Zawada on 28.11.17.
//

#ifndef PROJECT_KINECT_H
#define PROJECT_KINECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../vendor/libfreenect/include/libfreenect.h"

int kinect_init (freenect_context ** freenectContext,
                 freenect_device ** freenectDevice,
                 freenect_depth_cb callback);

#endif //PROJECT_KINECT_H
