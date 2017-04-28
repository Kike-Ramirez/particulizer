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

    void setup();
    void update(vector<float> audioBeats_);
    void setMode(int mode_);
    void display();

};

#endif // CIRCLEDANCERS_H
