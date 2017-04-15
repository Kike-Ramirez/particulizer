#include "modulframerate.h"

ModulFrameRate::ModulFrameRate()
{

}

void ModulFrameRate::setup(ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);

    frontColor = ofColor(155);
    backColor = ofColor(0);
    selectedColor = ofColor(255);

}

void ModulFrameRate::display() {

    ofPushMatrix();
    ofTranslate(position.x, position.y);
    ofSetColor(backColor);
    ofFill();
    ofDrawRectangle(0.05 * size.x, 0.05 * size.y, 0.9 * size.x, 0.9 * size.y);
    ofFill();
    ofSetColor(selectedColor);
    float level = ofMap(ofGetFrameRate(), 0, 60, 0.9 * size.y, 0);
    ofDrawRectangle(0.05 * size.x, 0.05 * size.y + level, 0.9 * size.x, 0.9 * size.y - level);
    ofSetColor(frontColor);
    ofDrawBitmapString(int(ofGetFrameRate()), 0.05 * size.x + 3, 0.05 * size.y + level + 12);
    ofNoFill();
    ofDrawRectangle(0.05 * size.x, 0.05 * size.y, 0.9 * size.x, 0.9 * size.y);
    ofPopMatrix();

}

void ModulFrameRate::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor = frontColor_;
    backColor = backColor_;
    selectedColor = selectedColor_;

}
