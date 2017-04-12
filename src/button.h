#ifndef BUTTON_H
#define BUTTON_H

#include "ofMain.h"

class Button
{
public:

    ofPoint position;
    ofPoint size;
    int type;
    float val;
    ofColor backColor, frontColor, selectedColor;

    Button();

    void setup(ofPoint position_, ofPoint size_, int type_);
    void update(float val_);
    float getVal();
    void display();
    void setColors(ofColor frontColor_, ofColor backColor, ofColor selectedColor_);


};

#endif // BUTTON_H
