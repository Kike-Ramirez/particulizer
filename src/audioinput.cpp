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
    
    // Draw Filter 1 Button
    ofPushMatrix();
    ofSetColor(0);
    ofTranslate(position.x, position.y);
    ofTranslate(0.1 * size.x, 0.6 * size.y);
    ofDrawCircle(0, 0, 0.05 * size.y);
    ofRotate(filterValues[0] * 270);
    ofTranslate(0.03 * size.x, 0);
    ofSetColor(255);
    ofDrawCircle(0, 0, 0.01 * size.y);
    ofPopMatrix();

    
    // Draw Filter 2 Button
    ofPushMatrix();
    ofSetColor(0);
    ofTranslate(position.x, position.y);
    ofTranslate(0.2 * size.x, 0.6 * size.y);
    ofDrawCircle(0, 0, 0.05 * size.y);
    ofRotate(filterValues[1] * 270);
    ofTranslate(0.03 * size.x, 0);
    ofSetColor(255);
    ofDrawCircle(0, 0, 0.01 * size.y);
    ofPopMatrix();

    // Draw Filter 2 Button
    ofPushMatrix();
    ofSetColor(0);
    ofTranslate(position.x, position.y);
    ofTranslate(0.3 * size.x, 0.6 * size.y);
    ofDrawCircle(0, 0, 0.05 * size.y);
    ofRotate(filterValues[2] * 270);
    ofTranslate(0.03 * size.x, 0);
    ofSetColor(255);
    ofDrawCircle(0, 0, 0.01 * size.y);
    ofPopMatrix();


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

        ofSetColor(filterColors[0]);
        ofRect(0.25 * size_.x, (1 - filterValues[0]) * size_.y, 0.05 * size_.x, filterValues[0] * size_.y);

        ofSetColor(filterColors[1]);
        ofRect(0.5 * size_.x, (1 - filterValues[1]) * size_.y, 0.05 * size_.x, filterValues[1] * size_.y);
    
        ofSetColor(filterColors[2]);
        ofRect(0.75 * size_.x, (1 - filterValues[2]) * size_.y, 0.05 * size_.x, filterValues[2] * size_.y);
    
        ofSetColor(255);
    
        //ofFill();
        ofDrawBitmapString("AudioInput", 0.02 * size_.x, 0.08 * size_.y);

            ofTranslate(position_.x, position_.y + size_.y, 0.0);

            ofBeginShape();
            for (int i = 0; i < n; i++) {
                float xx = ofMap(i, 0, n, 0, size_.x );
                ofVertex(xx, -1 * sqrt(buffer[int(xx)]) * size_.y);
            }
            ofEndShape();
    
    ofNoFill();
    


    ofPopMatrix();

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

