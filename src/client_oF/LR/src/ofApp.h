#pragma once

#include "ofMain.h"
#include "DataPoints.hpp"
#include "MeshEarth.hpp"
#include "CustomCam.hpp"
#include "PostEffect.hpp"
#include "DataCloud.hpp"

#include "ofxOsc.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    
    MeshEarth me;
    DataPoints dp;
    DataCloud dc;
    
    CustomCam cam;
    PostEffect pe;
    
private:
    const int PORT = 8032;
    const bool DEBUG = false;
    ofxOscReceiver receiver;
    
    float fcnt;

};
