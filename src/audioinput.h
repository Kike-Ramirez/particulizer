#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include "ofMain.h"
#include "ofxFft.h"
#include "button.h"
#include "pushbutton.h"
#include "nanokontrol2.h"
#include "ofxBeat.h"


class AudioInput
{
public:

    void setup(ofBaseApp * appPtr, ofPoint position_, ofPoint size_);
    void update(NanoKontrol2 & nano);
    void plot(vector<float>& buffer, ofPoint position_, ofPoint size_);
    void audioReceived(float* input, int bufferSize, int nChannels);
    void display(ofTrueTypeFont coolvetica);

    AudioInput();

    ofxFft* fft;
    ofxBeat beat;
    ofPoint position;
    ofPoint size;
    ofFbo canvas;

    int bufferSize;

    vector<float> drawBins, middleBins, audioBins;
    vector<Button> filterFrecuencyButtons;
    vector<PushButton> filterMiddleButtons;
    vector<float> filterWidth;
    vector<ofColor> filterColors;
    vector<float> beats, amps;
    ofColor frontColor, backColor, selectedColor;
    
    ofMutex soundMutex;


};

#endif // AUDIOINPUT_H
