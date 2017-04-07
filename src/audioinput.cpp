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

void AudioInput::display() {


    ofPushMatrix();
    ofTranslate(position.x, position.y);

    soundMutex.lock();
    drawBins = middleBins;
    soundMutex.unlock();

    ofSetColor(150);
    ofFill();
    ofRect(0, 0, size.x, size.y);
    ofSetColor(255);
    ofDrawBitmapString("Frequency Domain", 0.01 * size.x, 0.01 * size.y);

    ofPopMatrix();

    plot(drawBins, ofPoint(position.x + size.x/2, position.y), ofPoint(size.x/2, size.y/2));


}

void AudioInput::plot(vector<float>& buffer, ofPoint position, ofPoint height) {


    int n = buffer.size();

    glPushMatrix();
        glTranslatef(position.x, position.y, 0);

        ofSetColor(0);
        ofFill();
        ofRect(0, 0, size.x, size.y);

        ofNoFill();
        ofSetColor(255);
        ofRect(0, 0, size.x, size.y);

        ofFill();
        ofDrawBitmapString("AudioInput", 0.01 * size.x, 0.01 * size.y);

        glPushMatrix();

            glTranslatef(0, size.y * 0.5, 0.0);

            ofBeginShape();
            for (int i = 0; i < n; i++) {
                float xx = ofMap(i, 0, n, 0, size.x );
                ofVertex(xx, sqrt(buffer[i]) * size.y);
            }
            ofEndShape();

        glPopMatrix();

    glPopMatrix();

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
        cout << "audioBins: " << audioBins[i] << endl;
    }

    soundMutex.lock();
    middleBins = audioBins;
    soundMutex.unlock();

}

