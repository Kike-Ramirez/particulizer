#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;


    settings.width = 1280;
    settings.height = 720;
	settings.setPosition(ofVec2f(300,0));
	settings.resizable = true;
    settings.monitor = 0;
    settings.decorated = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

    settings.width = 1280;
    settings.height = 720;
	settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    settings.monitor = 1;

    settings.decorated = true;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);
	mainApp->gui = guiApp;

	ofRunApp(guiWindow, guiApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
