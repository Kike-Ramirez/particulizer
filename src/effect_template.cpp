#include "effect_template.h"

Effect_Template::Effect_Template()
{

}

void Effect_Template::setup(ofPoint _position, ofPoint _size, string name_){

    position.set(_position.x, _position.y);
    size.set(_size.x, _size.y);

    name = name_;
    selected = false;
    assigned = 0;
    offSet = 0;

    // Canvas
    effectCanvas.allocate(Constants::OUTPUT_WIDTH, Constants::OUTPUT_HEIGHT);                 // Canvas to render the effect
    smallCanvas.allocate(0.7 * size.y * Constants::ASPECT_RATIO, 0.7 * size.y); // Small canvas for Effect Layer Preview


    // Customization
    frontColor = ofColor(155);
    backColor = ofColor(0);
    selectedColor = ofColor(255);

    float speed = 0;

    int numPoints = 50;
    float spread = 100;

    for (int i = 0; i < numPoints; i++) {

        points.addVertex( ofVec3f(ofRandom(-spread, spread), ofRandom(-spread, spread),ofRandom(-spread, spread)));

    }

    // Variables for live output


    cameraPosition = ofVec3f(0,0,0);
    cameraTarget = ofVec3f(0,0,0);

    timeCamera = 0;
    timeParticles = 0;

    for (int i = 0; i < 5; i++) {

        timePanel.push_back(0);
        timePanelLocal.push_back(0);
        timePanelAnt.push_back(0);
        cameraPanel.push_back(0);
        cameraPanelLocal.push_back(0);
        cameraPanelAnt.push_back(0);
        particlePanel.push_back(0);
        particlePanelLocal.push_back(0);
        particlePanelAnt.push_back(0);
        shaderPanel.push_back(0);
        shaderPanelLocal.push_back(0);
        shaderPanelAnt.push_back(0);

    }

    postSetup();

    // Draw Output
    drawOutput();

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
    ofDrawRectangle(0, 0, size.x, size. y);
    ofSetColor(frontColor);
    ofNoFill();
    ofDrawRectangle(0, 0, size.x, size.y);


    if (selected) {

        ofSetColor(selectedColor);
        ofNoFill();
        ofSetLineWidth(1);
        ofDrawRectangle(0.03 * size.x, 0.03 * size.y, 0.94 * size.x, 0.94 * size. y);
        ofSetLineWidth(1);

    }

    ofSetColor(255);
    smallCanvas.draw(0.05 * size.x, 0.15 * size.y);

    ofSetColor(frontColor);
    ofNoFill();
    ofDrawRectangle(0.05 * size.x, 0.15 * size.y, smallCanvas.getWidth(), smallCanvas.getHeight());

    ofSetColor(255);
    coolvetica_.drawString(name, 0.08 * size.x + smallCanvas.getWidth(), 0.15 * size.y + 11);

    ofPopMatrix();

    if (selected || isAssigned()) {
        this->drawOutput();
    }

}


void Effect_Template::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor = frontColor_;
    backColor = backColor_;
    selectedColor = selectedColor_;

}


void Effect_Template::setName(string name_)
{
    name = name_;
}
