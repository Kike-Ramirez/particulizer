#ifndef SEGMENT_H
#define SEGMENT_H

#include "ofMain.h"

class Segment
{
public:
    Segment();

    ofVec3f initPoint;
    ofVec3f endPoint;
    ofColor color;
    float index;
    float lineWidth;

    void setup(ofVec3f initPoint_, ofVec3f endPoint_);
    void update(float index_);
    void display();

    void setColor(ofColor color_);
    void setLineWidth(float lineWidth_);
    void setInitPoint(ofVec3f initPoint_);
    void setEndPoint(ofVec3f endPoint_);

};

#endif // SEGMENT_H
