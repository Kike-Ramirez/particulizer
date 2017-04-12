#ifndef OUTPUT_H
#define OUTPUT_H

#include "ofMain.h"
#include "mainpanel.h"

class Output
{
public:
    Output();


    ofPoint position;
    ofPoint size;
    ofFbo canvas;

    void setup(ofPoint position_, ofPoint size_);
    void update(ofFbo & layerA, ofFbo & layerB, MainPanel & mainPanel);
    void display();
    void setColors(ofColor frontColor_, ofColor backColor, ofColor selectedColor_);


protected:
    bool blackout;
    ofTrueTypeFont font;
    string blackoutLabel;
    ofColor frontColor, backColor, selectedColor;

};

#endif // OUTPUT_H
