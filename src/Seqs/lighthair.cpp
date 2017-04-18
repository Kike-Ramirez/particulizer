#include "lighthair.h"

LightHair::LightHair()
{


}

void LightHair::postSetup() {

    points.clear();

    float limit = 500;
    float rndLimit = 20;
    float step = 20;

    for (int i = -limit; i < limit; i += step) {

        for (int j = -limit; j < limit; j += step) {

            float scale = 50;
            ofVec3f initPoint = ofVec3f(i + ofRandom(-rndLimit, rndLimit), 0, j + ofRandom(-rndLimit, rndLimit) );

            points.addVertex(initPoint);

            for (int k = 0; k < ofRandom(5); k++) {

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
    cameraRadio = 10 + 1000 * nanoPanel.buttons[1].getVal();
    cameraHeight = -10 - 1000 * nanoPanel.buttons[6].getVal();

    float cx = cameraRadio * cos(noiseTime * 360 / 2 / PI);
    float cz = cameraRadio * sin(noiseTime * 360 / 2 / PI);
    float cy = cameraHeight;

    camera.setPosition(cx, cy, cz);

    float cx2 = cameraRadio * cos(-noiseTime * 360 / 2 / PI);
    float cz2 = cameraRadio * sin(-noiseTime * 360 / 2 / PI);
    float cy2 = 0;

    camera.lookAt(ofVec3f(0, 0, 0));

    for (int i = 0; i < segments.size(); i++) {

        float value = ofNoise( noiseTime  + i * 50);
        segments[i].update(value);

    }

}

void LightHair::drawOutput() {

    float rotatePos = sin( ofGetElapsedTimeMillis() * 0.001 );


//    camera.lookAt(ofVec3f(0,0,0));

    effectCanvas.begin();

    camera.begin();
    ofBackground(0);

    for (int i = 0; i < segments.size(); i++) {

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
