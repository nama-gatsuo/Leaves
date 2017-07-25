#pragma once

#include "ofMain.h"
#include "DotEarth.hpp"
#include "DataPoints.hpp"
#include "CustomCam.hpp"
#include "PostEffect.hpp"

#include "ofxOsc.h"
#include "ofxSyphon.h"

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
    
    DotEarth de;
    DataPoints dp;
    CustomCam cam;
    
    PostEffect pe;
    float fcnt;
    
    ofxSyphonServer server;
};
