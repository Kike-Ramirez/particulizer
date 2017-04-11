#include "nanokontrol2.h"

NanoKontrol2::NanoKontrol2() {


}

NanoKontrol2::~NanoKontrol2() {
    // clean up
    midiIn.closePort();
    midiIn.removeListener(this);
    cout << "MIDI port is closed" << endl;
}

void NanoKontrol2::setup()
{
    for (int i = 0; i < 90; i++) {

        nanoValues.push_back(0);

    }

    portNum = findKontrolPort();

    midiIn.openPort(portNum);

    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn.ignoreTypes(false, false, false);

    // add ofApp as a listener
    midiIn.addListener(this);

    // print received messages to the console
    midiIn.setVerbose(true);

}

int NanoKontrol2::findKontrolPort() {
    unsigned int nPorts = midiIn.getNumPorts();
    std::string portName;

    for ( uint i=0; i < nPorts; i++ ) {
        portName = midiIn.getPortName(i);
        if(portName.find("nanoKONTROL") != std::string::npos) {
            cout << "Defaulting to port " << i << endl;
            return i;
        }
    }
    cout << "Cannot find nanoKONTROL or nanoKONTROL2" << endl;
    cout << "Check your midi device connection or try to set port number manually" << endl;

    return -1;

}

void NanoKontrol2::getListMidiDevices() {

    // print input ports to console
    unsigned int nPorts = midiIn.getNumPorts();
    cout << "port count: " << nPorts << endl;
    midiIn.listPorts(); // via instance
}

void NanoKontrol2::newMidiMessage(ofxMidiMessage& msg) {

    // make a copy of the latest message
    midiMessage = msg;

    /*
    cout << "Received : " << ofxMidiMessage::getStatusString(midiMessage.status) << endl;
    cout << "channel: " << midiMessage.channel << endl;
    cout << "pitch: " << midiMessage.pitch << endl;
    cout << "velocity: " << midiMessage.velocity << endl;
    cout << "control: " << midiMessage.control << endl;
    cout << "value : " << msg.value << endl;
    cout << "delta: " << midiMessage.deltatime << endl;
    */

    nanoValues[midiMessage.control] = msg.value / 127.0;

}

float NanoKontrol2::getVal(int number_) {

    if (number_>= 0 && number_ < nanoValues.size()) return nanoValues[number_];
    else return -1;
}

float NanoKontrol2::getSlider(int number_) {

    if (number_>= 0 && number_ < 8) return nanoValues[number_];
    else return -1;
}

float NanoKontrol2::getRotary(int number_) {

    if (number_>= 0 && number_ < 8) return nanoValues[number_ + 16];
    else return -1;
}

float NanoKontrol2::getUpperBtn(int number_) {

    if (number_>= 0 && number_ < 8) return nanoValues[number_ + 32];
    else return -1;
}


float NanoKontrol2::getMidBtn(int number_) {

    if (number_>= 0 && number_ < 8) return nanoValues[number_ + 48];
    else return -1;
}


float NanoKontrol2::getLowerBtn(int number_) {

    if (number_>= 0 && number_ < 8) return nanoValues[number_ + 64];
    else return -1;
}
