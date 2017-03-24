#include "ofApp.h"
#include <string>

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
	ofSetCircleResolution(200);
    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::update(){

    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(gui->colorBack);
    ofSetColor(gui->colorFront);
    ofDrawCircle(screenWidth*0.5,screenHeight*0.5,gui->radius);

    ofDrawBitmapString("particulizer_dev",20,20);
    ofDrawBitmapString("FrameRate: " + std::to_string(int(ofGetFrameRate()*100)/100),20,50);
    ofDrawBitmapString("Resolution: " + std::to_string(screenWidth) + "-" + std::to_string(screenHeight), 20, 70);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
