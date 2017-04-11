#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "ofMain.h"
#include "nanokontrol2.h"

class PushButton
{
public:
    PushButton();

    ofPoint position;
    ofPoint size;
    ofColor frontColor;
    ofColor backColor;
    float val, lastVal_;
    string label;
    ofTrueTypeFont font;
    int type;

    void setup(ofPoint position_, ofPoint size_, int type_);
    void update(float val_);
    void display();
    void setFont(const ofTrueTypeFont & font_, int size_);
    void setLabel(const string & label_);
    float getVal();

};

#endif // PUSHBUTTON_H
