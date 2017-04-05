#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxKorgNanoKontrol.h"


class GuiApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

    ofxDatGui* gui;
    ofFbo layerA, layerB, outputCanvas, effectCanvas, output;
    bool mFullscreen;
    void refreshWindow();
    void toggleFullscreen();

    void keyPressed(int key);
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onToggleEvent(ofxDatGuiToggleEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onTextInputEvent(ofxDatGuiTextInputEvent e);
    void on2dPadEvent(ofxDatGui2dPadEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    void onMatrixEvent(ofxDatGuiMatrixEvent e);
    void sceneButtonPressed(int &e);
    void exit();

    int tIndex;
    vector<ofxDatGuiTheme*> themes;
    ofxKorgNanoKontrol nano;

};

