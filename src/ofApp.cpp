#include <string>
#include "ofApp.h"

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

//

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofSetColor(255);
    this->gui->output.canvas.getTexture().draw(0,0);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if ((key == 'F') || (key == 'f')) {

        ofToggleFullscreen();

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
