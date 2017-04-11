#ifndef NANOPANEL_H
#define NANOPANEL_H

#include "ofMain.h"
#include "nanokontrol2.h"
#include "button.h"


class NanoPanel
{
public:

    ofPoint position;
    ofPoint size;
    ofColor frontColor;
    ofColor backColor;

    NanoPanel();

    void setup(ofPoint position_, ofPoint size_);
    void setPanel(int firstDeck_, int lastDeck_);
    void update(NanoKontrol2 & nano);
    void display();

private:

    int firstDeck;
    int lastDeck;

    vector<Button> buttons;

    void loadButtons();

};

#endif // NANOPANEL_H
