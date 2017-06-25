#pragma once
#include "ofMain.h"
#include "ofxJSON.h"

class DataPoints{
public:
    DataPoints();
    void setup(float rad);
    void draw();
    void add(float lat, float lon, bool isMale);
private:
    ofVboMesh mesh;
    ofShader shader;
    float radius;
    
    ofVec3f last;
};
