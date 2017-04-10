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
    button.setup(ofPoint(position.x + size.x * 0.125, position.y + size.y * 0.57), ofPoint(size.x * 0.07, size.x * 0.07), 1);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.375, position.y + size.y * 0.57), ofPoint(size.x * 0.07, size.x * 0.07), 1);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.625, position.y + size.y * 0.57), ofPoint(size.x * 0.07, size.x * 0.07), 1);
    filterFrecuencyButtons.push_back(button);

    // Insert Sliders
    button.setup(ofPoint(position.x + size.x * 0.090, position.y + size.y * 0.64), ofPoint(size.x * 0.07, size.x * 0.27), 0);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.340, position.y + size.y * 0.64), ofPoint(size.x * 0.07, size.x * 0.27), 0);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.590, position.y + size.y * 0.64), ofPoint(size.x * 0.07, size.x * 0.27), 0);
    filterFrecuencyButtons.push_back(button);

    // Insert Upper pads
    button.setup(ofPoint(position.x + size.x * 0.010, position.y + size.y * 0.64), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.260, position.y + size.y * 0.64), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.510, position.y + size.y * 0.64), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);

    // Insert Mid pads
    button.setup(ofPoint(position.x + size.x * 0.010, position.y + size.y * 0.64 + size.x * 0.1), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.260, position.y + size.y * 0.64 + size.x * 0.1), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.510, position.y + size.y * 0.64 + size.x * 0.1), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);

    // Insert Lower pads
    button.setup(ofPoint(position.x + size.x * 0.010, position.y + size.y * 0.64 + size.x * 0.2), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.260, position.y + size.y * 0.64 + size.x * 0.2), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.510, position.y + size.y * 0.64 + size.x * 0.2), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);
    
    filterColors.push_back(ofColor(255, 255, 0));
    filterColors.push_back(ofColor(255, 0, 255));
    filterColors.push_back(ofColor(0, 255, 255));

    filterWidth.push_back(0.1);
    filterWidth.push_back(0.1);
    filterWidth.push_back(0.1);

    for (int i = 0; i < 4; i++) {

        beats.push_back(0.0);

    }
    


}

void AudioInput::display(ofTrueTypeFont coolvetica) {

    // Copy data
    soundMutex.lock();
    drawBins = middleBins;
    soundMutex.unlock();

    // Draw BackPanel
    ofPushMatrix();
    ofTranslate(position.x, position.y);
    ofSetColor(150);
    ofFill();
    ofRect(0, 0, size.x, size.y);
    ofSetColor(255);
    coolvetica.drawString("Frequency Domain", 0.02 * size.x, 0.08 * size.y);

    for (int i = 0; i < 4; i++) {

        float alpha = 255 * beats[i];
        ofSetColor(0);
        ofFill();
        ofDrawRectangle(size.x * 0.7, (0.64 + i * 0.09) * size.y, 0.25 * size.x, 0.05 * size.y );
        if (i > 0) ofSetColor(filterColors[i - 1], alpha);
        else ofSetColor(255, alpha);
        ofFill();
        ofDrawRectangle(size.x * 0.7, (0.64 + i * 0.09) * size.y, 0.25 * size.x, 0.05 * size.y );
        if (i > 0) ofSetColor(filterColors[i - 1]);
        else ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(size.x * 0.7, (0.64 + i * 0.09) * size.y, 0.25 * size.x, 0.05 * size.y );
    }

    ofPopMatrix();
    
    for (int i = 0; i < 3; i++) {

    }

    for (int i = 0; i < filterFrecuencyButtons.size(); i++) {

        filterFrecuencyButtons[i].display();

    }

    plot(drawBins, ofPoint(position.x, position.y), ofPoint(size.x, size.y/2));


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
    ofSetColor(255);
    ofRect(0, 0, size_.x, size_.y);

    for (int i = 0; i < 3; i++) {

        ofFill();
        ofSetColor(filterColors[i], beats[i+1] * 255);
        ofRect(filterFrecuencyButtons[i].getVal() * size_.x, (1 - filterFrecuencyButtons[i+3].getVal()) * size_.y, filterWidth[i] * size_.x, filterFrecuencyButtons[i+3].getVal() * size_.y);
        ofSetColor(filterColors[i]);
        ofNoFill();
        ofRect(filterFrecuencyButtons[i].getVal() * size_.x, (1 - filterFrecuencyButtons[i+3].getVal()) * size_.y, filterWidth[i] * size_.x, filterFrecuencyButtons[i+3].getVal() * size_.y);

    }
    
    ofSetColor(255);

    //ofFill();
    ofDrawBitmapString("AudioInput", 0.02 * size_.x, 0.1 * size_.y);

    ofTranslate(0, size_.y, 0.0);
    ofSetLineWidth(0.1);
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

    // Actualizamos valores del controlador MIDI
    for (int i = 0; i < 3; i++) {

        filterFrecuencyButtons[i].update(nano.getRotary(i + 1));
        filterFrecuencyButtons[i+3].update(nano.getSlider(i + 1));
        filterFrecuencyButtons[i+6].update(nano.getUpperBtn(i + 1));
        filterFrecuencyButtons[i+9].update(nano.getMidBtn(i + 1));
        filterFrecuencyButtons[i+12].update(nano.getLowerBtn(i+1));

        float step = 0.001;

        if (nano.getUpperBtn(i+1) >= 1 && filterWidth[i] <= 1) filterWidth[i] += step;
        if (nano.getLowerBtn(i+1) >= 1 && filterWidth[i] >= 0) filterWidth[i] -= step;

    }

    // Calculamos nuevos beats
    beat.update(ofGetElapsedTimeMillis());

    for (int i = 0; i < beats.size(); i++) beats[i] = beats[i] * 0.95;

    if (beat.isBeat(0)) beats[0] = 1;
    if (beat.isHat()) beats[1] = 1;
    if (beat.isKick()) beats[2] = 1;
    if (beat.isSnare()) beats[3] = 1;

}

void AudioInput::audioReceived(float* input, int bufferSize, int nChannels) {

    beat.audioReceived(input, bufferSize, nChannels);

    float maxValue = 0;
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

    maxValue = 0;
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

