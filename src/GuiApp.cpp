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
    frontColor = ofColor(0, 20, 229);
    backColor = ofColor(10);
    selectedColor = ofColor(153, 161, 255);

    // launch the app //
        mFullscreen = false;

    // Initialize fbo layers

        layerA.setup(ofPoint(0, 0), ofPoint(0.25 * ofGetWidth(), 0.4 * ofGetHeight()));
        layerA.setColors(frontColor, backColor, selectedColor);
        layerB.setup(ofPoint(0, 0.5 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.4 * ofGetHeight()));
        layerB.setColors(frontColor, backColor, selectedColor);
        layerB.setAlpha(1);

        output.setup(ofPoint(0.5 * ofGetWidth(), 0), ofPoint(0.5 * ofGetWidth(), 0.5 * ofGetHeight()));
        output.setColors(frontColor, backColor, selectedColor);

        ofSetCircleResolution(200);

        nano.setup();

        numEffects = 12;

        int pos = 0;
        LightHair sequence0;
        string name = "Light - Hair Sequence\nAprox. Dur: 250''\nKike Ramirez - 2017";
        sequence0.setup(ofPoint(0.25 * ofGetWidth(), pos * 0.15 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.15 * ofGetHeight()), name );
        sequence0.setColors(frontColor, backColor, selectedColor);
        effects.push_back(std::make_unique<LightHair>(sequence0));

        pos = 1;
        Circle_Dancing sequence1;
        name = "Circle Dancing Sequence\nAprox. Dur: 300''\nKike Ramirez - 2017";
        sequence1.setup(ofPoint(0.25 * ofGetWidth(), pos * 0.15 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.15 * ofGetHeight()), name );
        sequence1.setColors(frontColor, backColor, selectedColor);
        effects.push_back(std::make_unique<Circle_Dancing>(sequence1));

        pos = 2;
        Moire sequence2;
        name = "Moire Sequence\nAprox. Dur: 300''\nKike Ramirez - 2017";
        sequence2.setup(ofPoint(0.25 * ofGetWidth(), pos * 0.15 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.15 * ofGetHeight()), name );
        sequence2.setColors(frontColor, backColor, selectedColor);
        effects.push_back(std::make_unique<Moire>(sequence2));

        pos = 3;
        Flocking sequence3;
        name = "Moire Sequence\nAprox. Dur: 300''\nKike Ramirez - 2017";
        sequence3.setup(ofPoint(0.25 * ofGetWidth(), pos * 0.15 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.15 * ofGetHeight()), name );
        sequence3.setColors(frontColor, backColor, selectedColor);
        effects.push_back(std::make_unique<Flocking>(sequence3));

        offSetDelta = 0;
        offSet = 0;

        ofTrueTypeFont::setGlobalDpi(72);

        coolvetica.load("Aquila Sans.ttf", 10, true, true);
        coolvetica.setLineHeight(18.0f);

        audioInput.setup(this, ofPoint(0.5 * ofGetWidth(), 0.5 * ofGetHeight()), ofPoint(0.2 * ofGetWidth(), 0.3 * ofGetHeight()));
        audioInput.setColors(frontColor, backColor, selectedColor);

        mainPanel.setup(ofPoint(0, 0.9 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.1 * ofGetHeight()));
        mainPanel.setColors(frontColor, backColor, selectedColor);

        modulFrameRate.setup(ofPoint(0.97 * ofGetWidth(), 0.8 * ofGetHeight()), ofPoint(0.02 * ofGetWidth(), 0.19 * ofGetHeight()));
        modulFrameRate.setColors(frontColor, backColor, selectedColor);

        nanoPanel.setup(ofPoint(0.5 * ofGetWidth(), 0.8 * ofGetHeight()), ofPoint(0.47 * ofGetWidth(), 0.2 * ofGetHeight()));
        nanoPanel.setColors(frontColor, backColor, selectedColor);

        effectPanel.setup(ofPoint(0.7 * ofGetWidth(), 0.5 * ofGetHeight()), ofPoint(0.3* ofGetWidth(), 0.3 * ofGetHeight()));
        effectPanel.setColors(frontColor, backColor, selectedColor);


}

void GuiApp::update(){

    audioInput.update(nano);

    mainPanel.update(nano);
    nanoPanel.update(nano);

    layerA.setAlpha(mainPanel.mainSlider.getVal());
    layerA.update(nano);

    layerB.setAlpha(1 - mainPanel.mainSlider.getVal());
    layerB.update(nano);




}

void GuiApp::draw(){

    // FAKE customization
    ofBackground(backColor);

    // Effects

    effectPanel.display();

    for (int i = 0; i < effects.size(); i++) {
        effects[i]->update(nanoPanel,audioInput);
        effects[i]->drawDisplay(coolvetica);
        if (effects[i]->isActive()) {
            effectPanel.display(effects[i]->effectCanvas);
        }
    }


    // Layers Area

    // Layer A

    for (int i = 0; i < effects.size(); i++) {

        if (effects[i]->assigned == 1) layerA.displayCanvas(effects[i]->effectCanvas);
        else if (effects[i]->assigned == 2) layerB.displayCanvas(effects[i]->effectCanvas);

    }

    layerA.display();
    layerB.display();

    mainPanel.display();

    nanoPanel.display();

    modulFrameRate.display();

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

        if (offSet >= -numEffects * effects[0]->size.y + ofGetHeight()) {
            offSet -= 10;
            for (int i = 0; i < effects.size(); i++) {

                effects[i]->setOffset(offSet);

            }
        }
    }

    else if (key == OF_KEY_DOWN) {

        if (offSet <= 0) {
            offSet += 10;

            for (int i = 0; i < effects.size(); i++) {

                effects[i]->setOffset(offSet);

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

        if (x >= effects[i]->position.x && x<=effects[i]->position.x + effects[i]->size.x &&
                y >= effects[i]->position.y + effects[i]->getOffset() &&
                y<= effects[i]->position.y + effects[i]->getOffset() + effects[i]->size.y) {

            effects[i]->select();

            if (layerA.isSelected()) {

                for (int j = 0; j < effects.size(); j++) {

                    if (j!=i && effects[j]->assigned == 1) effects[j]->assign(0);
                }
                effects[i]->assign(1);
            }

            if (layerB.isSelected()) {
                for (int j = 0; j < effects.size(); j++) {

                    if (j!=i && effects[j]->assigned == 2) effects[j]->assign(0);
                }
                effects[i]->assign(2);
            }
        }

        else effects[i]->unselect();

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

    if (x >= audioInput.position.x && x<=audioInput.position.x + audioInput.size.x &&
            y >= audioInput.position.y && y <= audioInput.position.y + audioInput.size.y) {

        audioInput.mousePressed(x, y, button);

    }

    else audioInput.selected = false;


}



void GuiApp::mouseReleased(int x, int y, int button) {


}

void GuiApp::audioReceived(float* input, int bufferSize, int nChannels) {

    audioInput.audioReceived(input, bufferSize, nChannels);

}

void GuiApp::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor = frontColor_;
    backColor = backColor_;
    selectedColor = selectedColor_;

}
