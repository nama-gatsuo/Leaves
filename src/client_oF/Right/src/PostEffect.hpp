#pragma once
#include "ofMain.h"

class PostEffect {
public:
    void setup();
    void begin();
    void end();
    void draw();
    
    ofFbo* getFbo();
    
    void enableNega();
    void disableNega();
    bool isNega();
    
private:
    ofFbo base;
    ofFbo composite;
    
    bool bNega = false;
    ofShader negaConv;
    
};
