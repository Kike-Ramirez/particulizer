#ifndef CIRCLE_DANCING_H
#define CIRCLE_DANCING_H

#include "ofMain.h"
#include "effect_template.h"
#include "circledancers.h"

class Circle_Dancing: public Effect_Template
{
public:
    Circle_Dancing();

    vector<float> audioBeats;
    CircleDancers circles;

    void postSetup();
    void update(NanoPanel &nanoPanel, AudioInput &audioInput);
    void drawOutput();

};

#endif // CIRCLE_DANCING_H
