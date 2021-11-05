#include <Arduino.h>
#include "src/VoiceRecognition/ManageRecognition.h"

#define TWO_FINGERS true
#include "src/ControlHand/ControlHand.h"

#define TRAIN_BTN   2

void train ();
void recognize ();

ManageRecognition handRec(3, 4);
ControlHand control;
States currentState = RECOGNIZE;

typedef void (*state_function_t)();

state_function_t currentFunction[2] = {
    train,
    recognize
};

void setup () {
    Serial.begin(9600);
    while(!Serial);

    Serial.println("Serial started.");

    handRec.begin(9600);

    Serial.println("DONE!");

    pinMode(TALK_LIGHT, OUTPUT);
    digitalWrite(TALK_LIGHT, LOW);

    pinMode(OK_LIGHT, OUTPUT);
    digitalWrite(OK_LIGHT, LOW);

    pinMode(ERROR_LIGHT, OUTPUT);
    digitalWrite(ERROR_LIGHT, LOW);

    pinMode(TRAIN_BTN, INPUT_PULLUP);

    control.begin();

    attachInterrupt(
        digitalPinToInterrupt(TRAIN_BTN),
        trainISR,
        FALLING
    );

    if (!handRec.loadCommands()){
        digitalWrite(ERROR_LIGHT, HIGH);
        delay(2000);
        digitalWrite(ERROR_LIGHT, LOW);
        currentState = TRAIN;
    }
    
    //train();
}

void loop () {

    currentFunction[currentState]();
    //recognize();
}

void trainISR () {
    currentState = TRAIN;
}


void train () {
    Serial.println("Trainer");
    handRec.trainHand();
}


void recognize () {
    int8_t val;

    Serial.println("Recognizer");

    while (currentState == RECOGNIZE) {
        val = handRec.controlHand();
        
        control.toggleHand(val);

        if (val >= 0) {
            digitalWrite(OK_LIGHT, HIGH);
            delay(500);
            digitalWrite(OK_LIGHT, LOW);
        }
    }
}
