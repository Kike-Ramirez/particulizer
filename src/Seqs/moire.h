#ifndef MOIRE_H
#define MOIRE_H

#include "ofMain.h"
#include "effect_template.h"
#include "audioinput.h"
#include "moirefront.h"

class Moire: public Effect_Template
{
public:
    Moire();

    vector<ofVec3f> particles;
    int numParticles;
    vector<float> audioBeats;
    vector<ofShader> shadersSequence;
    int subSequenceIndex;
    int subSequenceNum;
    vector<float> drawSamples;
    MoireFront moireFront;

    void postSetup();
    void loadParticles();
    void update(NanoPanel &nanoPanel, AudioInput &audioInput);
    void drawOutput();

};

#endif // MOIRE_H
