#include "button.h"

Button::Button()
{

}

void Button::setup(ofPoint position_, ofPoint size_, int type_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);
    type = type_;
    val = 0;
    colorFront = ofColor(255);
    colorBack = ofColor(0);

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
        ofSetColor(colorBack);
        ofDrawRectangle(0, 0, size.x, size.y);
        ofSetColor(colorFront);
        ofDrawRectangle(0.05 * size.x, (0.05 + 0.9 * (1 - val)) * size.y, 0.9 * size.x, 0.9 * val * size.y );
        ofNoFill();
        ofDrawRectangle(0, 0, size.x, size.y);
        ofPopMatrix();

    }

    else if (type == 1) {


        ofPushMatrix();
        ofTranslate(position.x, position.y);
        ofFill();
        ofSetColor(colorBack);
        ofDrawCircle(0, 0, size.x/2);
        ofSetColor(colorFront);
        ofNoFill();
        ofDrawCircle(0, 0, size.x/2);

        float angulo = ofMap(val, 0, 1, 0, 270) - 225;
        ofRotate(angulo);
        ofTranslate(size.x / 2 * 0.6, 0);
        ofFill();
        ofDrawLine(0, 0, size.x / 2 * 0.3, 0);
        ofPopMatrix();

    }

    else if (type == 2) {

        ofPushMatrix();
        ofTranslate(position.x, position.y);
        ofFill();
        ofSetColor(colorBack);
        ofDrawRectangle(0, 0, size.x, size.y);
        float alpha = ofMap(val, 0, 1, 0, 255);
        ofSetColor(colorFront, alpha);
        ofDrawRectangle(0.05 * size.x, 0.05 * size.y, 0.9 * size.x, 0.9 * size.y );
        ofNoFill();
        ofSetColor(colorFront);
        ofDrawRectangle(0, 0, size.x, size.y);
        ofPopMatrix();

    }

}
