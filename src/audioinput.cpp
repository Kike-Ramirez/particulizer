#include "audioinput.h"

audioInput::audioInput()
{

}

void audioInput::setup(ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);
    canvas.allocate(size.x, size.y);

    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);

    drawBins.resize(fft->getBinSize());
    middleBins.resize(fft->getBinSize());
    audioBins.resize(fft->getBinSize());

    // 0 output channels,
    // 1 input channel
    // 44100 samples per second
    // [bins] samples per buffer
    // 4 num buffers (latency)

    ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);

}

void audioInput::plot(vector<float>& buffer, float scale, float offset) {


}
void audioInput::audioReceived(float* input, int bufferSize, int nChannels) {}
void audioInput::display() {}
