#include <iostream>
#include <signal.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "vendor/libfreenect/include/libfreenect.h"
#include "support/GLWindowUtils.h"
#include "support/Kinect.h"
#include "support/Settings.h"
#include "support/Cloud.h"

using namespace glm;

Cloud * cloud;

volatile bool running = true;
volatile bool isCloudAvailable = false;

void depth_cb(freenect_device *dev, void *data, uint32_t timestamp){
    if(isCloudAvailable)
        cloud->update(data);
}


void signalHandler(int signal){
    if(signal == SIGINT || signal == SIGTERM || signal == SIGQUIT){
        running = false;
    }
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods){

    if(isCloudAvailable && action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_LEFT:
                cloud->setRotXSpeed(-0.0025f);
                break;
            case GLFW_KEY_RIGHT:
                cloud->setRotXSpeed(0.0025f);
                break;
            case GLFW_KEY_UP:
                cloud->setRotXSpeed(0.0f);
                break;
            default:
                break;
        }
    }

    if(action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_LEFT:
                rotate_speed += 0.005f;
                break;
            case GLFW_KEY_RIGHT:
                rotate_speed -= 0.005f;
                break;
            case GLFW_KEY_UP:
                look_far += 0.025f;
                break;
            case GLFW_KEY_DOWN:
                look_far -= 0.025f;
                break;
            default:
                break;
        }
    }


    switch (key) {
        case GLFW_KEY_UP:
            look_far += 0.05f;
            break;
        case GLFW_KEY_DOWN:
            look_far -= 0.05f;
            break;
        default:
            break;
    }

    return;
}

int main(int argc, char *argv[]){

    /**
     * Obsługa sygnałów (uodpornienie się na fackupy typu Ctrl+C)
     */
    signal (SIGINT,  signalHandler);
    signal (SIGTERM, signalHandler);
    signal (SIGQUIT, signalHandler);


    /**
     * Deklaracja wskaźników kontekstu i urządznia
     */

    freenect_context * fn_ctx;
    freenect_device  * fn_dev;


    /**
     * Inicjalizacja kinecta
     */
    int ret = kinect_init (&fn_ctx, &fn_dev, depth_cb);

    if (ret < 0) {
        freenect_shutdown (fn_ctx);
        return ret;
    }


    /**
     * Inicjalizacja GLFW
     */

    GLFWmonitor * monitor;
    GLFWwindow  * window;

    initGLFW ();

    monitor = setupGLMonitor (ksb::monitor);
    window = setupGLWindow (monitor, ksb::window_width, ksb::window_height, key_callback);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Generowanie bufora openGL - dummy generowanie bo wiem ze tylko bede rysował chmurę
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    /**
     * Macierze widoku i projekcji
     * przygotowanie chmury
     */

    //setup projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(40.0f), (float) ksb::window_width / (float) ksb::window_width, 0.1f, 100.0f);

    //setup view matrix
    glm::mat4 view = glm::lookAt(
            glm::vec3(0,0,-3),
            glm::vec3(0,0,0),
            glm::vec3(0,1,0)
    );

    glm::mat4 pv = projection * view;

    //setup cloud
    cloud = new Cloud(640, 480);
    isCloudAvailable = true;

    /**
     * Pętla rysownia
     */

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw cloud
        cloud->draw(pv);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
             && glfwWindowShouldClose(window) == 0
             && running
             && freenect_process_events(fn_ctx) >= 0);


    /**
     * Zamykanie aplikacji gdy pętla zakończy działanie
     */

    std::cout<<"Closing app"<<std::endl;
    delete cloud;

    // Stop everything and shutdown.
    freenect_stop_depth(fn_dev);
    freenect_close_device(fn_dev);
    freenect_shutdown(fn_ctx);

    std::cout<<"App closed"<<std::endl;
    return 0;
}




