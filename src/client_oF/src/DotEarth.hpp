#pragma once
#include "ofMain.h"

class DotEarth {
public:
    DotEarth();
    void setup(float rad);
    void draw();
private:
    ofVboMesh mesh;
    ofImage img;
    ofVboMesh black;
};
