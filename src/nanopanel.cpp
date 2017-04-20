#include "nanopanel.h"

NanoPanel::NanoPanel()
{

}

void NanoPanel::setup(ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);

    firstDeck = 4;
    lastDeck = 7;

    frontColor = ofColor(255);
    backColor = ofColor(0);

    loadButtons();

}

void NanoPanel::loadButtons() {

    float numDecks = lastDeck - firstDeck + 1;

    for (int i = firstDeck; i <= lastDeck; i++) {

        float deckWidth = size.x * 0.90 / numDecks;
        float deckHeight = size.y * 0.90;

        float posXDeck = position.x + (i - firstDeck) * (size.x / numDecks) + 0.025 * size.x;
        float posYDeck = position.y; // + 0.05 * size.y;

        Button button;
        PushButton pushButton;

        float radioRotary = 0.3 * deckWidth;

        button.setup(ofPoint(posXDeck + 0.65 * deckWidth, posYDeck + 0.2 * deckHeight), ofPoint(radioRotary, radioRotary), 1);
        button.setColors(frontColor, backColor, selectedColor);
        buttons.push_back(button);

        button.setup(ofPoint(posXDeck + 0.5 * deckWidth, posYDeck + 0.4 * deckHeight), ofPoint(0.3 * deckWidth, deckHeight * 0.6), 0);
        button.setColors(frontColor, backColor, selectedColor);
        buttons.push_back(button);

        button.setup(ofPoint(posXDeck + 0.15 * deckWidth, posYDeck + 0.4 * deckHeight), ofPoint(0.15 * deckWidth, deckHeight * 0.15), 2);
        button.setColors(frontColor, backColor, selectedColor);
        buttons.push_back(button);

        pushButton.setup(ofPoint(posXDeck + 0.15 * deckWidth, posYDeck + 0.6 * deckHeight), ofPoint(0.15 * deckWidth, deckHeight * 0.15), 1);
        pushButton.setColors(frontColor, backColor, selectedColor);
        midButtons.push_back(pushButton);

        button.setup(ofPoint(posXDeck + 0.15 * deckWidth, posYDeck + 0.8 * deckHeight), ofPoint(0.15 * deckWidth, deckHeight * 0.15), 2);
        button.setColors(frontColor, backColor, selectedColor);
        buttons.push_back(button);

    }

}
void NanoPanel::setPanel(int firstDeck_, int lastDeck_) {

    buttons.clear();

    firstDeck = firstDeck_;
    lastDeck = lastDeck_;

    loadButtons();

}

void NanoPanel::update(NanoKontrol2 &nano) {

    for (int i = firstDeck; i <= lastDeck; i++) {

        buttons[(i - firstDeck) * 4].update(nano.getRotary(i));
        buttons[(i - firstDeck) * 4 + 1].update(nano.getSlider(i));
        buttons[(i - firstDeck) * 4 + 2].update(nano.getUpperBtn(i));
        buttons[(i - firstDeck) * 4 + 3].update(nano.getLowerBtn(i));
        midButtons[(i - firstDeck)].update(nano.getMidBtn(i));
        cout << midButtons[(i - firstDeck)].getVal() << " ";
    }

    cout << endl;


}

void NanoPanel::display() {

    for (int i = 0; i < buttons.size(); i++) {

        buttons[i].display();

    }

    for (int i = 0; i < midButtons.size(); i++) {

        midButtons[i].display();

    }


}

void NanoPanel::setColors(ofColor frontColor_, ofColor backColor_, ofColor selectedColor_) {

    frontColor = frontColor_;
    backColor = backColor_;
    selectedColor = selectedColor_;

    for (int i = 0; i < buttons.size(); i++) {

        buttons[i].setColors(frontColor, backColor, selectedColor);
    }

}
