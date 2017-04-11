#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "effect_template.h"
#include "layer.h"
#include "output.h"
#include "audioinput.h"
#include "button.h"
#include "nanokontrol2.h"
#include "pushbutton.h"
#include "mainpanel.h"
#include "nanopanel.h"



class GuiApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

    ofxDatGui* gui;
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
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void audioReceived(float* input, int bufferSize, int nChannels);


    void exit();

    int tIndex;
    vector<ofxDatGuiTheme*> themes;
    NanoKontrol2 nano;
    Layer layerA, layerB;
    Output output;
    MainPanel mainPanel;
    NanoPanel nanoPanel;
    AudioInput audioInput;
    vector<Effect_Template> effects;
    float offSetDelta, offSet;
    int numEffects;
    ofTrueTypeFont  coolvetica;



};

