#pragma once

#include "ofMain.h"
#include "DotEarth.hpp"
#include "DataPoints.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

private:
    DotEarth de;
    DataPoints dp;
    ofEasyCam cam;
};
