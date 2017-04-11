#ifndef MAINPANEL_H
#define MAINPANEL_H

#include "ofMain.h"
#include "nanokontrol2.h"
#include "pushbutton.h"
#include "button.h"

class MainPanel
{

public:

    ofPoint position;
    ofPoint size;
    vector<PushButton> pushes;
    Button alphaMain;
    Button mainSlider;
    ofColor frontColor;
    ofColor backColor;

    MainPanel();

    void setup(ofPoint position_, ofPoint size_);
    void update(NanoKontrol2 &nano_);
    void display();
    void setFrontColor(ofColor color_);
    void setBackColor(ofColor color_);


};

#endif // MAINPANEL_H
