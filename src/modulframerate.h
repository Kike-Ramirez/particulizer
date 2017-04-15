#ifndef MODULFRAMERATE_H
#define MODULFRAMERATE_H

#include "ofMain.h"

class ModulFrameRate
{
public:
    ModulFrameRate();

    ofPoint position;
    ofPoint size;
    ofColor frontColor;
    ofColor backColor;
    ofColor selectedColor;

    void setup(ofPoint position_, ofPoint size_);
    void setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_);
    void display();

};

#endif // MODULFRAMERATE_H
