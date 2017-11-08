#pragma once

#include "ofMain.h"
#include "DataPoints.hpp"
#include "MeshEarth.hpp"
#include "CustomCam.hpp"
#include "PostEffect.hpp"
#include "DataCloud.hpp"

#include "ofxOsc.h"

const static int WINDOW_WIDTH = 1280;
const static int WINDOW_HEIGHT = 720;
const static int CANVAS_WIDTH = 960;
const static int CANVAS_HEIGHT = 720;
const static int CANVAS_OFFSET = (WINDOW_WIDTH - CANVAS_WIDTH) / 2;

struct DataRecord {
    ofVec2f coord;
    ofVec3f pos;
    
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
    int countFromBang = 0;
private:
    const int PORT = 8032;
    ofxOscReceiver receiver;
    
};
