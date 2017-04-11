#ifndef EFFECTPANEL_H
#define EFFECTPANEL_H

#include "ofMain.h"


class EffectPanel
{
public:

    ofPoint position;
    ofPoint size;
    ofColor backColor;
    ofColor frontColor;
    EffectPanel();

    void setup(ofPoint position_, ofPoint size_);
    void display();
    void display(const ofFbo &canvas_);

};

#endif // EFFECTPANEL_H
