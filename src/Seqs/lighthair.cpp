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
    float step = 10;

    for (int i = -limitH; i < limitH; i += step) {

        for (int j = -limitV; j < limitV; j += step) {

            ofVec3f initPoint = ofVec3f(i + ofRandom(-rndLimit, rndLimit), 0, j + ofRandom(-rndLimit, rndLimit));

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

    camera.setupTravelling(ofVec3f(0, 0, 0), ofVec3f(1.0 * limitH, 2.0 * limitH, 1.0 * limitV ));
    camera.setupPerspective();

    ofDisableArbTex();

}

void LightHair::update(NanoPanel &nanoPanel, AudioInput &audioInput) {

    // Update values from NanoKontrol if the effect is active

    if (isActive()) {
        for (int i = 0; i < 5; i++) {

            if (i < 2) {
                timePanel[i] = nanoPanel.buttons[i].getVal();
                cameraPanel[i] = nanoPanel.buttons[i+4].getVal();
                particlePanel[i] = nanoPanel.buttons[i+8].getVal();
                shaderPanel[i] = nanoPanel.buttons[i+12].getVal();
            }

            else if ( i == 3)
            {
                timePanel[i] = nanoPanel.midButtons[0].getVal();
                cameraPanel[i] = nanoPanel.midButtons[1].getVal();
                particlePanel[i] = nanoPanel.midButtons[2].getVal();
                shaderPanel[i] = nanoPanel.midButtons[3].getVal();

            }

            else {

                int j = i;
                if (i == 4) j = i - 1;
                timePanelLocal[i] = nanoPanel.buttons[j].getVal();
                if (timePanelAnt[i] == 0 && timePanelLocal[i] == 1) {
                    timePanel[i] = 1;
                    timePanelAnt[i] = timePanelLocal[i];
                }

                else {
                    timePanel[i] = 0;
                    timePanelAnt[i] = timePanelLocal[i];
                }


                cameraPanelLocal[i] = nanoPanel.buttons[j + 4].getVal();
                if (cameraPanelAnt[i] == 0 && cameraPanelLocal[i] == 1) {
                    cameraPanel[i] = 1;
                    cameraPanelAnt[i] = cameraPanelLocal[i];
                }

                else {
                    cameraPanel[i] = 0;
                    cameraPanelAnt[i] = cameraPanelLocal[i];
                }

                particlePanelLocal[i] = nanoPanel.buttons[j + 8].getVal();
                if (particlePanelAnt[i] == 0 && particlePanelLocal[i] == 1) {
                    particlePanel[i] = 1;
                    particlePanelAnt[i] = particlePanelLocal[i];
                }

                else {
                    particlePanel[i] = 0;
                    particlePanelAnt[i] = particlePanelLocal[i];
                }

                shaderPanelLocal[i] = nanoPanel.buttons[j + 12].getVal();
                if (shaderPanelAnt[i] == 0 && shaderPanelLocal[i] == 1) {
                    shaderPanel[i] = 1;
                    shaderPanelAnt[i] = shaderPanelLocal[i];
                }

                else {
                    shaderPanel[i] = 0;
                    shaderPanelAnt[i] = shaderPanelLocal[i];
                }

            }
        }

    }


    // Modify time parameters according to audio levels
    // if (audioInput.beats[1] == 1) timeCamera -= 0.1;

    // Modify time parameters according to NanoKontrol values
    timeCamera += 0.002 * timePanel[0];
    timeParticles += 0.01 * timePanel[1]; // - 0.01 * audioInput.beats[2];


    // Update particles
    for (float i = 0; i < segments.size(); i++) {

        float value = pow(ofNoise( timeParticles  + i * 1.2 + 3.333), 2);
        float scale = 50;

        ofVec3f initPoint;
        initPoint.set(segments[i].initPoint);

        ofVec3f endPoint;

        endPoint.set(scale * (1 - 2 * ofNoise(timeParticles + i * 1.3 + 10.0)),
                     - scale * (0.01 + 0.99 * ofNoise(timeParticles + i * 1.4 + 2.3)),
                     scale * (1 - 2 * ofNoise(timeParticles + i * 1.5 + 15.0)));

        endPoint = endPoint + initPoint;

        segments[i].setEndPoint(endPoint);
        segments[i].update(value);

    }

    // Update camera movements
    camera.updateTravelling(timeCamera, cameraPanel);

    // Update Effects&Shaders modes



    // Set texts
    string modeTrav;

    if (camera.modeTravelling  == 0) modeTrav = "FIXED";
    else if (camera.modeTravelling  == 1) modeTrav = "CIRCULAR";
    else if (camera.modeTravelling  == 2) modeTrav = "SPHERICAL";
    else if (camera.modeTravelling  == 3) modeTrav = "PERLIN 3D";


    string modeTarg;

    if (camera.modeTargeting  == 0) modeTarg = "FIXED";
    else if (camera.modeTargeting  == 1) modeTarg = "CIRCULAR";
    else if (camera.modeTargeting  == 2) modeTarg = "SPHERICAL";
    else if (camera.modeTargeting  == 3) modeTarg = "PERLIN 3D";

    string modeRandom;
    if (cameraPanel[3] == 1) modeRandom = "RANDOM";
    else modeRandom = "FIXED";

    string modeShader;

    if (shaderPanel[3] == 0) modeShader = "OFF";
    else if (shaderIndex  == 0) modeShader = "CONVERGENCE";
    else if (shaderIndex  == 1) modeShader = "GLOW";
    else if (shaderIndex  == 2) modeShader = "SHAKER";
    else if (shaderIndex  == 3) modeShader = "CUTSLIDER";
    else if (shaderIndex  == 4) modeShader = "TWIST";
    else if (shaderIndex  == 5) modeShader = "OUTLINE";
    else if (shaderIndex  == 6) modeShader = "NOISE";
    else if (shaderIndex  == 7) modeShader = "SLITSCAN";
    else if (shaderIndex  == 8) modeShader = "SWELL";
    else if (shaderIndex  == 9) modeShader = "INVERT";

    this->setName("Name: LIGHTHAIR\nRadio Mode: " + modeRandom + "\nTravel Mode: " + modeTrav + "\nTarget Mode: " + modeTarg + "\nShader: " + modeShader);

}

void LightHair::drawOutput() {


    effectCanvas.begin();

    camera.begin();
    ofBackground(0);

    for (int i = 0; i < segments.size(); i++) {

        segments[i].display();

    }

    camera.end();
    effectCanvas.end();

    ofSetColor(255);

    if (shaderPanel[2] == 1) {

        shaderIndex++;
        if (shaderIndex == 10) shaderIndex = 0;

    }

    if (shaderPanel[3] == 1) {

        shaders[shaderIndex].begin();

        if (ofRandom(1) < 0.1) shaders[shaderIndex].setUniform1f		("rand"			,ofRandom(1));
        else shaders[shaderIndex].setUniform1f		("rand"			,ofRandom(0));
        shaders[shaderIndex].setUniform1f("speed", shaderPanel[0]);
        shaders[shaderIndex].setUniform1f("intensity", shaderPanel[1]);

        shadingBuffer.begin();
        effectCanvas.draw(0, 0, shadingBuffer.getWidth(), shadingBuffer.getHeight());
        // ofRect(0, 0, shadingBuffer.getWidth(), shadingBuffer.getHeight());
        shadingBuffer.end();
        shaders[shaderIndex].end();

        effectCanvas.begin();
        shadingBuffer.draw(0, 0, effectCanvas.getWidth(), effectCanvas.getHeight());
        effectCanvas.end();

    }

    smallCanvas.begin();
    ofBackground(0);
    ofSetColor(255);
    effectCanvas.draw(0,0,smallCanvas.getWidth(), smallCanvas.getHeight());
    smallCanvas.end();

}
