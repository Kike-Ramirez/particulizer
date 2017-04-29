#ifndef CIRCLEDANCERS_H
#define CIRCLEDANCERS_H

#include "ofMain.h"
#include "constants.h"

class CircleDancers
{
public:
    CircleDancers();

    int modeSelected;
    ofVec2f position, positionA, positionB;
    ofVec2f target, targetA, targetB;
    float radio, radioTarget;
    float timeA, timerA;

    void setup();
    void update(vector<float> audioBeats_);
    void nextMode();
    void activateFlash();
    void display();

};

#endif // CIRCLEDANCERS_H
