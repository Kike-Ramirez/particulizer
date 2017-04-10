#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "effect_template.h"
#include "layer.h"
#include "output.h"
#include "audioinput.h"
#include "button.h"
#include "nanokontrol2.h"



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
    vector<Effect_Template> effects;
    Layer layerA, layerB;
    Output output;
    AudioInput audioInput;
    float offSetDelta, offSet;
    int numEffects;
    ofTrueTypeFont  coolvetica;
    Button mainSlider;

};

