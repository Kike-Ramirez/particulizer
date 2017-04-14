#include "audioinput.h"

AudioInput::AudioInput()
{

}

void AudioInput::setup(ofBaseApp *appPtr, ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);
    canvas.allocate(size.x, size.y);

    bufferSize = beat.getBufferSize();

    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);

    drawBins.resize(fft->getBinSize());
    middleBins.resize(fft->getBinSize());
    audioBins.resize(fft->getBinSize());

    // 0 output channels,
    // 1 input channel
    // 44100 samples per second
    // [bins] samples per buffer
    // 4 num buffers (latency)

    ofSoundStreamSetup(0, 1, appPtr, 44100, bufferSize, 4);

    // Insert buttons into Audio Display

    Button button = Button();

    // Insert Rotarys
    button.setup(ofPoint(position.x + size.x * 0.175, position.y + size.y * 0.57), ofPoint(size.x * 0.05, size.x * 0.05), 1);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.415, position.y + size.y * 0.57), ofPoint(size.x * 0.05, size.x * 0.05), 1);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.655, position.y + size.y * 0.57), ofPoint(size.x * 0.05, size.x * 0.05), 1);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);

    // Insert Sliders
    button.setup(ofPoint(position.x + size.x * 0.155, position.y + size.y * 0.64), ofPoint(size.x * 0.04, size.x * 0.22), 0);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.395, position.y + size.y * 0.64), ofPoint(size.x * 0.04, size.x * 0.22), 0);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.635, position.y + size.y * 0.64), ofPoint(size.x * 0.04, size.x * 0.22), 0);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);

    // Insert Upper pads
    button.setup(ofPoint(position.x + size.x * 0.090, position.y + size.y * 0.64), ofPoint(size.x * 0.04, size.x * 0.04), 2);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.335, position.y + size.y * 0.64), ofPoint(size.x * 0.04, size.x * 0.04), 2);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.575, position.y + size.y * 0.64), ofPoint(size.x * 0.04, size.x * 0.04), 2);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);

    // Insert Lower pads
    button.setup(ofPoint(position.x + size.x * 0.090, position.y + size.y * 0.64 + size.x * 0.18), ofPoint(size.x * 0.04, size.x * 0.04), 2);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.335, position.y + size.y * 0.64 + size.x * 0.18), ofPoint(size.x * 0.04, size.x * 0.04), 2);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.575, position.y + size.y * 0.64 + size.x * 0.18), ofPoint(size.x * 0.04, size.x * 0.04), 2);
    button.setColors(frontColor, backColor, selectedColor);
    filterFrecuencyButtons.push_back(button);
    
    // Insert Mid pads
    PushButton button2;
    button2.setup(ofPoint(position.x + size.x * 0.090, position.y + size.y * 0.64 + size.x * 0.09), ofPoint(size.x * 0.04, size.x * 0.04), 1);
    button2.setLabel("");
    button2.setColors(frontColor, backColor, selectedColor);
    filterMiddleButtons.push_back(button2);
    button2.setup(ofPoint(position.x + size.x * 0.335, position.y + size.y * 0.64 + size.x * 0.09), ofPoint(size.x * 0.04, size.x * 0.04), 1);
    button2.setLabel("");
    button2.setColors(frontColor, backColor, selectedColor);
    filterMiddleButtons.push_back(button2);
    button2.setup(ofPoint(position.x + size.x * 0.575, position.y + size.y * 0.64 + size.x * 0.09), ofPoint(size.x * 0.04, size.x * 0.04), 1);
    button2.setLabel("");
    button2.setColors(frontColor, backColor, selectedColor);
    filterMiddleButtons.push_back(button2);


    // Insert filter color list
    filterColors.push_back(ofColor(255, 255, 0));
    filterColors.push_back(ofColor(255, 0, 255));
    filterColors.push_back(ofColor(0, 255, 255));

    frontColor = ofColor(155);
    backColor = ofColor(0);
    selectedColor = ofColor(255);

    filterWidth.push_back(0.1);
    filterWidth.push_back(0.1);
    filterWidth.push_back(0.1);
    filterWidth.push_back(0.1);

    for (int i = 0; i < 4; i++) {

        beats.push_back(0.0);
        amps.push_back(0.0);

    }
    
    selected = false;


}

