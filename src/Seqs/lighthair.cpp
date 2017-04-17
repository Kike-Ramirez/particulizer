#include "lighthair.h"

LightHair::LightHair()
{

    points.clear();

    float limit = 200;
    float rndLimit = 5;
    float step = 20;

    for (int i = -limit; i < limit; i += step) {

        for (int j = -limit; j < limit; j += step) {

            float scale = 50;
            ofVec3f initPoint = ofVec3f(i + ofRandom(-rndLimit, rndLimit), ofRandom(rndLimit), j + ofRandom(-rndLimit, rndLimit) );

            points.addVertex(initPoint);

            for (int k = 0; k < ofRandom(15); k++) {

                ofVec3f endPoint = ofVec3f(initPoint.x + ofRandom(-scale, scale),
                                           initPoint.y + ofRandom(-scale),
                                           initPoint.z + ofRandom(-scale, scale));

                Segment segment;
                segment.setup(initPoint, endPoint);
                segments.push_back(segment);

            }

        }
    }

    camera.setupPerspective();
}

void LightHair::update(NanoPanel &nanoPanel, AudioInput &audioInput) {

    noiseTime += 0.001 * nanoPanel.buttons[0].getVal();
    zoom = 2000 * nanoPanel.buttons[1].getVal();

}

void LightHair::drawOutput() {

    float rotatePos = sin( ofGetElapsedTimeMillis() * 0.001 );

    camera.setPosition(ofVec3f(zoom * (1 - 2 * ofNoise(noiseTime)),
                               -zoom * ofNoise(noiseTime + 5000),
                               -zoom * ofNoise(noiseTime + 10000)));
    camera.lookAt(ofVec3f(200 * (1 - 2 * ofNoise(noiseTime + 15000),
                                  0,
                                  200 * (1 - 2 * ofNoise(noiseTime + 20000)))));

//    camera.lookAt(ofVec3f(0,0,0));

    effectCanvas.begin();

    camera.begin();
    ofBackground(0);

    for (int i = 0; i < segments.size(); i++) {

        float index = ofNoise( noiseTime  + i * 500000);
        segments[i].update(index);
        segments[i].display();

    }

    ofDrawBitmapString( ofGetFrameRate(), 50, 50 );
    camera.end();
    effectCanvas.end();

    smallCanvas.begin();
    ofBackground(0);
    ofSetColor(255);
    effectCanvas.draw(0,0,smallCanvas.getWidth(), smallCanvas.getHeight());
    smallCanvas.end();

}
