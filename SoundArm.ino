#include "src/VoiceRecognition/ManageRecognition.h"

#define TWO_FINGERS false
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
    Serial.begin(115200);
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

    /*attachInterrupt(
        digitalPinToInterrupt(TRAIN_BTN),
        trainISR,
        RISING
    );*/

    if (!handRec.loadCommands()){
        digitalWrite(ERROR_LIGHT, HIGH);
        delay(2000);
        digitalWrite(ERROR_LIGHT, LOW);
        currentState = TRAIN;
    }
    

    //pinMode(13, INPUT_PULLUP);
    //train();
}

void loop () {

    //int var = digitalRead(13);

    currentFunction[currentState]();
    //Serial.println(var);
    //control.toggleHand(var);
    
}

void trainISR () {
    Serial.println("ISR");
    currentState = TRAIN;
}


void train () {
    Serial.println("Trainer");
    handRec.trainHand();

    currentState = RECOGNIZE;
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
