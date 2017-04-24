#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"
#include "constants.h"


bool setSecondWindowDimensions(ofGLFWWindowSettings& settings) {
    // Check screens size and location
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    cout << "Number of screens found: " << count << endl;
    if (count>1) {
        int xM; int yM;
        glfwGetMonitorPos(monitors[1], &xM, &yM); // We take the second monitor
        const GLFWvidmode * desktopMode = glfwGetVideoMode(monitors[1]);

        settings.width = desktopMode->width;
        settings.height = desktopMode->height;
        settings.setPosition(ofVec2f(xM, yM));
        return true;
    } else {
        settings.width = Constants::OUTPUT_WIDTH; // Default settings if there is only one screen
        settings.height = Constants::OUTPUT_HEIGHT;
        settings.setPosition(ofVec2f(0, 0));
        return false;
    }
}


//========================================================================
int main( ){
	ofGLFWWindowSettings settings;

    settings.width = 1280;
    settings.height = 720;
    settings.setPosition(ofVec2f(0, 0));
    settings.resizable = true;
    settings.decorated = true;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

    setSecondWindowDimensions(settings);
    settings.resizable = false;
    settings.decorated = false;
    settings.shareContextWith = guiWindow;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);


	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);
	mainApp->gui = guiApp;

	ofRunApp(guiWindow, guiApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
