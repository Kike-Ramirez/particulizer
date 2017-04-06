#ifndef LAYER_H
#define LAYER_H

#include "ofMain.h"

class Layer
{
public:

    ofPoint position;
    ofPoint size;
    ofFbo canvas;
    float alpha;

    Layer();

    void setup(ofPoint position_, ofPoint size_);
    void update(const ofFbo & effectCanvas_);
    void display();
    void select();
    void unselect();
    bool isSelected();
    void setAlpha(float alpha_);

private:
    bool selected;

};

#endif // LAYER_H
