#pragma once

#include "ofMain.h"
#include "DataPoints.hpp"
#include "MeshEarth.hpp"
#include "CustomCam.hpp"
#include "PostEffect.hpp"
#include "DataCloud.hpp"

#include "ofxOsc.h"

struct DataRecord {
    ofVec2f coord;
    string country;
    string city;
    string reason;
    string age;
    bool isMale;
};

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
    
    DataRecord latest;
private:
    const int PORT = 8032;
    ofxOscReceiver receiver;
    
    int fcnt;
    
    
};
