#include "layer.h"

Layer::Layer()
{


}

void Layer::setup(ofPoint position_, ofPoint size_) {

    position = ofPoint(position_.x, position_.y);
    size = ofPoint(size_.x, size_.y);
    selected = false;
    alpha = 0;
    canvasLayer.allocate(1024, 768);

    canvasLayer.begin();
    ofBackground(0);
    canvasLayer.end();

}

void Layer::update(const ofFbo &effectCanvas_) {

    canvasLayer.begin();
    ofBackground(0);
    effectCanvas_.draw(0, 0, canvasLayer.getWidth(), canvasLayer.getHeight());
    canvasLayer.end();

}

void Layer::display() {

    ofPushMatrix();
    ofTranslate(position.x, position.y);

    float greyLevel = 255 / 2;
    float alphaLevel = 255 - greyLevel;

    ofColor grey = ofColor(150);
    grey.lerp(ofColor(255, 75, 75), alpha);

    ofSetColor(grey);
    ofFill();

    ofRect(0, 0, size.x, size.y);

    canvasLayer.draw(0.05 * size.x, 0.05 * size.y, 0.9 * size.x, 0.9 * size.x * 9 / 16.0);

    ofSetColor(greyLevel - 30);
    ofRect(0.05 * size.x, 0.65 * size.y, 0.9 * size.x, 0.3 * size.y);

    if (selected) {

        ofSetColor(255, 0, 0);
        ofSetLineWidth(4);
        ofNoFill();
        ofRect(0.05 * size.x, 0.05 * size.y, 0.9 * size.x, 0.9 * size.y);
        ofSetLineWidth(1);

    }

    ofPopMatrix();


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
