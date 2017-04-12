#ifndef EFFECT_TEMPLATE_H
#define EFFECT_TEMPLATE_H

#include "ofMain.h"

class Effect_Template {

    public:                             // place public functions or variables declarations here

    // methods, equivalent to specific functions of your class objects
    void setup(ofPoint _position, ofPoint _size, vector<string> _nanoKorgTexts, string name_);	// setup method, use this to setup your object's initial state
    void update();                      // update method, used to refresh your objects properties
    void drawDisplay(const ofTrueTypeFont & coolvetica_);                 // draw method, this where you'll do the object's drawing
    void drawOutput();                  // draw method, this where you'll do the object's drawing
    void setOffset(int _offSet);        // set new Offset for display
    float getOffset();                  // Get Offset for display
    void select();                      // Select display
    void unselect();                    // Unselect display
    bool isActive();                    // Return whether the effect is selected or not
    bool isAssigned();                  // Returns true if the effect is being displayed in any layer
    void assign(int id);                // Assigns the effect to a layer

    // variables to setup & display
    ofPoint position;                   // Position of the display of the Effect
    ofPoint size;                       // Size of the display of the Effect
    vector<string> nanoKorgTexts;       // Texts for MIDI tablet
    bool selected;                      // Flag to indicate the effect is selected by the user
    int assigned;                       // Assignation indication (0 - none; 1 - layerA; 2 - layerB)
    float offSet;                       // Offset to display the window width
    string name;                        // Name of the effect

    // Canvas
    ofFbo effectCanvas;                 // Canvas to render the effect
    ofFbo smallCanvas;                  // Small canvas to be displayed on Effect Layer Preview

    // Parameters for live output
    float speed;                        // Speed variable (0 - 1)
    float audioLevel;                   // Main audio Level
    vector<float> audioFiltersLevel;    // Independent levels for each audioFilter;
    ofColor frontColor;                 // Front Color
    ofColor backColor;                  // Backtround Color
    ofColor selectedColor;              // Selected Color

    int dim;        // size
    ofColor color;  // color using ofColor type

    Effect_Template();  // constructor - used to initialize an object, if no properties are passed the program sets them to the default value
    private: // place private functions or variables declarations here

}; // don't forget the semicolon!

#endif // EFFECT_TEMPLATE_H
