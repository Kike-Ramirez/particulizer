#include "sms.h"

SMS::SMS()
{

}

void SMS::postSetup()
{

    fontSmall.loadFont("PxPlus_AmstradPC1512.ttf", 24);
    fontMedium.loadFont("PxPlus_AmstradPC1512.ttf", 26);
    fontMedium.setLineHeight(60);
    fontBig.loadFont("PxPlus_AmstradPC1512.ttf", 96);

    timeItem = ofGetElapsedTimef();
    timerItem = 2;

    timeDigit = ofGetElapsedTimef();
    timerDigit = 0.1;

    indexDigit = 0;
    indexSequence = 0;
    indexLoc = -2;

    shaderIndex = 5;

    loadData(0);
    timeItem = ofGetElapsedTimef();

    for (int i = 0; i < 10000; i++) {

        dataNumbers.push_back(ofRandom(0, 1));

    }

    video.loadMovie("movies/mariano.mov");
    video.setLoopState(OF_LOOP_NORMAL);
    video.play();



}

void SMS::loadData(int i)
{
    if(file.loadFile("sms.xml")){
        file.pushTag("sms");
        sequenceNumber = file.getNumTags("sequence");
        file.pushTag("sequence", i);
        notif = file.getValue("notif", "");
        opening = file.getValue("opening", "");
        from = file.getValue("from", "");
        message = ofToString(file.getValue("message", ""));
        file.popTag();
        file.popTag(); //pop position
    }
    else{

        ofLogError("XML file did not load!");

    }

}

void SMS::update(NanoPanel &nanoPanel, AudioInput &audioInput)
{
    if (isActive()) {

        video.update();

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

        indexLoc++;

        if (indexLoc == 3) {

            indexLoc = -2;
            indexSequence++;
            if (indexSequence >= sequenceNumber) indexSequence = 0;
        }

        loadData(indexSequence);
        timeItem = ofGetElapsedTimef();

    }

    if (particlePanel[4] == 1) {

        indexSequence--;
        if (indexSequence <= -1) indexSequence = sequenceNumber-1;
        indexLoc = -2;
        loadData(indexSequence);

    }



    audioBeats.clear();
    audioBeats.push_back(audioInput.beats[0]);
    audioBeats.push_back(audioInput.beats[1]);
    audioBeats.push_back(audioInput.beats[2]);


    // Modify time parameters according to NanoKontrol values
    timeCamera += 0.1 * (timePanel[0] + audioBeats[2]);
    timeParticles += 0.1 * (timePanel[1] + audioBeats[1]);


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

    string ONOFF;
    if (particlePanel[3] == 1) ONOFF = "ON";
    else ONOFF = "OFF";

    this->setName("Name: SMS\nStatus: " + ONOFF + "\nIndex: " + ofToString(indexSequence) + "\nIndexLoc: " + ofToString(indexLoc) + "\nShader: " + modeShader);





}

void SMS::drawOutput()
{

    effectCanvas.begin();
    ofSetColor(255);
    video.draw(-0.1 * effectCanvas.getWidth(), -0.1 * effectCanvas.getHeight(), 1.2 * effectCanvas.getWidth(), 1.2 * effectCanvas.getHeight());
    effectCanvas.end();

    ofSetColor(255);

    if (shaderPanel[3] == 1) {

        shaders[shaderIndex].begin();

        shaders[shaderIndex].setUniform1f		("rand"			, audioBeats[1]);
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

    if (particlePanel[3] == 1) {

        float timeLoc = ofGetElapsedTimef() - timeItem;

        float valueLoc = ofMap(timeLoc, 0, timerItem, 0, 1);
        if (valueLoc >= 1) valueLoc = 1;

        effectCanvas.begin();
        ofFill();
        ofSetColor(255, particlePanel[1] * 255);

        if (indexLoc == -1) {

            float size = notif.size();

            int endString = int(valueLoc * size);

            if (ofGetFrameNum() % 30 > 15 ) fontSmall.drawString(notif.substr(0, endString) + "_", 0.05 * effectCanvas.getWidth(), 0.5 * effectCanvas.getHeight());

            else fontSmall.drawString(notif.substr(0, endString), 0.05 * effectCanvas.getWidth(), 0.5 * effectCanvas.getHeight());



        }

        else if (indexLoc == 0) {

            float size = from.size();

            int endString = int(valueLoc * size);

            if (ofGetFrameNum() % 30 > 15 ) fontSmall.drawString(from.substr(0, endString) + "_", 0.05 * effectCanvas.getWidth(), 0.5 * effectCanvas.getHeight());

            else fontSmall.drawString(from.substr(0, endString), 0.05 * effectCanvas.getWidth(), 0.5 * effectCanvas.getHeight());

        }

        else if (indexLoc == 1) {

            float size = opening.size();

            int endString = int(valueLoc * size);

            if (ofGetFrameNum() % 30 > 15 ) fontSmall.drawString(opening.substr(0, endString) + "_", 0.05 * effectCanvas.getWidth(), 0.5 * effectCanvas.getHeight());

            else fontSmall.drawString(opening.substr(0, endString), 0.05 * effectCanvas.getWidth(), 0.5 * effectCanvas.getHeight());

        }

        else if (indexLoc == 2) {

            float size = message.size();

            int endString = int(valueLoc * size);

            if (ofGetFrameNum() % 30 > 15 ) fontMedium.drawString(message.substr(0, endString) + "_", 0.05 * effectCanvas.getWidth(), 0.5 * effectCanvas.getHeight());

            else fontMedium.drawString(message.substr(0, endString), 0.05 * effectCanvas.getWidth(), 0.5 * effectCanvas.getHeight());


        }

        effectCanvas.end();

    }


    smallCanvas.begin();
    ofBackground(0);
    ofSetColor(255);
    effectCanvas.draw(0,0,smallCanvas.getWidth(), smallCanvas.getHeight());
    smallCanvas.end();

}
