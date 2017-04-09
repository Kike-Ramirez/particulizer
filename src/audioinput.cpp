#include "audioinput.h"

AudioInput::AudioInput()
{

}

void AudioInput::setup(ofBaseApp *appPtr, ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);
    canvas.allocate(size.x, size.y);

    bufferSize = 2048;

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
    
    filterFrequencies.push_back(0.25 * fft->getBinSize());
    filterFrequencies.push_back(0.5 * fft->getBinSize());
    filterFrequencies.push_back(0.75 * fft->getBinSize());

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

    // Insert Lower pads
    button.setup(ofPoint(position.x + size.x * 0.010, position.y + size.y * 0.64 + size.x * 0.2), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.260, position.y + size.y * 0.64 + size.x * 0.2), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.510, position.y + size.y * 0.64 + size.x * 0.2), ofPoint(size.x * 0.07, size.x * 0.07), 2);
    filterFrecuencyButtons.push_back(button);

    filterValues.push_back(0.6);
    filterValues.push_back(0.7);
    filterValues.push_back(0.8);
    
    filterColors.push_back(ofColor(255, 255, 0));
    filterColors.push_back(ofColor(255, 0, 255));
    filterColors.push_back(ofColor(0, 255, 255));
    
    


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
    ofPopMatrix();
    
    for (int i = 0; i < 3; i++) {

        filterFrecuencyButtons[i].update(filterValues[i]);
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

            ofSetColor(filterColors[i]);
            ofRect(filterFrecuencyButtons[i].getVal() * size_.x, (1 - filterFrecuencyButtons[i+3].getVal()) * size_.y, 0.05 * size_.x, filterFrecuencyButtons[i+3].getVal() * size_.y);

        }
    
        ofSetColor(255);
    
        //ofFill();
        ofDrawBitmapString("AudioInput", 0.02 * size_.x, 0.08 * size_.y);

            ofTranslate(position_.x, position_.y + size_.y, 0.0);
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

void AudioInput::update(ofxKorgNanoKontrol &nano) {

    cout << nano.getVal(1, K_TYPE_POT) << endl;

    for (int i = 0; i < 3; i++) {

        filterFrecuencyButtons[i].update(nano.getVal(i+1, K_TYPE_POT) / 127.0);
        filterFrecuencyButtons[i+3].update(nano.getVal(i+1, K_TYPE_SLIDER) / 127.0);
        filterFrecuencyButtons[i+6].update(nano.getButtonVal(2*i+3, K_TYPE_BUTTON) / 127.0);
        filterFrecuencyButtons[i+9].update(nano.getButtonVal(2*i+4, K_TYPE_BUTTON) / 127.0);


    }
}

void AudioInput::audioReceived(float* input, int bufferSize, int nChannels) {

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

