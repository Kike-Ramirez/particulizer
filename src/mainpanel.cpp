#include "mainpanel.h"

MainPanel::MainPanel()
{

}

void MainPanel::setup(ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);

    PushButton button;

    button.setup(ofPoint(position.x + 0.025 * size.x, position.y + 0.025 * size.y), ofPoint(0.2* size.x, 0.95 * size.y), 1 );
    button.setLabel("Blackout");
    pushes.push_back(button);

    button.setup(ofPoint(position.x + 0.525 * size.x, position.y + 0.025 * size.y), ofPoint(0.2 * size.x, 0.45 * size.y), 1 );
    button.setLabel("Warping cal.");
    pushes.push_back(button);

    button.setup(ofPoint(position.x + 0.525 * size.x, position.y + 0.525 * size.y), ofPoint(0.2 * size.x, 0.45 * size.y), 1 );
    button.setLabel("Warping SET");
    pushes.push_back(button);

    button.setup(ofPoint(position.x + 0.775 * size.x, position.y + 0.025 * size.y), ofPoint(0.2 * size.x, 0.45 * size.y), 1 );
    button.setLabel("Mapping cal.");
    pushes.push_back(button);

    button.setup(ofPoint(position.x + 0.775 * size.x, position.y + 0.525 * size.y), ofPoint(0.2 * size.x, 0.45 * size.y), 1 );
    button.setLabel("Mapping SET");
    pushes.push_back(button);

    alphaMain.setup(ofPoint(position.x + 0.275 * size.x, position.y + 0.025 * size.y), ofPoint(0.2 * size.x, 0.95 * size.y), 0 );

    mainSlider.setup(ofPoint(0, 0.4 * ofGetHeight()), ofPoint(0.25 * ofGetWidth(), 0.1 * ofGetHeight()), 3);

}


void MainPanel::update(NanoKontrol2 &nano_) {

    pushes[0].update(nano_.getVal(42));
    pushes[1].update(nano_.getVal(58));
    pushes[2].update(nano_.getVal(59));
    pushes[3].update(nano_.getVal(61));
    pushes[4].update(nano_.getVal(62));

    alphaMain.update(nano_.getRotary(0));

    mainSlider.update(nano_.getSlider(0));

}

void MainPanel::display() {

    for (int i = 0; i < pushes.size(); i++) pushes[i].display();
    alphaMain.display();
    mainSlider.display();
}

void MainPanel::setBackColor(ofColor color_) {

    backColor.set(color_);

}

void MainPanel::setFrontColor(ofColor color_) {

    frontColor.set(color_);
}
