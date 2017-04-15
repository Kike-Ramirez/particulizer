#include "lighthair.h"

LightHair::LightHair()
{

    points.clear();

    float limit = 200;
    float rndLimit = 5;
    float step = 20;

    for (int i = -limit; i < limit; i += step) {

        for (int j = -limit; j < limit; j += step) {

            points.addVertex(ofVec3f(i + ofRandom(-rndLimit, rndLimit), ofRandom(rndLimit), j + ofRandom(-rndLimit, rndLimit) ));
        }
    }

    camera.setupPerspective();
}

void LightHair::update(NanoPanel &nanoPanel, AudioInput &audioInput) {

    // speed = 360.0;


}

void LightHair::drawOutput() {

    float rotatePos = sin( ofGetElapsedTimeMillis() * 0.001 );

    camera.setPosition(ofVec3f(1000 * (1 - 2 * ofNoise(0.01 * ofGetElapsedTimeMillis() / 1000.0)),
                               1000 * (1 - 2 * ofNoise(0.01 * ofGetElapsedTimeMillis() / 1000.0 + 5000)),
                               1000 * (1 - 2 * ofNoise(0.01 * ofGetElapsedTimeMillis() / 1000.0 + 10000))));
    camera.lookAt(ofVec3f(0, 0, 0));

    effectCanvas.begin();

    camera.begin();
    ofBackground(0);

    for (int i = 0; i < points.getNumVertices(); i++) {

        ofColor(255);
        ofDrawSphere(points.getVertex(i), 2);
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
