#include "output.h"

Output::Output()
{


}

void Output::setup(ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);

    canvas.allocate(1280, 1024);

    blackout = false;

    font.load("coolvetica.ttf", 20, true, true);

    blackoutLabel = "BLACKOUT";

    frontColor = ofColor(155);
    backColor = ofColor(255);
    selectedColor = ofColor(255);

}

void Output::update(ofFbo &layerA, ofFbo &layerB, MainPanel &mainPanel) {

    float alphaOut = mainPanel.alphaMain.getVal();
    float alphaSlider = mainPanel.mainSlider.getVal();

    if (mainPanel.pushes[0].getVal() == 1) blackout = true;
    else blackout = false;

    if (! blackout) {
        canvas.begin();
        ofBackground(0);
        ofFill();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(255, 255.0 * alphaSlider * alphaOut);
        layerA.draw(0, 0, canvas.getWidth(), canvas.getHeight());
        ofSetColor(255, 255.0 * (1.0 - alphaSlider) * alphaOut);
        layerB.draw(0,0, canvas.getWidth(), canvas.getHeight());
        ofDisableBlendMode();
        canvas.end();
    }

    else {
        canvas.begin();
        ofBackground(0);
        canvas.end();

    }
}

void Output::display() {


    if (! blackout) {
        ofPushMatrix();
        ofTranslate(position);
        ofSetColor(255);
        float dist = (0.9 * size.x - 0.9 * size.y * 5.0 / 4.0 ) * 0.5;
        canvas.draw(0.05 * size.x + dist, 0.05 * size.y, size.y * 0.9 * 5.0 / 4.0, size.y * 0.9);
        ofSetColor(frontColor);
        ofNoFill();
        ofDrawRectangle(0.05 * size.x, 0.05 * size.y, size.x * 0.9, size.y * 0.9);
        ofPopMatrix();
    }

    else {
        ofPushMatrix();
        ofTranslate(position);
        ofSetColor(0);
        ofFill();
        ofDrawRectangle(0.05 * size.x, 0.05 * size.y, size.x * 0.9, size.y * 0.9);
        ofNoFill();
        ofSetColor(frontColor);
        ofDrawRectangle(0.05 * size.x, 0.05 * size.y, size.x * 0.9, size.y * 0.9);
        ofSetColor(selectedColor);
        ofTranslate(0.5 * (size.x - font.stringWidth(blackoutLabel)), 0.5 * (size.y));
        font.drawString("Blackout", 0, 0);
        ofPopMatrix();
    }

}

void Output::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor = frontColor_;
    backColor = backColor_;
    selectedColor = selectedColor_;

}
