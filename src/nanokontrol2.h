#ifndef NANOKONTROL2_H
#define NANOKONTROL2_H

#include "ofMain.h"
#include "ofxMidi.h"

class NanoKontrol2 : public ofxMidiListener
{
public:
    NanoKontrol2();
    ~NanoKontrol2();

    void getListMidiDevices();

    float getVal(int number_);
    float getSlider(int number_);
    float getRotary(int number_);
    float getUpperBtn(int number_);
    float getMidBtn(int number_);
    float getLowerBtn(int number_);

    void setup();

private:

    ofxMidiIn midiIn;
    ofxMidiOut midiOut;
    ofxMidiMessage midiMessage;
    vector<float> nanoValues;

    int findKontrolPort();
    int portNum;

    void newMidiMessage(ofxMidiMessage& eventArgs);

};

#endif // NANOKONTROL2_H
