#include "circle_dancing.h"

Circle_Dancing::Circle_Dancing()
{

}

void Circle_Dancing::update(NanoPanel &nanoPanel, AudioInput &audioInput) {



}

void Circle_Dancing::postSetup() {


}

void Circle_Dancing::drawOutput() {

    float posX = 100.0 * sin( ofGetElapsedTimeMillis() * 0.01 );

    effectCanvas.begin();
    ofPushMatrix();
    ofTranslate(effectCanvas.getWidth()/2, effectCanvas.getHeight()/2, 100);
    ofBackground(0);
    ofSetColor(255);
    ofSetLineWidth(5);
    ofNoFill();
    ofDrawCircle(posX, 0, 100);
    ofDrawCircle(-posX, 0, 100);
    ofPopMatrix();
    ofDrawBitmapString( ofGetFrameRate(), 50, 50 );
    effectCanvas.end();

    smallCanvas.begin();
    ofBackground(0);
    ofSetColor(255);
    effectCanvas.draw(0,0,smallCanvas.getWidth(), smallCanvas.getHeight());
    smallCanvas.end();

}
