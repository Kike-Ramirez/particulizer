#ifndef LIGHTHAIR_H
#define LIGHTHAIR_H

#include "ofMain.h"
#include "effect_template.h"

class LightHair: public Effect_Template
{
public:

    LightHair();
    ofCamera camera;

    void update(NanoPanel &nanoPanel, AudioInput &audioInput);
    void drawOutput();

};

#endif // LIGHTHAIR_H
