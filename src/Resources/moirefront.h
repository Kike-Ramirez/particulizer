#ifndef MOIREFRONT_H
#define MOIREFRONT_H

#include "ofMain.h"

class MoireFront
{
public:
    MoireFront();

    void setup(ofFbo &canvas);
    void update();
    void draw1(ofFbo &canvas, vector<float> drawSamples, ofColor colorMoire);
    void draw2(ofFbo &canvas, vector<float> drawSamples, ofColor colorMoire);
    void draw3(ofFbo &canvas, vector<float> drawSamples, ofColor colorMoire);
    void draw(ofFbo &canvas, vector<float> drawSamples, ofColor colorMoire);
    void shoot(float v);

    int index;
    float timerCheck;
    ofFbo canvasMoire;


};

#endif // MOIREFRONT_H
