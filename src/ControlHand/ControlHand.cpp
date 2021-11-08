#include "ControlHand.h"


ControlHand::ControlHand () {}

#if (TWO_FINGERS == true)
    void ControlHand::begin() {
        thumb_o.attach(THUMB);
        thumb_o.write(OPEN_DEGREE);

        fingers_o.attach(FINGERS);
        fingers_o.write(OPEN_DEGREE);
    }

    void ControlHand::toggleHand (uint8_t state) {
        digitalWrite(ERROR_LIGHT, LOW);

        switch (state)
            {
            case OPEN:
                thumb_o.write(OPEN_DEGREE);
                fingers_o.write(OPEN_DEGREE);
                break;
            
            case CLOSE:
                thumb_o.write(CLOSE_DEGREE);
                fingers_o.write(CLOSE_DEGREE);
                break;
            default:
                digitalWrite(ERROR_LIGHT, HIGH);
            }
        }

#else
    void ControlHand::begin() {
        thumb_o.attach(THUMB);
        thumb_o.write(T_OPEN_DEGREE);

        index_o.attach(INDEX);
        index_o.write(I_OPEN_DEGREE);

        middle_o.attach(MIDDLE);
        middle_o.write(M_OPEN_DEGREE);

        ring_o.attach(RING);
        ring_o.write(R_OPEN_DEGREE);

        pinky_o.attach(PINKY);
        pinky_o.write(P_OPEN_DEGREE);
    }
    void ControlHand::toggleHand (uint8_t state) {
        digitalWrite(ERROR_LIGHT, LOW);

        switch (state)
            {
            case OPEN:
                thumb_o.write(T_OPEN_DEGREE);
                index_o.write(I_OPEN_DEGREE);
                middle_o.write(M_OPEN_DEGREE);
                ring_o.write(R_OPEN_DEGREE);
                pinky_o.write(P_OPEN_DEGREE);
                break;
            
            case CLOSE:
                thumb_o.write(T_CLOSE_DEGREE);
                index_o.write(I_CLOSE_DEGREE);
                middle_o.write(M_CLOSE_DEGREE);
                ring_o.write(R_CLOSE_DEGREE);
                pinky_o.write(P_CLOSE_DEGREE);
                break;
            default:
                digitalWrite(ERROR_LIGHT, HIGH);
            }
        }
#endif