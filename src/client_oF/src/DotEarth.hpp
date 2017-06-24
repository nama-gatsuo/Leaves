#pragma once
#include "ofMain.h"

class DotEarth {
public:
    DotEarth();
    void setup();
    void draw();
private:
    ofVboMesh mesh;
    ofImage img;
};
