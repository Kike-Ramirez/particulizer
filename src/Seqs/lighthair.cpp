#include "lighthair.h"

LightHair::LightHair()
{


}

void LightHair::postSetup() {

    ofImage image;
    image.load("./images/chiquito.jpg");
    images.clear();
    images.push_back(image);


    points.clear();

    float limitH = images[0].getWidth() * 0.95 / 2.0;
    float limitV = images[0].getHeight() * 0.95 / 2.0;
    float rndLimit = 5;
    float step = 5;

    for (int i = -limitH; i < limitH; i += step) {

        for (int j = -limitV; j < limitV; j += step) {

            ofVec3f initPoint = ofVec3f(i + ofRandom(-rndLimit, rndLimit), 0, j + ofRandom(-rndLimit, rndLimit) );

            ofColor col = images[0].getColor(initPoint.x + limitH, initPoint.z + limitV);
            float scale = 50;


                points.addVertex(initPoint);

                if (col.getSaturation() < 100 && col.getBrightness() > 5) {

                for (int k = 0; k < ofRandom(3); k++) {

                    ofVec3f endPoint = ofVec3f(initPoint.x + ofRandom(-scale, scale),
                                               initPoint.y + ofRandom(-scale),
                                               initPoint.z + ofRandom(-scale, scale));

                    Segment segment;
                    segment.setup(initPoint, endPoint);
                    segment.setColor(col);
                    segments.push_back(segment);

                }

                }


        }
    }

    camera.setupPerspective();

}

void LightHair::update(NanoPanel &nanoPanel, AudioInput &audioInput) {

    noiseTime += 0.001 * nanoPanel.buttons[0].getVal();
    particleTime += 0.01 * nanoPanel.buttons[5].getVal();
    cameraRadio = 10.0 + 1000.0 * (0.2 + 0.8 * ofNoise(10 * noiseTime + 1.0)) * nanoPanel.buttons[1].getVal();
    cameraHeight = -10.0 - 2000.0 * (0.2 + 0.8 * ofNoise(20 * noiseTime + 2.0)) * nanoPanel.buttons[6].getVal();

    float cx = cameraRadio * cos(noiseTime * 360 / 2 / PI);
    float cz = cameraRadio * sin(noiseTime * 360 / 2 / PI);
    float cy = cameraHeight;

    camera.setPosition(cx, cy, cz);

    cout << camera.getPosition() << " " << cameraRadio<<  endl;

    float cx2 = cameraRadio * cos(noiseTime * 360 / 2 / PI + 180.0);
    float cz2 = cameraRadio * sin(noiseTime * 360 / 2 / PI + 180.0);
    float cy2 = 0;

    camera.lookAt(ofVec3f(cx2, cy2, cz2));

    for (float i = 0; i < segments.size(); i++) {

        float value = ofNoise( particleTime  + i * 1.2 + 3.333);
        float scale = 50;

        ofVec3f initPoint;
        initPoint.set(segments[i].initPoint);

        ofVec3f endPoint;

        endPoint.set(scale * (1 - 2 * ofNoise(particleTime + i * 1.3 + 10.0)),
                     - scale * (0.75 + 0.25 * ofNoise(particleTime + i * 1.4 + 2.3)),
                     scale * (1 - 2 * ofNoise(particleTime + i * 1.5 + 15.0)));

        endPoint = endPoint + initPoint;

        segments[i].setEndPoint(endPoint);
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

    camera.end();
    ofDrawBitmapString( ofGetFrameRate(), 50, 50 );
    effectCanvas.end();

    smallCanvas.begin();
    ofBackground(0);
    ofSetColor(255);
    effectCanvas.draw(0,0,smallCanvas.getWidth(), smallCanvas.getHeight());
    smallCanvas.end();

}
