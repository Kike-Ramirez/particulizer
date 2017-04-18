#include "segment.h"

Segment::Segment()
{

}

void Segment::setup(ofVec3f initPoint_, ofVec3f endPoint_) {

    initPoint.set(initPoint_);
    endPoint.set(endPoint_);

    index = 1;

    lineWidth = 3;

    color = ofColor(255);

}

void Segment::update(float index_) {

    index = index_;

}

void Segment::display() {

    ofSetColor(color);
    ofSetLineWidth(lineWidth);

    ofVec3f vector;
    vector = endPoint - initPoint;

    ofVec3f endPoint2;
    endPoint2 = initPoint + vector * index;

    ofDrawLine(initPoint, endPoint2);
    ofSetColor(255);

}

void Segment::setColor(ofColor color_) {

    color.set(color_);

}

void Segment::setEndPoint(ofVec3f endPoint_) {

    endPoint.set(endPoint_);

}

void Segment::setInitPoint(ofVec3f initPoint_) {

    initPoint.set(initPoint_);

}

void Segment::setLineWidth(float lineWidth_) {

    lineWidth = lineWidth_;

}
