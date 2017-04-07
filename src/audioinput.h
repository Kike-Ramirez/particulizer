#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include "ofMain.h"
#include "ofxFft.h"

class AudioInput
{
public:

    void setup(ofBaseApp * appPtr, ofPoint position_, ofPoint size_);
    void plot(vector<float>& buffer, ofPoint position, ofPoint height);
    void audioReceived(float* input, int bufferSize, int nChannels);
    void display();

    AudioInput();

    ofxFft* fft;
    ofPoint position;
    ofPoint size;
    ofFbo canvas;

    int bufferSize;

    vector<float> drawBins, middleBins, audioBins;
    ofMutex soundMutex;


};

#endif // AUDIOINPUT_H