void AudioInput::display(ofTrueTypeFont coolvetica) {

    // Copy data
    soundMutex.lock();
    drawBins = middleBins;
    soundMutex.unlock();

    // Draw BackPanel
    ofPushMatrix();
    ofTranslate(position.x, position.y);
    ofSetColor(selectedColor);
    ofNoFill();
    ofSetLineWidth(1);
    if (selected) ofDrawRectangle(0.05 * size.x, 0.05 * size.y, 0.9 * size.x, 0.9 * size.y);



    for (int i = 0; i < 4; i++) {

        float alpha;

        if (i == 0) alpha = 255 * beats[0];
        else {

            if (filterMiddleButtons[i-1].getVal() == 0) alpha = 255 * beats[i];
            else alpha = 20 * amps[i];

        }

        ofSetColor(0);
        ofFill();

        ofDrawRectangle(size.x * 0.75, (0.64 + i * 0.07) * size.y, 0.15 * size.x, 0.04 * size.y );

        if (i > 0) ofSetColor(filterColors[i - 1], alpha);
        else ofSetColor(255, alpha);
        ofFill();
        ofDrawRectangle(size.x * 0.75, (0.64 + i * 0.07) * size.y, 0.15 * size.x, 0.04 * size.y );

        if (i > 0) ofSetColor(filterColors[i - 1]);
        else ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(size.x * 0.75, (0.64 + i * 0.07) * size.y, 0.15 * size.x, 0.04 * size.y );
    }

    ofPopMatrix();
    
    for (int i = 0; i < filterFrecuencyButtons.size(); i++) {

        filterFrecuencyButtons[i].display();

    }

    for (int i = 0; i < filterMiddleButtons.size(); i++) {

        filterMiddleButtons[i].display();

    }

    plot(drawBins, ofPoint(position.x + 0.1* size.x, position.y + 0.1 * size.y), ofPoint(0.8 * size.x, 0.8 * size.y/2));


}

void AudioInput::plot(vector<float>& buffer, ofPoint position_, ofPoint size_) {


    int n = buffer.size();

    ofPushMatrix();
    ofTranslate(position_.x, position_.y);

    ofSetColor(0);
    ofFill();
    ofRect(0, 0, size_.x, size_.y);

    // Draw Filter Images
    ofNoFill();
    ofSetColor(frontColor);
    ofRect(0, 0, size_.x, size_.y);

    for (int i = 0; i < 3; i++) {

        float alpha;

        if (filterMiddleButtons[i].getVal() == 0) alpha = beats[i+1] * 255;
        else alpha = amps[i+1] * 10;

        ofFill();
        ofSetColor(filterColors[i], alpha);
        ofRect(filterFrecuencyButtons[i].getVal() * size_.x, (1 - filterFrecuencyButtons[i+3].getVal()) * size_.y, filterWidth[i] * size_.x, filterFrecuencyButtons[i+3].getVal() * size_.y);
        ofSetColor(filterColors[i]);
        ofNoFill();
        ofRect(filterFrecuencyButtons[i].getVal() * size_.x, (1 - filterFrecuencyButtons[i+3].getVal()) * size_.y, filterWidth[i] * size_.x, filterFrecuencyButtons[i+3].getVal() * size_.y);

    }
    
    ofSetColor(selectedColor);

    //ofFill();

    ofTranslate(0, size_.y, 0.0);
    ofSetLineWidth(0.5);
    ofBeginShape();
    for (int i = 0; i < n; i++) {
        float xx = ofMap(i, 0, n, 0, size_.x );
        ofVertex(xx, -1 * sqrt(buffer[int(xx)]) * size_.y);
    }
    ofEndShape();
    ofSetLineWidth(1);

    ofNoFill();
    ofPopMatrix();

}

