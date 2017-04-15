#ifndef MOIRE_H
#define MOIRE_H

#include "ofMain.h"
#include "effect_template.h"

class Moire: public Effect_Template
{
public:
    Moire();

    void update();
    void drawOutput();

};

#endif // MOIRE_H
