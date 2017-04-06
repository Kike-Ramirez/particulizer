#ifndef OUTPUT_H
#define OUTPUT_H

#include "ofMain.h"

class Output
{
public:
    Output();


    ofPoint position;
    ofPoint size;
    ofFbo canvas;

    void setup(ofPoint position_, ofPoint size_);
    void update(float alpha, const ofFbo & layerA, const ofFbo & layerB);
    void display();


};

#endif // OUTPUT_H
