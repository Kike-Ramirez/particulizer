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


}

void AudioInput::display(ofTrueTypeFont coolvetica) {


    ofPushMatrix();
    ofTranslate(position.x, position.y);

    soundMutex.lock();
    drawBins = middleBins;
    soundMutex.unlock();

    ofSetColor(150);
    ofFill();
    ofRect(0, 0, size.x, size.y);
    ofSetColor(255);
    coolvetica.drawString("Frequency Domain", 0.02 * size.x, 0.08 * size.y);

    ofPopMatrix();

    plot(drawBins, ofPoint(position.x, position.y + size.y/2), ofPoint(size.x/2, size.y/2));


}

void AudioInput::plot(vector<float>& buffer, ofPoint position_, ofPoint size_) {


    int n = buffer.size();

    ofPushMatrix();
        ofTranslate(position_.x, position_.y);

        ofSetColor(0);
        ofFill();
        ofRect(0, 0, size_.x, size_.y);

        ofNoFill();
        ofSetColor(255);
        ofRect(0, 0, size_.x, size_.y);

        //ofFill();
        ofDrawBitmapString("AudioInput", 0.02 * size_.x, 0.08 * size_.y);

            ofTranslate(position_.x, position_.y + size_.y, 0.0);

            ofBeginShape();
            for (int i = 0; i < n; i++) {
                float xx = ofMap(i, 0, n, 0, size_.x );
                ofVertex(xx, -1 * sqrt(buffer[int(xx)]) * size_.y);
            }
            ofEndShape();


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

