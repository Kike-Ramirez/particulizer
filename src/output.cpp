#include "output.h"

Output::Output()
{


}

void Output::setup(ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);

    canvas.allocate(1024, 768);

    blackout = false;

    font.load("coolvetica.ttf", 20, true, true);

    blackoutLabel = "BLACKOUT";
}

void Output::update(ofFbo &layerA, ofFbo &layerB, MainPanel &mainPanel) {

    float alpha = mainPanel.alphaMain.getVal();

    if (mainPanel.pushes[0].getVal() == 1) blackout = true;
    else blackout = false;

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


    if (! blackout) {
        ofPushMatrix();
        ofTranslate(position);
        ofSetColor(255);
        canvas.draw(0.05 * size.x, 0.05 * size.y, size.x * 0.9, size.y * 0.9);
        ofPopMatrix();
    }

    else {
        ofPushMatrix();
        ofTranslate(position);
        ofSetColor(0);
        ofFill();
        ofDrawRectangle(0.05 * size.x, 0.05 * size.y, size.x * 0.9, size.y * 0.9);
        ofSetColor(255, 0, 0);
        ofTranslate(0.5 * (size.x - font.stringWidth(blackoutLabel)), 0.5 * (size.y));
        font.drawString("Blackout", 0, 0);
        ofNoFill();
        ofPopMatrix();
    }

}

