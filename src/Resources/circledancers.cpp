#include "circledancers.h"

CircleDancers::CircleDancers()
{

}

void CircleDancers::setup()
{

    modeSelected = 0;
    position = ofVec2f(0.5 * Constants::OUTPUT_WIDTH, 0.5 * Constants::OUTPUT_HEIGHT);
    target = ofVec2f(0.5 * Constants::OUTPUT_WIDTH, 0.5 * Constants::OUTPUT_HEIGHT);

    positionA = ofVec2f(-0.3 * Constants::OUTPUT_WIDTH, 0.0 * Constants::OUTPUT_HEIGHT);
    targetA = ofVec2f(-0.3 * Constants::OUTPUT_WIDTH, 0.0 * Constants::OUTPUT_HEIGHT);

    positionB = ofVec2f(0.3 * Constants::OUTPUT_WIDTH, 0.0 * Constants::OUTPUT_HEIGHT);
    targetB = ofVec2f(0.3 * Constants::OUTPUT_WIDTH, 0.0 * Constants::OUTPUT_HEIGHT);

    radio = 100;
    radioTarget = 100;

    timeA = ofGetElapsedTimef();
    timerA = 0.5;

}

void CircleDancers::update(vector<float> audioBeats_)
{

    if (modeSelected == 0) {

        if (audioBeats_[1] == 1) {

            target = ofVec2f(0.5 * Constants::OUTPUT_WIDTH, Constants::OUTPUT_HEIGHT);

        }

        else target = ofVec2f(0.5 * Constants::OUTPUT_WIDTH, 0.5 * Constants::OUTPUT_HEIGHT);


        ofVec2f speed = 0.3 * (target - position);
        position = position + speed;
    }

    else if (modeSelected == 1) {

        if (audioBeats_[1] == 1) {

            radioTarget = 150;

        }

        else radioTarget = 100;


        float delta = 0.3 * (radioTarget - radio);
        radio = radio + delta;
    }

    else if (modeSelected == 2) {

        if (audioBeats_[1] == 1) {

            targetA = ofVec2f(0.0 * Constants::OUTPUT_WIDTH, 0.0 * Constants::OUTPUT_HEIGHT);
            targetB = ofVec2f(0.0 * Constants::OUTPUT_WIDTH, 0.0 * Constants::OUTPUT_HEIGHT);

        }

        else {

            targetA = ofVec2f(-0.3 * Constants::OUTPUT_WIDTH, 0.0 * Constants::OUTPUT_HEIGHT);
            targetB = ofVec2f(0.3 * Constants::OUTPUT_WIDTH, 0.0 * Constants::OUTPUT_HEIGHT);

        }


        ofVec2f deltaA = 0.3 * (targetA - positionA);
        positionA = positionA + deltaA;

        ofVec2f deltaB = 0.3 * (targetB - positionB);
        positionB = positionB + deltaB;


    }

}

void CircleDancers::nextMode()
{

    modeSelected++;

    if (modeSelected == 3) modeSelected = 0;

}

void CircleDancers::activateFlash()
{

    timeA = ofGetElapsedTimef();

}

void CircleDancers::display()
{

    if (modeSelected == 0) {

        ofBackground(255);
        ofSetColor(0);
        ofDrawEllipse(position.x, position.y, 400, 400);
    }

    else if (modeSelected == 1) {

        ofFill();
        ofBackground(0);
        ofSetColor(255);

        for (int i = 0; i < 8; i++) {
            ofPushMatrix();
            ofTranslate(0.5 * Constants::OUTPUT_WIDTH, 0.5 * Constants::OUTPUT_HEIGHT);
            ofRotate(360 * ofNoise( ofGetFrameNum() *0.003 + 5 ));
            ofRotate(i * 360/8);
            ofTranslate(0, 200);
            ofDrawEllipse(0, 0, radio, radio);
            ofPopMatrix();
        }

        for (int i = 0; i < 13; i++) {
            ofPushMatrix();
            ofTranslate(0.5 * Constants::OUTPUT_WIDTH, 0.5 * Constants::OUTPUT_HEIGHT);
            ofRotate(360 * ofNoise( ofGetFrameNum() *0.0032 + 10 ));
            ofRotate(i * 360/13);
            ofTranslate(0, 350);
            ofDrawEllipse(0, 0, 0.7 * radio, 0.7 * radio);
            ofPopMatrix();
        }
    }

    else if (modeSelected == 2) {

        ofFill();
        ofBackground(0);
        ofSetColor(255);

        float dist = abs(positionA.x - positionB.x);

        float radioCircles;

        if (dist < 300) radioCircles = ofMap(dist, 0, 300, 1000, 300);
        else radioCircles = 300;

        ofPushMatrix();
        ofTranslate(0.5 * Constants::OUTPUT_WIDTH, 0.5 * Constants::OUTPUT_HEIGHT);
        ofScale(1 + ofNoise( ofGetFrameNum() *0.0032 + 20 ), 1 + ofNoise( ofGetFrameNum() *0.0032 + 20 ));
        ofRotate(360 * ofNoise( ofGetFrameNum() *0.0032 + 15 ));
        ofPushMatrix();
        ofTranslate(positionA.x, positionA.y);
        ofDrawEllipse(0, 0, radioCircles, radioCircles);
        ofPopMatrix();

        ofPushMatrix();
        ofTranslate(positionB.x, positionB.y);
        ofDrawEllipse(0, 0, radioCircles, radioCircles);
        ofPopMatrix();

        ofPopMatrix();

    }

    if (ofGetElapsedTimef() - timeA <= timerA) {

        float alpha = ofMap(ofGetElapsedTimef() - timeA, 0, timerA, 255, 0);
        float radio = ofMap(ofGetElapsedTimef() - timeA, 0, timerA, 120, 640);

        ofSetColor(255, 0, 0, alpha);

        for (int i = 0; i < 10; i++ ) {

            ofPushMatrix();
            ofTranslate(0.5 * Constants::OUTPUT_WIDTH, 0.5 * Constants::OUTPUT_HEIGHT);
            ofRotate(i * 360 / 10);
            ofTranslate(0, radio);
//            float x = Constants::OUTPUT_WIDTH * (ofNoise(0.6 * ofGetElapsedTimef() + i * 21 + 0.3));
//            float y = Constants::OUTPUT_HEIGHT * (ofNoise(0.6 * ofGetElapsedTimef() + i * 53) + 0.12);
            ofDrawEllipse(0, 0, 100, 100);
            ofPopMatrix();

        }

    }
}
