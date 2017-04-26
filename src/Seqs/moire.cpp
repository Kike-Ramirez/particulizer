#include "moire.h"

Moire::Moire()
{

}

void Moire::postSetup() {

    //ofEnableArbTex();

    numParticles = 2000;

    loadParticles();

    shaderIndex = 10;
    subSequenceIndex = 0;
    subSequenceNum = 5;

    ofShader shader;
    shader.load("Shaders/Moire/moiredeeppatterns");
    shadersSequence.push_back(shader);



}

void Moire::loadParticles() {

    for (int i = 0; i < numParticles; i++) {

        ofVec3f particle = ofVec3f(ofRandom(Constants::OUTPUT_WIDTH), ofRandom(Constants::OUTPUT_HEIGHT) , 0);
        particles.push_back(particle);

    }
}


void Moire::update(NanoPanel &nanoPanel, AudioInput &audioInput) {

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


    if (shaderPanel[2] == 1) {

        shaderIndex++;
        if (shaderIndex == shaderNum) shaderIndex = 0;

    }

    if (particlePanel[2] == 1) {


    }

    audioBeats.clear();
    audioBeats.push_back(audioInput.beats[0]);
    audioBeats.push_back(audioInput.beats[1]);
    audioBeats.push_back(audioInput.beats[2]);

    // Modify time parameters according to audio levels
    // if (audioInput.beats[1] == 1) timeCamera -= 0.1;

    // Modify time parameters according to NanoKontrol values
    // timeCamera += 0.002 * timePanel[0];
    timeParticles += 0.1 * timePanel[1];


    // Update particles

    // Update camera movements

    // Update Effects&Shaders modes



    // Set texts

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
    else if (shaderIndex  == 10) modeShader = "MOIRE";

    this->setName("Name: MOIRE\nShader: " + modeShader);



}

void Moire::drawOutput() {

    shadersSequence[subSequenceIndex].begin();
    shadersSequence[subSequenceIndex].setUniform1f("time", timeParticles);
    float xx = ofNoise(timeParticles);
    float yy = ofNoise(timeParticles + 10);
    shadersSequence[subSequenceIndex].setUniform2f("mouse", ofVec2f(xx, yy));
    shadersSequence[subSequenceIndex].setUniform2f("resolution", ofVec2f(effectCanvas.getWidth(), effectCanvas.getHeight()));

    effectCanvas.begin();
    ofSetColor(255);
    ofFill();
    ofDrawRectangle(0, 0, effectCanvas.getWidth(), effectCanvas.getHeight());
    effectCanvas.end();

    shadersSequence[subSequenceIndex].end();



    ofSetColor(255);

    if (shaderPanel[3] == 1) {

        shaders[shaderIndex].begin();

        shaders[shaderIndex].setUniform1f		("rand"			, audioBeats[1]);
        shaders[shaderIndex].setUniform1f("speed", shaderPanel[0]);
        shaders[shaderIndex].setUniform1f("intensity", shaderPanel[1]);
        shaders[shaderIndex].setUniform3f("center1", ofVec3f(effectCanvas.getWidth()/2, effectCanvas.getHeight()/2, 0));

        shadingBuffer.begin();
        ofSetColor(255);
        effectCanvas.draw(0, 0, shadingBuffer.getWidth(), shadingBuffer.getHeight());
        // ofRect(0, 0, shadingBuffer.getWidth(), shadingBuffer.getHeight());
        shadingBuffer.end();
        shaders[shaderIndex].end();

        effectCanvas.begin();
        shadingBuffer.draw(0, 0, effectCanvas.getWidth(), effectCanvas.getHeight());
        effectCanvas.end();

    }

    smallCanvas.begin();
    ofSetColor(255);
    effectCanvas.draw(0,0,smallCanvas.getWidth(), smallCanvas.getHeight());
    smallCanvas.end();


}
