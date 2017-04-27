#ifndef DATABOMBING_H
#define DATABOMBING_H

#include "ofMain.h"
#include "effect_template.h"
#include "ofxXmlSettings.h"

class DataBombing : public Effect_Template
{
public:
    DataBombing();

    vector<ofVec3f> particles;
    int numParticles;
    vector<float> audioBeats;
    ofxXmlSettings file;
    ofTrueTypeFont fontSmall, fontMedium, fontBig;
    int sequenceNumber;
    string title;
    vector<string> name;
    vector<float> initNumber;
    vector<float> endNumber;
    float timerItem, timeItem;
    float timerDigit, timeDigit;
    int indexDigit;
    int indexSequence;
    int indexLoc;
    vector<float> dataNumbers;

    // Para saber qué linea estamos escribiendo...
    int maxString;

    void postSetup();
    void loadData(int i);
    void update(NanoPanel &nanoPanel, AudioInput &audioInput);
    void drawOutput();
};

#endif // DATABOMBING_H
