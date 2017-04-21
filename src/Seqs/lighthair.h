#ifndef LIGHTHAIR_H
#define LIGHTHAIR_H

#include "ofMain.h"
#include "effect_template.h"
#include "Resources/segment.h"
#include "Resources/travelling.h"

class LightHair: public Effect_Template
{
public:

    LightHair();
    Travelling camera;
    ofxPostGlitch glitch;
    ofFbo testCanvas;

    vector<Segment> segments;
    vector<ofImage> images;

    void postSetup();
    void update(NanoPanel &nanoPanel, AudioInput &audioInput);
    void drawOutput();

};

#endif // LIGHTHAIR_H
