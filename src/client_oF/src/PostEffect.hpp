#pragma once
#include "ofMain.h"

class PostEffect {
public:
    void setup(int w, int h);
    void begin();
    void end();
    void draw(int x, int y);
    
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
