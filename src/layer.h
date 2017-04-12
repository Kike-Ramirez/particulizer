#ifndef LAYER_H
#define LAYER_H

#include "ofMain.h"
#include "button.h"
#include "pushbutton.h"
#include "nanokontrol2.h"

class Layer
{
public:

    ofPoint position;
    ofPoint size;
    ofFbo canvas;
    float alpha;
    ofColor frontColor, backColor, selectedColor;
    vector<Button> buttons;
    vector<PushButton> midButtons;

    Layer();

    void setup(ofPoint position_, ofPoint size_);
    void update(const ofFbo & effectCanvas_, NanoKontrol2 & nano);

    void display();
    void select();
    void unselect();
    bool isSelected();
    void setAlpha(float alpha_);
    void setColors(ofColor frontColor_, ofColor backColor, ofColor selectedColor_);

private:
    bool selected;

};

#endif // LAYER_H
