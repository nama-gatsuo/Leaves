#pragma once
#include "ofMain.h"
#include "ofxJSON.h"
#include "DataTail.hpp"

class DataPoints{
public:
    DataPoints();
    void setup(float rad);
    void update();
    void draw();
    void add(float lat, float lon, bool isMale, bool isDefault=false);
    
private:
    ofVboMesh mesh;
    ofShader shader;
    float radius;
    DataTail tail;
    
};
