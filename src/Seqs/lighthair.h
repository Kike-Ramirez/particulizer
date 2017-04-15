#ifndef LIGHTHAIR_H
#define LIGHTHAIR_H

#include "ofMain.h"
#include "effect_template.h"

class LightHair: public Effect_Template
{
public:

    LightHair();

    void update();
    void drawOutput();

};

#endif // LIGHTHAIR_H
