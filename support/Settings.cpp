//
// Created by Marcin Zawada on 03.12.17.
//

#include "Settings.h"

namespace ksb {

    /**
     * Funkcja mapująca wartości
     */
    float map(float x, float in_min, float in_max, float out_min, float out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

}