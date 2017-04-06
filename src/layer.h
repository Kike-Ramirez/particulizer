#ifndef LAYER_H
#define LAYER_H

#include "ofMain.h"

class Layer
{
public:

    ofPoint position;
    ofPoint size;
    bool selected;
    ofFbo canvasLayer;
    float alpha;

    Layer();

    void setup(ofPoint position_, ofPoint size_);
    void update(const ofFbo & effectCanvas_);
    void display();
    void select();
    void unselect();
    void setAlpha(float alpha_);

};

#endif // LAYER_H
