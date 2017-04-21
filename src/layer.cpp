#include "layer.h"

Layer::Layer()
{


}

void Layer::setup(ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);
    selected = false;
    alpha = 0;

    frontColor = ofColor(155);
    backColor = ofColor(0);
    selectedColor = ofColor(255);

    canvas.allocate(Constants::OUTPUT_WIDTH, Constants::OUTPUT_HEIGHT);

    canvas.begin();
    ofBackground(0);
    canvas.end();

    // Insert buttons into Audio Display

    Button button = Button();

    float scaleButtons = 0.05;

    // Insert Rotarys
    button.setup(ofPoint(position.x + size.x * 0.155, position.y + size.y * 0.70), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 1);
    buttons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.405, position.y + size.y * 0.70), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 1);
    buttons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.655, position.y + size.y * 0.70), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 1);
    buttons.push_back(button);

    // Insert Sliders
    button.setup(ofPoint(position.x + size.x * 0.130, position.y + size.y * 0.75), ofPoint(size.x * scaleButtons, size.x * 0.18), 0);
    buttons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.380, position.y + size.y * 0.75), ofPoint(size.x * scaleButtons, size.x * 0.18), 0);
    buttons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.630, position.y + size.y * 0.75), ofPoint(size.x * scaleButtons, size.x * 0.18), 0);
    buttons.push_back(button);

    // Insert Upper pads
    button.setup(ofPoint(position.x + size.x * 0.050, position.y + size.y * 0.75), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 2);
    buttons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.300, position.y + size.y * 0.75), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 2);
    buttons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.550, position.y + size.y * 0.75), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 2);
    buttons.push_back(button);

    // Insert Lower pads
    button.setup(ofPoint(position.x + size.x * 0.050, position.y + size.y * 0.67 + size.x * 0.2), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 2);
    buttons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.300, position.y + size.y * 0.67 + size.x * 0.2), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 2);
    buttons.push_back(button);
    button.setup(ofPoint(position.x + size.x * 0.550, position.y + size.y * 0.67 + size.x * 0.2), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 2);
    buttons.push_back(button);

    // Insert Mid pads
    PushButton button2;
    button2.setup(ofPoint(position.x + size.x * 0.050, position.y + size.y * 0.71 + size.x * 0.1), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 1);
    button2.setLabel("");
    midButtons.push_back(button2);
    button2.setup(ofPoint(position.x + size.x * 0.300, position.y + size.y * 0.71 + size.x * 0.1), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 1);
    button2.setLabel("");
    midButtons.push_back(button2);
    button2.setup(ofPoint(position.x + size.x * 0.550, position.y + size.y * 0.71 + size.x * 0.1), ofPoint(size.x * scaleButtons, size.x * scaleButtons), 1);
    button2.setLabel("");
    midButtons.push_back(button2);


}

void Layer::update(NanoKontrol2 & nano) {

    if (selected) {
        // Actualizamos valores del controlador MIDI
        for (int i = 0; i < 3; i++) {

            buttons[i].update(nano.getRotary(i + 1));
            buttons[i+3].update(nano.getSlider(i + 1));
            buttons[i+6].update(nano.getUpperBtn(i + 1));
            buttons[i+9].update(nano.getLowerBtn(i + 1));

            midButtons[i].update(nano.getMidBtn(i+1));

        }
    }

}

void Layer::displayCanvas(const ofFbo &effectCanvas_) {

    canvas = effectCanvas_;

}


bool Layer::isSelected() {

    return selected;

}

void Layer::display() {

    ofPushMatrix();
    ofTranslate(position.x, position.y);

    ofSetColor(255);
    float dist = (0.9 * size.x - 0.6 * size.y * Constants::ASPECT_RATIO) * 0.5;

    canvas.draw(0.05 * size.x + dist, 0.05 * size.y, 0.6 * size.y * Constants::ASPECT_RATIO, 0.6 * size.y);

    ofSetColor(frontColor);
    ofNoFill();
    ofDrawRectangle(0.05 * size.x, 0.05 * size.y, 0.9 * size.x, 0.6 * size.y);

    ofSetColor(selectedColor, alpha * 255);
    ofSetLineWidth(4);
    ofDrawRectangle(0.05 * size.x, 0.05 * size.y, 0.9 * size.x, 0.6 * size.y);
    ofSetLineWidth(1);

    //ofSetColor(greyLevel - 30);
    //ofRect(0.05 * size.x, 0.65 * size.y, 0.9 * size.x, 0.3 * size.y);

    if (selected) {

        ofSetColor(selectedColor);
        ofSetLineWidth(1);
        ofNoFill();
        ofRect(0.02 * size.x, 0.02 * size.y, 0.96 * size.x, 0.96 * size.y);

    }

    ofPopMatrix();

    for (int i = 0; i < buttons.size(); i++) {

        buttons[i].display();

    }

    for (int i = 0; i < midButtons.size(); i++) {

        midButtons[i].display();

    }


}

void Layer::setAlpha(float alpha_) {

    alpha = alpha_;

}

void Layer::select() {

    selected = true;

}

void Layer::unselect() {

    selected = false;

}

void Layer::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor.set(frontColor_);
    backColor.set(backColor_);
    selectedColor.set(selectedColor_);

    for (int i = 0; i < buttons.size(); i++) {

        buttons[i].setColors(frontColor, backColor, selectedColor);
    }

    for (int i = 0; i < midButtons.size(); i++) {

        midButtons[i].setColors(frontColor, backColor, selectedColor);
    }

}
