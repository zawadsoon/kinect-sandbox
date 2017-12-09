//
// Created by Marcin Zawada on 28.11.17.
//


#include "Kinect.h"
#include <iostream>
#include "../vendor/libfreenect/include/libfreenect.h"

/**
 * Funkcja zawierająca wszystkie etapy inicjalizacji kinecta za pomocą 
 * biblioteki freenect
 *
 * @param freenectContext - Holds information about the usb context
 * @param freenectDevice - Holds device information.
 * @param callback - depth image received event callbacks
 * @return
 */
int kinect_init (freenect_context ** freenectContext, freenect_device ** freenectDevice, freenect_depth_cb callback) {

    /**
     * Tymaczasowa zmienna do przechowywania błędów
     */

    int ret;

    /**
     * Inicjalizacjia kontekstu
     */

    ret = freenect_init (freenectContext, NULL);

    if (ret < 0)
        return ret;


    /**
     * Szukanie podłaczonych urządzeń
     */

    int numberOfDevices = ret = freenect_num_devices (*freenectContext);

    if (ret < 0)
        return ret;

    if (numberOfDevices == 0){
        std::cout<<"No devices found!"<<std::endl;
        return -1;
    }

    /**
     * Otwieranie urządzenia
     * 0 - czyli pierwsze znalezione urządznie
     */

    ret = freenect_open_device (*freenectContext, freenectDevice, 0);

    if (ret < 0)
        return ret;

    /**
     * Ustawienie trybu głębi
     * FREENECT_RESOLUTION_MEDIUM - rozdzielczość obrazu - 640x480
     * FREENECT_DEPTH_MM - zwaracana głębia jest w zakresie od 0 do 10 metrów
     */

    ret = freenect_set_depth_mode (*freenectDevice, freenect_find_depth_mode(
            FREENECT_RESOLUTION_MEDIUM,
            FREENECT_DEPTH_MM
    ));

    if (ret < 0)
        return ret;

    /**
     * Ustawienie callbacka dla pobrania ramki głębi i uruchomienie pobierania głębi
     */

    freenect_set_depth_callback (*freenectDevice, callback);

    ret = freenect_start_depth(*freenectDevice);

    if (ret < 0)
        return ret;


    return 0;
}
