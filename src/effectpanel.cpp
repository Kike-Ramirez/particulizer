#include "effectpanel.h"

EffectPanel::EffectPanel()
{

}

void EffectPanel::setup(ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);
    backColor = ofColor(0);
    frontColor = ofColor(255);

}

void EffectPanel::display() {

    ofPushMatrix();
    ofTranslate(position.x + 0.05 * size.x, position.y + 0.05 * size.y);

    ofSetColor(backColor);
    ofFill();
    ofDrawRectangle(0, 0, 0.9 * size.x, 0.9 * size.y);
    ofNoFill();
    ofSetColor(frontColor);
    ofDrawRectangle(0, 0, 0.9 * size.x, 0.9 * size.y);
    ofPopMatrix();

}

void EffectPanel::display(const ofFbo &canvas_) {

    ofPushMatrix();
    ofTranslate(position.x + 0.05 * size.x, position.y + 0.05 * size.y);

    ofSetColor(0);

    float distX = (0.9 * size.x - 0.9 * size.y * Constants::ASPECT_RATIO) * 0.5;
    ofDrawRectangle(0, 0, 0.9 * size.x, 0.9 * size.y);
    ofSetColor(255);
    canvas_.draw(distX, 0, 0.9 * size.y * Constants::ASPECT_RATIO,  0.9 * size.y);
    ofSetColor(frontColor);
    ofDrawRectangle(0, 0, 0.9 * size.x, 0.9 * size.y);
    ofPopMatrix();

}

void EffectPanel::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor = frontColor_;
    backColor = backColor_;
    selectedColor = selectedColor_;

}
