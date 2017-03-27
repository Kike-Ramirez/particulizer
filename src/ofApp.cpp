#include <string>
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
	ofSetCircleResolution(200);
    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();

    effectCanvas.allocate(screenWidth, screenHeight);

}

//--------------------------------------------------------------
void ofApp::update(){

    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();

//    ofSetFullscreen(gui->fullScreen);
    effectCanvas.begin();
    ofBackground(0);
    gui->output.draw(0,0, effectCanvas.getWidth(), effectCanvas.getHeight());
    effectCanvas.end();

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofSetColor(255);
    effectCanvas.draw(0,0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if ((key == 'F') || (key == 'f')) {

        //gui->fullScreen = !gui->fullScreen;

    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

    effectCanvas.allocate(w, h);

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
