#include "effect_template.h"

Effect_Template::Effect_Template()
{

}

void Effect_Template::setup(ofPoint _position, ofPoint _size, ofxKorgNanoKontrol _nano, vector<string> _nanoKorgTexts){

    position.set(_position.x, _position.y);
    size.set(_size.x, _size.y);
    nano = _nano;

    for (int i = 0; i < _nanoKorgTexts.size(); i++) {

        nanoKorgTexts.push_back(_nanoKorgTexts[i]);

    }

    selected = false;
    offSet = 0;
    name = "FakeEffect_01";

    // Canvas
    effectCanvas.allocate(1024, 768);                 // Canvas to render the effect
    smallCanvas.allocate(0.7 * size.y * 16.0 / 9.0, 0.7 * size.y); // Small canvas for Effect Layer Preview

    // Parameters for live output
    speed = 0;                        // Speed variable (0 - 1)
    audioLevel = 0;                   // Main audio Level

    for (int i = 0; i < 3; i++) {

        audioFiltersLevel.push_back(0);
    }

    colorFront = ofColor(255);
    colorBack = ofColor(0);

}

void Effect_Template::update(){



}

void Effect_Template::setOffset(int _offSet){

    offSet = _offSet;
}

float Effect_Template::getOffset(){

    return offSet;
}


void Effect_Template::select(){

    selected = true;
}

void Effect_Template::unselect(){

    selected = false;
}

void Effect_Template::drawDisplay() {

    ofPushMatrix();
    ofTranslate(position.x, position.y + offSet);
    ofSetColor(120);
    ofFill();
    ofRect(0, 0, size.x, size. y);

    if (selected) {

        ofSetColor(255, 0, 0);
        ofNoFill();
        ofSetLineWidth(4);
        ofRect(0, 0, size.x, size. y);
        ofSetLineWidth(1);
    }

    smallCanvas.begin();
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString("hi!!", smallCanvas.getWidth() * 0.5, smallCanvas.getHeight() * 0.5);
    smallCanvas.end();

    smallCanvas.draw(0.05 * size.x, 0.15 * size.y);

    ofSetColor(0);
    ofDrawBitmapString(name, 0.08 * size.x + smallCanvas.getWidth(), 0.15 * size.y + 11);

    ofPopMatrix();

}

void Effect_Template::drawOutput(){

}
