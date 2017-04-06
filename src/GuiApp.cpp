/*
 * GuiApp.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: arturo
 */

#include "GuiApp.h"

void GuiApp::setup(){

    // instantiate and position the gui //
        gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );

    // add some components //
        gui->addTextInput("message", "# particuliZer v0.1 #");

        gui->addFRM();
        gui->addBreak();

    // add a folder to group a few components together //
        ofxDatGuiFolder* folder = gui->addFolder("Effect Parameter", ofColor::white);
        //folder->addTextInput("** input", "nested input field");
        folder->addSlider("** Radio", 0.0f, 1.0f, 0.5f);
        folder->addColorPicker("** Front Color", ofColor::fromHex(0xFFFFFF));
        folder->addColorPicker("** Back Color", ofColor::fromHex(0x000000));
    // let's have it open by default. note: call this only after you're done adding items //
        folder->expand();

        gui->addBreak();

    // add a couple range sliders //
        gui->addSlider("position X", 0.0f, 1.0f, 0.5f);
        gui->addSlider("position Y", 0.0f, 1.0f, 0.5f);

    // and a slider to adjust the gui opacity //
        gui->addSlider("datgui opacity", 0, 100, 100);

    // and a couple of simple buttons //
        gui->addToggle("toggle fullscreen", true);

    // adding the optional header allows you to drag the gui around //
        gui->addHeader(":: drag me to reposition ::");

    // adding the optional footer allows you to collapse/expand the gui //
        gui->addFooter();

    // once the gui has been assembled, register callbacks to listen for component specific events //
        gui->onButtonEvent(this, &GuiApp::onButtonEvent);
        gui->onToggleEvent(this, &GuiApp::onToggleEvent);
        gui->onSliderEvent(this, &GuiApp::onSliderEvent);
        gui->onColorPickerEvent(this, &GuiApp::onColorPickerEvent);

        gui->setOpacity(gui->getSlider("datgui opacity")->getScale());
        gui->setLabelAlignment(ofxDatGuiAlignment::CENTER);

    // finally let's load up the stock themes, press spacebar to cycle through them //
        themes = {  new ofxDatGuiTheme(true),
                    new ofxDatGuiThemeSmoke(),
                    new ofxDatGuiThemeWireframe(),
                    new ofxDatGuiThemeMidnight(),
                    new ofxDatGuiThemeAqua(),
                    new ofxDatGuiThemeCharcoal(),
                    new ofxDatGuiThemeAutumn(),
                    new ofxDatGuiThemeCandy()};
        tIndex = 0;

    // launch the app //
        mFullscreen = false;
        refreshWindow();

    // Initialize fbo layers

        layerA.setup(ofPoint(0, 0), ofPoint(0.25 * ofGetWidth(), 0.4 * ofGetHeight()));
        layerB.setup(ofPoint(0, 0.5 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.4 * ofGetHeight()));
        layerB.setAlpha(1);

        output.setup(ofPoint(0.5 * ofGetWidth(), 0), ofPoint(0.5 * ofGetWidth(), 0.5 * ofGetHeight()));

        ofSetCircleResolution(200);

        nano.setup(true);
        ofAddListener(nano.sceneButtonPressed, this, &GuiApp::sceneButtonPressed);

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

        coolvetica.load("coolvetica.ttf", 14, true, true);
        coolvetica.setLineHeight(18.0f);
        coolvetica.setLetterSpacing(1.037);

}

void GuiApp::update(){


    layerA.setAlpha(nano.getVal(0) / 127.0);
    layerB.setAlpha(1 - nano.getVal(0) / 127.0);
}

void GuiApp::draw(){

    // FAKE customization
    ofBackground(150);

    // Effects

    for (int i = 0; i < effects.size(); i++) {
        effects[i].drawDisplay(coolvetica);
    }

    // Layers Area

    // Layer A

    for (int i = 0; i < effects.size(); i++) {

        if (effects[i].assigned == 1) layerA.update(effects[i].effectCanvas);
        else if (effects[i].assigned == 2) layerB.update(effects[i].effectCanvas);

    }



    layerA.display();
    layerB.display();

    // Main Controls
    ofSetColor(125);
    ofFill();
    ofRect(0.5 * ofGetWidth(), 0.5 * ofGetHeight(), 0.2 * ofGetWidth(), 0.3 * ofGetHeight());
    ofSetColor(255);


    // Output Canvas
    ofSetColor(100);
    ofRect(0.5 * ofGetWidth(), 0.0, 0.5 * ofGetWidth(), 0.5 * ofGetHeight());
    ofSetColor(255);

    output.update(nano.getVal(0) / 127.0, layerA.canvas, layerB.canvas);
    output.display();

    // NanoKorg Controls
    ofSetColor(100);
    ofRect(0.5 * ofGetWidth(), 0.8 * ofGetHeight(), 0.5 * ofGetWidth(), 0.2 * ofGetHeight());
    ofSetColor(255);

    ofPoint location = ofPoint(0.5 * ofGetWidth(), 0.8 * ofGetHeight());
    nano.showGui(true, false, location, coolvetica);


}

void GuiApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "onButtonEvent: " << e.target->getLabel() << endl;
}

void GuiApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
    if (e.target->is("toggle fullscreen")) toggleFullscreen();
    cout << "onToggleEvent: " << e.target->getLabel() << " " << e.checked << endl;
}

void GuiApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    cout << "onSliderEvent: " << e.target->getLabel() << " "; e.target->printValue();
    if (e.target->is("datgui opacity")) gui->setOpacity(e.scale);
}



void GuiApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    cout << "onColorPickerEvent: " << e.target->getLabel() << " " << e.target->getColor() << endl;
    ofSetBackgroundColor(e.color);
}

void GuiApp::keyPressed(int key)
{
    if (key == 'f') {
        toggleFullscreen();
    }

    else if (key == 32){
        tIndex = tIndex < themes.size()-1 ? tIndex+1 : 0;
        gui->setTheme(themes[tIndex]);
    }

    else if (key == OF_KEY_UP) {

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

void GuiApp::toggleFullscreen()
{
    cout << mFullscreen << endl;
    gui->getToggle("toggle fullscreen")->toggle();

    refreshWindow();
}

void GuiApp::refreshWindow()
{
    ofSetFullscreen(mFullscreen);
    mFullscreen = !mFullscreen;

    if (!mFullscreen) {
        ofSetWindowShape(1920, 1400);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1920/2), 0);
    }
}

//--------------------------------------------------------------
void GuiApp::sceneButtonPressed(int &e) {
    cout <<  "Scene button pressed" << endl;
}

void GuiApp::exit() {
    ofRemoveListener(nano.sceneButtonPressed, this, &GuiApp::sceneButtonPressed);
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
