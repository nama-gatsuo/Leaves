#pragma once

#include "ofMain.h"
#include "DataPoints.hpp"
#include "MeshEarth.hpp"
#include "CustomCam.hpp"
#include "PostEffect.hpp"

#include "ofxOsc.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

private:
    const int PORT = 8032;
    const bool DEBUG = false;
    ofxOscReceiver receiver;
    
    MeshEarth me;
    DataPoints dp;
    CustomCam cam;
    ofVboMesh sphere;
    PostEffect pe;
    float fcnt;
    
};
