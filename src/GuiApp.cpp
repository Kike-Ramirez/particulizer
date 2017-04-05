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
        layerA.allocate(0.23 * ofGetWidth(), 9.0 / 16.0 * 0.23 * ofGetWidth());
        layerB.allocate(0.23 * ofGetWidth(), 9.0 / 16.0 * 0.23 * ofGetWidth());

        effectCanvas.allocate(0.35 * ofGetWidth(), 9.0 / 16.0 * 0.35 * ofGetWidth());
        outputCanvas.allocate(0.45 * ofGetWidth(), 9.0 / 16.0 * 0.45 * ofGetWidth());

        output.allocate(0.5 * ofGetWidth(), 0.5 * ofGetHeight());

        ofSetColor(255);
        layerA.begin();

            ofBackground(0);
            ofDrawBitmapString("A", layerA.getWidth() * 0.5, layerA.getHeight() * 0.5);

        layerA.end();


        layerB.begin();

            ofBackground(0);
            ofDrawBitmapString("B", layerB.getWidth() * 0.5, layerB.getHeight() * 0.5);

        layerB.end();


        ofSetCircleResolution(200);

        nano.setup(true);
        ofAddListener(nano.sceneButtonPressed, this, &GuiApp::sceneButtonPressed);


}

void GuiApp::update(){

}

void GuiApp::draw(){

    // FAKE customization
    ofBackground(150);

    // Layers Area
    ofSetColor(125);
    ofRect(0, 0, 0.25 * ofGetWidth(), ofGetHeight());
    ofSetColor(255);

    // Layer A
    layerA.draw( 0.01 * ofGetWidth(), 0.05 * ofGetHeight() );

    // Layer B
    layerB.draw( 0.01 * ofGetWidth(), 0.55 * ofGetHeight() );

    // Effects

    // Main Controls
    ofSetColor(125);
    ofFill();
    ofRect(0.5 * ofGetWidth(), 0.5 * ofGetHeight(), 0.2 * ofGetWidth(), 0.3 * ofGetHeight());
    ofSetColor(255);

    // Effect Canvas

    ofSetColor(160, 0);
    ofFill();
    ofRect(0.7 * ofGetWidth(), 0.5 * ofGetHeight(), 0.3 * ofGetWidth(), 0.3 * ofGetHeight());
    ofSetColor(255);
    effectCanvas.begin();

    ofBackground(gui->getColorPicker("** Back Color")->getColor());
    ofSetColor(gui->getColorPicker("** Front Color")->getColor());
    ofDrawCircle(gui->getSlider("position X")->getValue() * effectCanvas.getWidth(),
                 gui->getSlider("position Y")->getValue() * effectCanvas.getHeight(),
                 gui->getSlider("** Radio")->getValue() * effectCanvas.getWidth());

    ofDrawBitmapString("particulizer_dev",20,20);
    ofDrawBitmapString("FrameRate: " + std::to_string(int(ofGetFrameRate()*100)/100),20,50);
    //ofDrawBitmapString("Resolution: " + std::to_string(screenWidth) + "-" + std::to_string(screenHeight), 20, 70);

    effectCanvas.end();

    float effectCanvasWidth = 0.25 * ofGetHeight() * 16.0 / 9.0;
    effectCanvas.draw(0.98 * ofGetWidth() - effectCanvasWidth , 0.525 * ofGetHeight(), effectCanvasWidth, 0.25 * ofGetHeight());

    // Output Canvas
    ofSetColor(100);
    ofRect(0.5 * ofGetWidth(), 0.0, 0.5 * ofGetWidth(), 0.5 * ofGetHeight());
    ofSetColor(255);

    output.begin();

        effectCanvas.draw(0, 0, output.getWidth(), output.getHeight());

    output.end();

    outputCanvas.begin();

    effectCanvas.draw(0, 0, outputCanvas.getWidth(), outputCanvas.getHeight());

    outputCanvas.end();

    outputCanvas.draw(0.525 * ofGetWidth(), 0.025 * ofGetHeight(), 0.45 * ofGetWidth(), 0.45 * ofGetWidth() * 9.0 / 16.0);

    gui->draw();


    // NanoKorg Controls
    ofSetColor(100);
    ofRect(0.5 * ofGetWidth(), 0.8 * ofGetHeight(), 0.5 * ofGetWidth(), 0.2 * ofGetHeight());
    ofSetColor(255);

    ofPoint location = ofPoint(0.5 * ofGetWidth(), 0.8 * ofGetHeight());
    nano.showGui(true, false, location);

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
    }   else if (key == 32){
        tIndex = tIndex < themes.size()-1 ? tIndex+1 : 0;
        gui->setTheme(themes[tIndex]);
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
