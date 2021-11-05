#ifndef __CONTROLHAND_H__
#define __CONTROLHAND_H__

#include <Arduino.h>
#include <Servo.h>


#ifndef ERROR_LIGHT
    #define ERROR_LIGHT 12
#endif

#ifndef TWO_FINGERS
    #define TWO_FINGERS true
#endif

#ifndef OPEN
    #define OPEN (uint8_t)  0
#endif

#ifndef CLOSE
    #define CLOSE (uint8_t) 1
#endif

#if (TWO_FINGERS == true)
    #define THUMB   5
    #define FINGERS 6   

    #define OPEN_DEGREE     0
    #define CLOSE_DEGREE    90

    static Servo thumb_o, fingers_o;
#else
    #define THUMB   5
    #define INDEX   6
    #define MIDDLE  9
    #define RING    10
    #define PINKY   11

    //Grado de apertura para el pulgar.
    #define T_OPEN_DEGREE     0
    #define T_CLOSE_DEGREE    90
    //Grado de apertura para el dedo índice.
    #define I_OPEN_DEGREE     0
    #define I_CLOSE_DEGREE    90
    //Grado de apertura para el dedo del medio.
    #define M_OPEN_DEGREE     0
    #define M_CLOSE_DEGREE    90
    //Grado de apertura para el dedo anular.
    #define R_OPEN_DEGREE     0
    #define R_CLOSE_DEGREE    90
    //Grado de apertura para el dedo meñique.
    #define P_OPEN_DEGREE     0
    #define P_CLOSE_DEGREE    90

    static Servo thumb_o, index_o, 
            middle_o, ring_o, 
            pinky_o;
#endif

class ControlHand{

    public:
        ControlHand();
        void begin();
        void toggleHand(uint8_t state);
};

#endif