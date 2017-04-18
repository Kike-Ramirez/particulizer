#ifndef FLOCKING_H
#define FLOCKING_H

#include "ofMain.h"
#include "effect_template.h"

class Flocking: public Effect_Template
{
public:
    Flocking();

    void postSetup();
    void update(NanoPanel &nanoPanel, AudioInput &AudioInput);
    void drawOutput();

};

#endif // FLOCKING_H
