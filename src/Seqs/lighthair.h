#ifndef LIGHTHAIR_H
#define LIGHTHAIR_H

#include "ofMain.h"
#include "effect_template.h"
#include "Resources/segment.h"
#include "Resources/travelling.h"
#include "constants.h"

class LightHair: public Effect_Template
{
public:

    LightHair();
    Travelling camera;

    vector<Segment> segments;
    vector<ofImage> images;
    int indexImages;
    int numImages;
    int numParticles;
    vector<float> audioBeats;

    void postSetup();
    void loadParticles(int index_);
    void update(NanoPanel &nanoPanel, AudioInput &audioInput);
    void drawOutput();

};

#endif // LIGHTHAIR_H
