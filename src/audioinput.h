#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include "ofMain.h"
#include "ofxFft.h"

class audioInput
{
public:

    void setup(ofPoint position_, ofPoint size_);
    void plot(vector<float>& buffer, float scale, float offset);
    void audioReceived(float* input, int bufferSize, int nChannels);
    void display();

    audioInput();

    ofxFft* fft;
    ofPoint position;
    ofPoint size;
    ofFbo canvas;

};

#endif // AUDIOINPUT_H
