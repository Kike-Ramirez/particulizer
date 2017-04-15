#include "lighthair.h"

LightHair::LightHair()
{


}

void LightHair::update() {

    speed = 360.0;


}

void LightHair::drawOutput() {

    float rotatePos = sin( ofGetElapsedTimeMillis() * 0.001 );

    effectCanvas.begin();
    ofPushMatrix();
    ofTranslate(effectCanvas.getWidth()/2, effectCanvas.getHeight()/2, 100);
    ofRotate(180 * rotatePos);
    ofBackground(0);
    ofSetColor(255);
    ofSetLineWidth(5);
    ofNoFill();
    points.draw();
    ofPopMatrix();
    ofDrawBitmapString( ofGetFrameRate(), 50, 50 );
    effectCanvas.end();

    smallCanvas.begin();
    ofBackground(0);
    ofSetColor(255);
    effectCanvas.draw(0,0,smallCanvas.getWidth(), smallCanvas.getHeight());
    smallCanvas.end();

}
