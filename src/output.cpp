#include "output.h"

Output::Output()
{


}

void Output::setup(ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);

    canvas.allocate(1024, 768);

}

void Output::update(float alpha, const ofFbo & layerA, const ofFbo & layerB) {

    canvas.begin();
    ofBackground(0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255, 255.0 * alpha);
    layerA.draw(0, 0, canvas.getWidth(), canvas.getHeight());
    ofSetColor(255, 255.0 * (1.0 - alpha));
    layerB.draw(0,0, canvas.getWidth(), canvas.getHeight());
    ofDisableBlendMode();
    canvas.end();

}

void Output::display() {

    ofPushMatrix();
    ofTranslate(position);
    ofSetColor(255);
    canvas.draw(0.05 * size.x, 0.05 * size.y, size.x * 0.9, size.y * 0.9);
    ofPopMatrix();

}
