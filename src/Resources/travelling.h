#ifndef TRAVELLING_H
#define TRAVELLING_H

#include "ofMain.h"
#include "nanopanel.h"

class Travelling: public ofCamera
{
public:
    Travelling();

    ofVec3f position;
    ofVec3f size;
    int modeTravelling;
    int modeTargeting;
    void setupTravelling(ofVec3f position_, ofVec3f size_);
    void setModeTravelling(int mode_);
    void setModeTargeting(int mode_);
    void updateTravelling(int ellapsedTime_, vector<float> &cameraPanel_);

};

#endif // TRAVELLING_H