void AudioInput::update(NanoKontrol2 &nano) {

    if (selected) {

        // Actualizamos valores del controlador MIDI
        for (int i = 0; i < 3; i++) {

            filterFrecuencyButtons[i].update(nano.getRotary(i + 1));
            filterFrecuencyButtons[i+3].update(nano.getSlider(i + 1));
            filterFrecuencyButtons[i+6].update(nano.getUpperBtn(i + 1));
            filterFrecuencyButtons[i+9].update(nano.getLowerBtn(i + 1));

            filterMiddleButtons[i].update(nano.getMidBtn(i+1));

            float step = 0.001;

            if (nano.getUpperBtn(i+1) >= 1 && filterWidth[i] <= 1) filterWidth[i] += step;
            if (nano.getLowerBtn(i+1) >= 1 && filterWidth[i] >= 0) filterWidth[i] -= step;

        }
    }

    // Calculamos nuevos beats
    beat.update(ofGetElapsedTimeMillis());

    for (int i = 0; i < beats.size(); i++) {
        beats[i] = beats[i] * 0.95;
        amps[i] = 0;
    }

    if (beat.isBeat(0)) beats[0] = 1;

    for (int i = 0; i < FFT_SUBBANDS; i++) {

        amps[0] += beat.getBand(i);
    }
    amps[0] = amps[0] / (FFT_SUBBANDS);



    int low = filterFrecuencyButtons[0].getVal() * FFT_SUBBANDS;
    int high = (filterFrecuencyButtons[0].getVal() + filterWidth[0]) * FFT_SUBBANDS;
    int thresh = (high - low) / 3;
    if (beat.isBeatRange(low, high, thresh)) beats[1] = filterFrecuencyButtons[3].getVal();

    for (int i = low; i <= high; i++) {

        amps[1] += beat.getBand(i);

    }
    amps[1] = amps[1] * filterFrecuencyButtons[3].getVal() / (filterWidth[1] * FFT_SUBBANDS);

    low = filterFrecuencyButtons[1].getVal() * FFT_SUBBANDS;
    high = (filterFrecuencyButtons[1].getVal() + filterWidth[1]) * FFT_SUBBANDS;
    thresh = (high - low) / 3;
    if (beat.isBeatRange(low, high, thresh)) beats[2] = filterFrecuencyButtons[4].getVal();

    for (int i = low; i <= high; i++) {

        amps[2] += beat.getBand(i);

    }
    amps[2] = amps[2] * filterFrecuencyButtons[4].getVal() / (filterWidth[2] * FFT_SUBBANDS);

    low = filterFrecuencyButtons[2].getVal() * FFT_SUBBANDS;
    high = (filterFrecuencyButtons[2].getVal() + filterWidth[2]) * FFT_SUBBANDS;
    thresh = (high - low) / 3;
    if (beat.isBeatRange(low, high, thresh)) beats[3] = filterFrecuencyButtons[5].getVal();

    for (int i = low; i <= high; i++) {

        amps[3] += (beat.getBand(i) * beat.getBand(i));

    }
    amps[3] = amps[3] * filterFrecuencyButtons[5].getVal() / (filterWidth[3] * FFT_SUBBANDS);

}

void AudioInput::audioReceived(float* input, int bufferSize, int nChannels) {

    beat.audioReceived(input, bufferSize, nChannels);

    float maxValue = 1;
    for(int i = 0; i < bufferSize; i++) {
        if(abs(input[i]) > maxValue) {
            maxValue = abs(input[i]);
        }
    }
    for(int i = 0; i < bufferSize; i++) {
        input[i] /= maxValue;
    }

    fft->setSignal(input);

    float* curFft = fft->getAmplitude();
    memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());

    maxValue = 1;
    for(int i = 0; i < fft->getBinSize(); i++) {
        if(abs(audioBins[i]) > maxValue) {
            maxValue = abs(audioBins[i]);
        }
    }
    for(int i = 0; i < fft->getBinSize(); i++) {
        audioBins[i] /= maxValue;
    }

    soundMutex.lock();
    middleBins = audioBins;
    soundMutex.unlock();


}

void AudioInput::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor = frontColor_;
    backColor = backColor_;
    selectedColor = selectedColor_;

    for (int i = 0; i < filterFrecuencyButtons.size(); i++) {

        filterFrecuencyButtons[i].setColors(frontColor, backColor, selectedColor);

    }

    for (int i = 0; i < filterMiddleButtons.size(); i++) {

        filterMiddleButtons[i].setColors(frontColor, backColor, selectedColor);

    }

}

void AudioInput::mousePressed(int x, int y, int button) {

    if (x > position.x && x <= position.x + size.x &&
            y > position.y && y < position.y + size.y) {

        selected = !selected;

    }
}
