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
    ofPopMatrix();

}

void EffectPanel::display(const ofFbo &canvas_) {

    ofPushMatrix();
    ofTranslate(position.x + 0.05 * size.x, position.y + 0.05 * size.y);

    ofSetColor(backColor);
    ofDrawRectangle(0, 0, 0.9 * size.x, 0.9 * size.y);
    canvas_.draw(0, 0, 0.9 * size.x, 0.9 * size.y);
    ofPopMatrix();

}
