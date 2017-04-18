#include "flocking.h"

Flocking::Flocking()
{

}

void Flocking::postSetup() {


}

void Flocking::update(NanoPanel &nanoPanel, AudioInput &AudioInput) {


}

void Flocking::drawOutput() {

    float posX = 100.0 * sin( ofGetElapsedTimeMillis() * 0.01 );

    effectCanvas.begin();
    ofPushMatrix();
    ofTranslate(effectCanvas.getWidth()/2, effectCanvas.getHeight()/2, 100);
    ofBackground(0);
    ofSetColor(255, 0, 0);
    ofFill();
    ofDrawRectangle(posX, 0, 100, 200);
    ofNoFill();
    ofSetColor(255);
    ofDrawRectangle(-10, -posX, 120, 210);
    ofPopMatrix();
    ofDrawBitmapString( ofGetFrameRate(), 50, 50 );
    effectCanvas.end();

    smallCanvas.begin();
    ofBackground(0);
    ofSetColor(255);
    effectCanvas.draw(0,0,smallCanvas.getWidth(), smallCanvas.getHeight());
    smallCanvas.end();
}
