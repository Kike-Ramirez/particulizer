#include "button.h"

Button::Button()
{

}

void Button::setup(ofPoint position_, ofPoint size_, int type_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);
    type = type_;
    val = 0;
    frontColor = ofColor(155);
    backColor = ofColor(0);
    selectedColor = ofColor(255);

}

void Button::update(float val_) {

    val = val_;

}

float Button::getVal() {

    return val;

}


void Button::display() {

    if (type == 0) {

        ofPushMatrix();
        ofTranslate(position.x, position.y);
        ofFill();
        ofSetColor(backColor);
        ofDrawRectangle(0, 0, size.x, size.y);
        ofSetColor(selectedColor);
        ofDrawRectangle(0, (1 - val) * size.y, size.x, val * size.y );
        ofSetColor(frontColor);
        ofNoFill();
        ofDrawRectangle(0, 0, size.x, size.y);
        ofPopMatrix();

    }

    else if (type == 1) {


        ofPushMatrix();
        ofTranslate(position.x, position.y);
        ofFill();
        ofSetColor(backColor);
        ofDrawCircle(0, 0, size.x/2);
        ofSetColor(frontColor);
        ofNoFill();
        ofDrawCircle(0, 0, size.x/2);

        float angulo = ofMap(val, 0, 1, 0, 270) - 225;
        ofRotate(angulo);
        ofTranslate(size.x / 2 * 0.4, 0);
        ofFill();
        ofSetColor(selectedColor);
        ofDrawLine(0, 0, size.x / 2 * 0.5, 0);
        ofPopMatrix();

    }

    else if (type == 2) {

        ofPushMatrix();
        ofTranslate(position.x, position.y);
        ofFill();
        ofSetColor(backColor);
        ofDrawRectangle(0, 0, size.x, size.y);
        float alpha = ofMap(val, 0, 1, 0, 255);
        ofSetColor(selectedColor, alpha);
        ofDrawRectangle(0.05 * size.x, 0.05 * size.y, 0.9 * size.x, 0.9 * size.y );
        ofNoFill();
        ofSetColor(frontColor);
        ofDrawRectangle(0, 0, size.x, size.y);
        ofPopMatrix();

    }

    if (type == 3) {

        ofPushMatrix();
        ofTranslate(position.x, position.y);
        ofFill();
        ofSetColor(backColor);
        ofDrawRectangle(0, 0, size.x, size.y);
        float mappedVal = ofMap(val, 0, 1, 0, 0.9);
        ofSetColor(selectedColor, 100);
        ofDrawRectangle(0, 0, mappedVal * size.x, size.y );
        ofSetColor(frontColor);
        ofDrawRectangle(mappedVal * size.x, 0, 0.1 * size.x, size.y);
        ofNoFill();
        ofDrawRectangle(0, 0, size.x, size.y);
        ofPopMatrix();

    }

}

void Button::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor = frontColor_;
    backColor = backColor_;
    selectedColor = selectedColor_;

}
