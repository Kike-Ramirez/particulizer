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
    ofColor selectedColor;

    EffectPanel();

    void setup(ofPoint position_, ofPoint size_);
    void display();
    void display(const ofFbo &canvas_);
    void setColors(ofColor frontColor_, ofColor backColor, ofColor selectedColor_);

};

#endif // EFFECTPANEL_H
