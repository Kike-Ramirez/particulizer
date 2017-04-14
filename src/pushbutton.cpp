#include "pushbutton.h"

PushButton::PushButton()
{

}

void PushButton::setup(ofPoint position_, ofPoint size_, int type_) {

    font.load("coolvetica.ttf", 8, true, true);

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);
    type = type_;

    label = "label - label";

    frontColor = ofColor(155);
    backColor = ofColor(0);
    selectedColor = ofColor(255);

    val = 0;
    lastVal_ = 0;


}

void PushButton::update(float val_) {

    if (type == 0) {

        val = val_;

    }

    else if (type == 1) {

        if (val_ == 1 && lastVal_ == 0) {

            if (val == 1) val = 0;
            else val = 1;

        }

        lastVal_ = val_;

    }

}

void PushButton::display() {

    ofPushMatrix();
    ofTranslate(position.x, position.y);
    ofFill();
    ofSetColor(backColor);
    ofDrawRectangle(0, 0, size.x, size.y);

    float alpha = ofMap(val, 0, 1, 0, 255);
    ofSetColor(selectedColor, alpha);
    ofDrawRectangle(0, 0, size.x, size.y);

    ofNoFill();
    ofSetColor(frontColor);
    ofDrawRectangle(0, 0, size.x, size.y);

    ofColor colorLabel;
    colorLabel.set(selectedColor);
    colorLabel.setBrightness(255*(1-val));
    ofSetColor(colorLabel);
    font.drawString(label, 0.5 * (size.x - font.stringWidth(label)), 0.5 * (size.y));
    ofPopMatrix();

}

void PushButton::setFont(const ofTrueTypeFont & font_, int size_) {

    font = font_;

}

void PushButton::setLabel(const string & label_) {

    label = label_;

}

float PushButton::getVal() {

    return val;
}

void PushButton::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor = frontColor_;
    backColor = backColor_;
    selectedColor = selectedColor_;

}
