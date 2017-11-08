#pragma once

#include "ofMain.h"
#include "ofApp.h"

class LeftApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void drawMap();
    
    bool isMap;
    shared_ptr<ofApp> main;
    PostEffect pe;
};


