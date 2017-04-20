#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "ofMain.h"
#include "nanopanel.h"
#include "audioinput.h"

class ShaderManager
{
public:

    vector<ofShader> shaders;
    int index;

    ShaderManager();

    void setup();
    void update(float ellapsedTime_, vector<float> &shaderPanel_, AudioInput audioInput_);
    void begin();
    void end();


};

#endif // SHADERMANAGER_H
