#ifndef SMS_H
#define SMS_H

#include "ofMain.h"
#include "effect_template.h"
#include "ofxXmlSettings.h"


class SMS : public Effect_Template
{
public:
    SMS();

    vector<ofVec3f> particles;
    int numParticles;
    vector<float> audioBeats;
    ofxXmlSettings file;
    ofTrueTypeFont fontSmall, fontMedium, fontBig;
    int sequenceNumber;
    string title;
    string notif;
    string opening;
    string message;

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

#endif // SMS_H
