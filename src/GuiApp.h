#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "effect_template.h"
#include "effectpanel.h"
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

    bool mFullscreen;
    void refreshWindow();
    void toggleFullscreen();

    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void audioReceived(float* input, int bufferSize, int nChannels);
    void setColors(ofColor frontColor_, ofColor backColor, ofColor selectedColor_);


    void exit();

    NanoKontrol2 nano;
    Layer layerA, layerB;
    Output output;
    MainPanel mainPanel;
    NanoPanel nanoPanel;
    EffectPanel effectPanel;
    AudioInput audioInput;
    vector<Effect_Template> effects;
    float offSetDelta, offSet;
    int numEffects;
    ofTrueTypeFont  coolvetica;
    ofColor frontColor;
    ofColor backColor;
    ofColor selectedColor;



};

