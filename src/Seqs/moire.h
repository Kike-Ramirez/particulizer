#ifndef MOIRE_H
#define MOIRE_H

#include "ofMain.h"
#include "effect_template.h"

class Moire: public Effect_Template
{
public:
    Moire();

    vector<ofVec3f> particles;
    int numParticles;
    vector<float> audioBeats;

    void postSetup();
    void loadParticles();
    void update(NanoPanel &nanoPanel, AudioInput &audioInput);
    void drawOutput();

};

#endif // MOIRE_H
