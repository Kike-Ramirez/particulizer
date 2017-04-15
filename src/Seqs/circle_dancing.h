#ifndef CIRCLE_DANCING_H
#define CIRCLE_DANCING_H

#include "ofMain.h"
#include "effect_template.h"

class Circle_Dancing: public Effect_Template
{
public:
    Circle_Dancing();

    void update(NanoPanel &nanoPanel, AudioInput &audioInput);
    void drawOutput();

};

#endif // CIRCLE_DANCING_H
