#pragma once
#include "ofMain.h"
#include "ofxJSON.h"

class DataPoints{
public:
    DataPoints();
    void setup();
    void draw();
private:
    ofVboMesh mesh;
    ofShader shader;
    
};
