#include "effect_template.h"

Effect_Template::Effect_Template()
{

}

void Effect_Template::setup(ofPoint _position, ofPoint _size, vector<string> _nanoKorgTexts, string name_){

    position.set(_position.x, _position.y);
    size.set(_size.x, _size.y);

    for (int i = 0; i < _nanoKorgTexts.size(); i++) {

        nanoKorgTexts.push_back(_nanoKorgTexts[i]);

    }

    name = name_;
    selected = false;
    assigned = 0;
    offSet = 0;

    // Canvas
    effectCanvas.allocate(1024, 768);                 // Canvas to render the effect
    smallCanvas.allocate(0.7 * size.y * 16.0 / 9.0, 0.7 * size.y); // Small canvas for Effect Layer Preview

    // Parameters for live output
    speed = 0;                        // Speed variable (0 - 1)
    audioLevel = 0;                   // Main audio Level

    for (int i = 0; i < 3; i++) {

        audioFiltersLevel.push_back(0);
    }

    frontColor = ofColor(155);
    backColor = ofColor(0);
    selectedColor = ofColor(255);

    drawOutput();

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

bool Effect_Template::isActive(){

    return selected;

}

bool Effect_Template::isAssigned(){

    if (assigned > 0) return true;
    else return false;

}

void Effect_Template::assign(int id){

    assigned = id;

}

void Effect_Template::drawDisplay(const ofTrueTypeFont & coolvetica_) {

    ofPushMatrix();
    ofTranslate(position.x, position.y + offSet);
    ofSetColor(backColor);
    ofFill();
    ofRect(0, 0, size.x, size. y);
    ofSetColor(frontColor);
    ofNoFill();
    ofRect(0, 0, size.x, size.y);


    if (selected) {

        ofSetColor(selectedColor);
        ofNoFill();
        ofSetLineWidth(1);
        ofRect(0.03 * size.x, 0.03 * size.y, 0.94 * size.x, 0.94 * size. y);
        ofSetLineWidth(1);

    }

    ofSetColor(255);
    ofNoFill();
    smallCanvas.draw(0.05 * size.x, 0.15 * size.y);

    ofSetColor(frontColor);
    ofDrawRectangle(0.05 * size.x, 0.15 * size.y, smallCanvas.getWidth(), smallCanvas.getHeight());

    ofSetColor(frontColor);
    coolvetica_.drawString(name, 0.08 * size.x + smallCanvas.getWidth(), 0.15 * size.y + 11);

    ofPopMatrix();

    if (selected || isAssigned()) drawOutput();

}

void Effect_Template::drawOutput(){

    float radio = ofMap(sin( ofGetFrameNum() / 60.0), -1, 1, 0, effectCanvas.getHeight()/2);

    ofSetColor(255);

    effectCanvas.begin();
    ofBackground(0);
    ofSetColor(255);
    ofFill();
    ofCircle(effectCanvas.getWidth() /2, effectCanvas.getHeight() / 2, radio/2, radio/2);
    ofSetColor(255, 0, 0);
    ofCircle(effectCanvas.getWidth() /2, effectCanvas.getHeight() / 2, radio/4, radio/4);
    ofSetColor(255);

    effectCanvas.end();

    smallCanvas.begin();
    ofBackground(0);
    effectCanvas.draw(0,0,smallCanvas.getWidth(), smallCanvas.getHeight());
    smallCanvas.end();

}

void Effect_Template::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor = frontColor_;
    backColor = backColor_;
    selectedColor = selectedColor_;

}
