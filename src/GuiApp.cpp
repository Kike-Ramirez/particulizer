/*
 * GuiApp.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: arturo
 */

#include "GuiApp.h"

void GuiApp::setup(){
	parameters.setName("parameters");
	parameters.add(radius.set("radius",50,1,100));
    parameters.add(colorFront.set("color front",255,ofColor(0,0),255));
    parameters.add(colorBack.set("color back",0,ofColor(0,0),255));
    parameters.add(fullScreen.set("full screen", false));
    gui.setup(parameters);
	ofBackground(0);
	ofSetVerticalSync(false);
}

void GuiApp::update(){

}

void GuiApp::draw(){
	gui.draw();
}
