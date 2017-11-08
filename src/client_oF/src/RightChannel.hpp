#pragma once

#include "ofMain.h"
#include "ofApp.h"

class RightApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    shared_ptr<ofApp> main;
    ofCamera cam;
    ofVec3f la, up;
    ofMatrix4x4 mat;
    bool isFocus = true;
    
    PostEffect pe;
};

