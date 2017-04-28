#include "circle_dancing.h"

Circle_Dancing::Circle_Dancing()
{

}

void Circle_Dancing::update(NanoPanel &nanoPanel, AudioInput &audioInput) {

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

    if (particlePanel[4] == 1) {

        //moireFront.update();

    }

    if (particlePanel[2] == 1) {

//        subSequenceIndex++;
//        if (subSequenceIndex == shadersSequence.size()) subSequenceIndex = 0;
//        cout << "subSequenceIndex: " << subSequenceNum << endl;

    }

    audioBeats.clear();
    audioBeats.push_back(audioInput.beats[0]);
    audioBeats.push_back(audioInput.beats[1]);
    audioBeats.push_back(audioInput.beats[2]);


    // Modify time parameters according to NanoKontrol values
    timeCamera += 0.1 * (timePanel[0] + audioBeats[2]);
    timeParticles += 0.1 * (timePanel[1] + audioBeats[1]);


    // Update particles
    circles.update(audioBeats);

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

    this->setName("Name: CircleDancing\nShader: " + modeShader);





}

void Circle_Dancing::postSetup() {

    circles.setup();

}

void Circle_Dancing::drawOutput() {


    effectCanvas.begin();
    ofBackground(0);
    ofFill();
    ofSetColor(255);
    circles.display();
    effectCanvas.end();

    ofSetColor(255);

    if (shaderPanel[3] == 1) {

        shaders[shaderIndex].begin();

        shaders[shaderIndex].setUniform1f		("rand"			, audioBeats[1]);
        shaders[shaderIndex].setUniform1f("speed", shaderPanel[0]);
        shaders[shaderIndex].setUniform1f("intensity", shaderPanel[1]);

        shadingBuffer.begin();
        ofFill();
        ofSetColor(255);
        effectCanvas.draw(0, 0, shadingBuffer.getWidth(), shadingBuffer.getHeight());
        // ofRect(0, 0, shadingBuffer.getWidth(), shadingBuffer.getHeight());
        shadingBuffer.end();
        shaders[shaderIndex].end();

        effectCanvas.begin();
        ofFill();
        ofSetColor(255);
        shadingBuffer.draw(0, 0, effectCanvas.getWidth(), effectCanvas.getHeight());
        effectCanvas.end();

    }

    smallCanvas.begin();
    ofBackground(0);
    ofSetColor(255);
    ofFill();
    effectCanvas.draw(0,0,smallCanvas.getWidth(), smallCanvas.getHeight());
    smallCanvas.end();

}
