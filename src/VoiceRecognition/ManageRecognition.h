#ifndef __MANAGERECOGNITION_H__
#define __MANAGERECOGNITION_H__

#include "VoiceRecognitionV3.h"

#define TALK_LIGHT  7
#define OK_LIGHT    8
#define ERROR_LIGHT 12

#define OPEN (uint8_t)0
#define CLOSE (uint8_t)1

#define OPEN_SIGN "OPEN"
#define CLOSE_SIGN "CLOSE"

enum States {TRAIN, RECOGNIZE};

class ManageRecognition : public VR{
    
    uint8_t buff[255];
    
    public:
        ManageRecognition(uint8_t RX, uint8_t TX);
        bool trainHand();
        bool loadCommands();
        int8_t controlHand();
};

#endif
