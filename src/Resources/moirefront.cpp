#include "moirefront.h"

MoireFront::MoireFront()
{

}


void MoireFront::setup(ofFbo &canvas)
{

    index = 0;

    timerCheck = ofGetElapsedTimeMillis();

    canvasMoire.allocate(canvas.getWidth(), canvas.getHeight());

}

void MoireFront::update()
{

    index ++;

    if (index == 3) index = 0;

}

void MoireFront::shoot(float v)
{

    if (v == 1.0) {

        timerCheck = ofGetElapsedTimeMillis();
    }

}

void MoireFront::draw1(ofFbo &canvas, vector<float> drawSamples, ofColor colorMoire)
{

    canvasMoire.begin();

    ofBackground(0, 20);

    ofSetColor(colorMoire);

    float maxTime = 500;

    float dist = 0;

    if (ofGetElapsedTimeMillis() - timerCheck <= maxTime) {

        dist = ofMap(ofGetElapsedTimeMillis() - timerCheck, 0, maxTime, 0, canvas.getWidth() );

    }

    for (int i = 0; i < drawSamples.size() * 0.33; i++) {

        ofPushMatrix();

        ofTranslate(0.5 * canvas.getWidth(), 0.5 * canvas.getHeight());

        float xx = ofMap(i, 0, drawSamples.size() * 0.33, 0.0, 0.5 * canvas.getWidth());
        float xx2 = ofMap(i, 0, drawSamples.size() * 0.33, 0.0, - 0.5 * canvas.getWidth() );

        float yy = sqrt(drawSamples[int(xx)]) * canvas.getHeight() * 3.0;

        float scale = 1 + 2 * ofNoise(ofGetElapsedTimef() * 0.5 + 7.352);

        ofScale(scale, scale, scale);

        ofFill();

        if (dist > 0) {

            ofDrawRectangle(xx + dist,  - yy/2, 1, yy);
            ofDrawRectangle(xx2 - dist, - yy/2, 1, yy);

        }


        ofRotate(360 * ofNoise(ofGetElapsedTimef() * 0.1 + 12.32));

        ofDrawRectangle(xx,  - yy/2, 2, yy);
        ofDrawRectangle(xx2, - yy/2, 2, yy);

        ofPopMatrix();

        ofNoFill();

    }

    canvasMoire.end();

    canvas.begin();

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255);
    canvasMoire.draw(0,0);
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    canvas.end();


}

void MoireFront::draw2(ofFbo &canvas, vector<float> drawSamples, ofColor colorMoire)
{

    canvasMoire.begin();

    ofBackground(0, 20);

    ofSetColor(colorMoire);

    float maxTime = 2000;

    float dist = 0;

    int squareBegin = 0;
    int squareEnd = 50;

    float actualTime = ofGetElapsedTimeMillis() - timerCheck;

    if (actualTime <= maxTime) {

        dist = ofMap(actualTime, 0, maxTime, 0, canvas.getWidth() );

        if (actualTime >= 0.1 * maxTime) {

            squareBegin = int(ofMap(actualTime, 0.1 * maxTime, maxTime, 0, squareEnd));
        }
    }

    for (int i = squareBegin; i < squareEnd; i++) {

        ofPushMatrix();

        ofTranslate(0.5 * canvas.getWidth(), 0.5 * canvas.getHeight());

        float step = ofMap(ofGetElapsedTimeMillis() % 2000, 0, 2000, -10, 20);

        float xx = -0.25 * canvas.getWidth() + i * step;
        float side = i * 12;

        float scale = 1 + 2 * ofNoise(ofGetElapsedTimef() * 0.5 + 7.352);

        ofScale(scale, scale, scale);
        ofSetLineWidth(5);

        if (dist > 0) {

            ofDrawRectangle(xx + dist,  -0.5 * side, side, side);

        }


        ofRotate(360 * ofNoise(ofGetElapsedTimef() * 0.1 + 12.32));

        ofDrawRectangle(xx,  -0.5 * side, side, side);

        ofPopMatrix();

        ofSetLineWidth(1);
    }

    canvasMoire.end();

    canvas.begin();

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255);
    canvasMoire.draw(0,0);
    ofDisableBlendMode();
    canvas.end();

}

void MoireFront::draw3(ofFbo &canvas, vector<float> drawSamples, ofColor colorMoire)
{

    canvasMoire.begin();

    ofBackground(0, 20);

    ofSetColor(colorMoire);

    float maxTime = 2000;

    float dist = 0;

    int squareBegin = 0;
    int squareEnd = 20;

    float actualTime = ofGetElapsedTimeMillis() - timerCheck;

    if (actualTime <= maxTime) {

        dist = ofMap(actualTime, 0, maxTime, 0, canvas.getWidth() );

        if (actualTime >= 0.1 * maxTime) {

            squareBegin = int(ofMap(actualTime, 0.1 * maxTime, maxTime, 0, squareEnd));
        }
    }

    for (int i = squareBegin; i < squareEnd; i++) {

        ofPushMatrix();

        ofTranslate(0.5 * canvas.getWidth(), 0.5 * canvas.getHeight());

        float step = ofMap(ofGetElapsedTimeMillis() % 2000, 0, 2000, -10, 50);

        float xx = -0.25 * canvas.getWidth() + i * step;
        float side = i * 12;

        float scale = 1 + 2 * ofNoise(ofGetElapsedTimef() * 0.5 + 7.352);

        ofScale(scale, scale, scale);
        ofSetLineWidth(5);

        if (dist > 0) {

            for (int j = 0; j < 20; j++) {

                ofPushMatrix();

                ofTranslate(xx,  -0.5 * side);

                ofRotate(360 * ofNoise(ofGetElapsedTimef() * 0.5 + 12.32));

                ofRotate(360 * j / 20.0);

                ofTranslate(side, 0);

                ofDrawCircle(dist, 0, 1 * i);

                ofPopMatrix();

            }

        }


        ofRotate(360 * ofNoise(ofGetElapsedTimef() * 0.1 + 12.32));

        for (int j = 0; j < 20; j++) {

            ofPushMatrix();

            ofTranslate(xx,  -0.5 * side);

            ofRotate(360 * ofNoise(ofGetElapsedTimef() * 0.5 + 12.32));

            ofRotate(360 * j / 20.0);

            ofTranslate(side, 0);

            ofDrawCircle(0, 0, 1 * i);

            ofPopMatrix();

        }

        ofPopMatrix();

        ofSetLineWidth(1);
    }

    canvasMoire.end();

    canvas.begin();

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255);
    canvasMoire.draw(0,0);
    ofDisableBlendMode();
    canvas.end();

}

void MoireFront::draw(ofFbo &canvas, vector<float> drawSamples, ofColor colorMoire)
{
    if (index ==  0) draw1(canvas, drawSamples, colorMoire);
    else if (index ==  1) draw2(canvas, drawSamples, colorMoire);
    else if (index ==  2) draw3(canvas, drawSamples, colorMoire);

}
