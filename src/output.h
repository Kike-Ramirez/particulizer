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
    void update(const ofFbo & layerA, const ofFbo & layerB, MainPanel & mainPanel);
    void display();

protected:
    bool blackout;
    ofTrueTypeFont font;
    string blackoutLabel;

};

#endif // OUTPUT_H
