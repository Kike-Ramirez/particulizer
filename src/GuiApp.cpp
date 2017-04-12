/*
 * GuiApp.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: arturo
 */

#include "GuiApp.h"

void GuiApp::setup(){

    ofSetVerticalSync(true);

    // Set colorset
    frontColor = ofColor(155);
    backColor = ofColor(0);
    selectedColor = ofColor(255);

    // launch the app //
        mFullscreen = false;

    // Initialize fbo layers

        layerA.setup(ofPoint(0, 0), ofPoint(0.25 * ofGetWidth(), 0.4 * ofGetHeight()));
        layerB.setup(ofPoint(0, 0.5 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.4 * ofGetHeight()));
        layerB.setAlpha(1);

        output.setup(ofPoint(0.5 * ofGetWidth(), 0), ofPoint(0.5 * ofGetWidth(), 0.5 * ofGetHeight()));

        ofSetCircleResolution(200);

        nano.setup();

        vector<string> textos;
        textos.push_back("1");
        textos.push_back("2a");
        textos.push_back("3b");

        numEffects = 12;

        for (int i = 0; i < numEffects; i++) {

            Effect_Template effect;
            string name = "Efecto #" + ofToString(i);
            effect.setup(ofPoint(0.25 * ofGetWidth(), i * 0.15 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.15 * ofGetHeight()), textos, name );

            effects.push_back(effect);
        }

        offSetDelta = 0;
        offSet = 0;

        ofTrueTypeFont::setGlobalDpi(72);

        coolvetica.load("coolvetica.ttf", 10, true, true);
        coolvetica.setLineHeight(18.0f);

        audioInput.setup(this, ofPoint(0.5 * ofGetWidth(), 0.5 * ofGetHeight()), ofPoint(0.2 * ofGetWidth(), 0.3 * ofGetHeight()));


        mainPanel.setup(ofPoint(0, 0.9 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.1 * ofGetHeight()));

        nanoPanel.setup(ofPoint(0.5 * ofGetWidth(), 0.8 * ofGetHeight()), ofPoint(0.5 * ofGetWidth(), 0.2 * ofGetHeight()));

        effectPanel.setup(ofPoint(0.7 * ofGetWidth(), 0.5 * ofGetHeight()), ofPoint(0.3* ofGetWidth(), 0.3 * ofGetHeight()));


}

void GuiApp::update(){

    audioInput.update(nano);

    mainPanel.update(nano);
    nanoPanel.update(nano);

    layerA.setAlpha(mainPanel.mainSlider.getVal());
    layerB.setAlpha(1 - mainPanel.mainSlider.getVal());



}

void GuiApp::draw(){

    // FAKE customization
    ofBackground(backColor);

    // Effects

    effectPanel.display();

    for (int i = 0; i < effects.size(); i++) {
        effects[i].drawDisplay(coolvetica);
        if (effects[i].isActive()) {
            effectPanel.display(effects[i].effectCanvas);
        }
    }

    // Layers Area

    // Layer A

    for (int i = 0; i < effects.size(); i++) {

        if (effects[i].assigned == 1) layerA.update(effects[i].effectCanvas, nano);
        else if (effects[i].assigned == 2) layerB.update(effects[i].effectCanvas, nano);

    }
    //void audioReceived(float* input, int bufferSize, int nChannels);



    layerA.display();
    layerB.display();

    mainPanel.display();

    nanoPanel.display();

    // Main Controls
    ofSetColor(125);
    ofFill();
    // ofRect(0.5 * ofGetWidth(), 0.5 * ofGetHeight(), 0.2 * ofGetWidth(), 0.3 * ofGetHeight());
    ofSetColor(255);

    audioInput.display(coolvetica);

    // Output Canvas
    ofSetColor(100);
    //ofRect(0.5 * ofGetWidth(), 0.0, 0.5 * ofGetWidth(), 0.5 * ofGetHeight());
    ofSetColor(255);

    output.update(layerA.canvas, layerB.canvas, mainPanel);

    output.display();

    // NanoKorg Controls
    ofSetColor(100);
    // ofRect(0.5 * ofGetWidth(), 0.8 * ofGetHeight(), 0.5 * ofGetWidth(), 0.2 * ofGetHeight());
    ofSetColor(255);



}


void GuiApp::keyPressed(int key)
{
    if (key == OF_KEY_UP) {

        if (offSet >= -numEffects * effects[0].size.y + ofGetHeight()) {
            offSet -= 10;
            for (int i = 0; i < effects.size(); i++) {

                effects[i].setOffset(offSet);

            }
        }
    }

    else if (key == OF_KEY_DOWN) {

        if (offSet <= 0) {
            offSet += 10;

            for (int i = 0; i < effects.size(); i++) {

                effects[i].setOffset(offSet);

            }

        }
    }

}


void GuiApp::exit() {

}


void GuiApp::mouseDragged(int x, int y, int button) {


}


void GuiApp::mousePressed(int x, int y, int button) {

    for (int i = 0; i < effects.size(); i++) {

        if (x >= effects[i].position.x && x<=effects[i].position.x + effects[i].size.x &&
                y >= effects[i].position.y + effects[i].getOffset() &&
                y<= effects[i].position.y + effects[i].getOffset() + effects[i].size.y) {

            effects[i].select();

            if (layerA.isSelected()) {

                for (int j = 0; j < effects.size(); j++) {

                    if (j!=i && effects[j].isAssigned() == 1) effects[j].assign(0);
                }
                effects[i].assign(1);
                layerA.unselect();
            }

            if (layerB.isSelected()) {
                for (int j = 0; j < effects.size(); j++) {

                    if (j!=i && effects[j].isAssigned() == 2) effects[j].assign(0);
                }
                effects[i].assign(2);
                layerB.unselect();
            }
        }

        else effects[i].unselect();

    }

    if (x >= layerA.position.x && x<=layerA.position.x + layerA.size.x &&
            y >= layerA.position.y && y <= layerA.position.y + layerA.size.y) {

        layerA.select();
        layerB.unselect();

    }

    else if (x >= layerB.position.x && x<=layerB.position.x + layerB.size.x &&
            y >= layerB.position.y && y <= layerB.position.y + layerB.size.y) {

        layerB.select();
        layerA.unselect();

    }

    else {

        if (layerA.isSelected()) layerA.unselect();
        else if (layerB.isSelected()) layerB.unselect();
    }

}



void GuiApp::mouseReleased(int x, int y, int button) {


}

void GuiApp::audioReceived(float* input, int bufferSize, int nChannels) {

    audioInput.audioReceived(input, bufferSize, nChannels);

};
