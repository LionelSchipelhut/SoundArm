#include "ManageRecognition.h"


ManageRecognition::ManageRecognition (uint8_t RX, uint8_t TX)
: VR(RX, TX) {

}


bool ManageRecognition::trainHand () {
    int recv;

    recv = this->trainWithSignature(OPEN, OPEN_SIGN, 5, this->buff);
    if (recv <= 0) return false;
    Serial.print("Trained: ");
    Serial.println(this->buff[2], HEX);

    this->trainWithSignature(CLOSE, CLOSE_SIGN, 6, this->buff);
    if (recv <= 0) return false;
    Serial.print("Trained: ");
    Serial.println(this->buff[2], HEX);

    return true;

}

bool ManageRecognition::loadCommands () {
    if(this->clear() == 0) Serial.println("Recognizer cleared.");
    else return false;

    if (this->load((uint8_t)OPEN) >= 0) Serial.println("OPEN loaded.");
    else return false;
    
    if (this->load((uint8_t)CLOSE) >= 0) Serial.println("CLOSE loaded.");
    else return false;

    return true;
}

int8_t ManageRecognition::controlHand () {
    int ret;

    ret = this->recognize(this->buff, 50);

    if (ret > 0) {
        Serial.println("Recognized: " + String(this->buff[1]));
        return buff[1];
    }

    return -1;
}
