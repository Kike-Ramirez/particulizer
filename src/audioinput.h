#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include "ofMain.h"
#include "ofxFft.h"
#include "button.h"
#include "ofxKorgNanoKontrol.h"

class AudioInput
{
public:

    void setup(ofBaseApp * appPtr, ofPoint position_, ofPoint size_);
    void update(ofxKorgNanoKontrol & nano);
    void plot(vector<float>& buffer, ofPoint position_, ofPoint size_);
    void audioReceived(float* input, int bufferSize, int nChannels);
    void display(ofTrueTypeFont coolvetica);

    AudioInput();

    ofxFft* fft;
    ofPoint position;
    ofPoint size;
    ofFbo canvas;

    int bufferSize;

    vector<float> drawBins, middleBins, audioBins;
    vector<float> filterFrequencies;
    vector<Button> filterFrecuencyButtons;
    vector<float> filterValues;
    vector<Button> filterValueButtons;
    vector<Button> filterWidthButtons;
    vector<ofColor> filterColors;
    
    ofMutex soundMutex;


};

#endif // AUDIOINPUT_H
