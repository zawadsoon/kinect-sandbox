//
// Created by Marcin Zawada on 28.11.17.
//

#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

namespace ksb {

    /**
     * 0 is monitor domyślny
     * 1 drugi monitor, jeżeli jest dostępny
     */
    static const int monitor = 0;

    /**
     * Ustawienie na sztywno romaru ekranu (px) bo GLFW nie umie w ekran :C
     * DELL 27" 2048x1152, VAIO 15" 1366x768
     */
    static int window_width = 2048;
    static int window_height = 1152;
    //static int window_width = 800;
    //static int window_height = 800;

    float map(float, float, float, float, float);

}

#endif //PROJECT_SETTINGS_H
