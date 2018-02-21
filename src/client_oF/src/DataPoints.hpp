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
    ofVec3f add(float lat, float lon, bool isMale, bool isDefault = false);
    void remark();

private:
    ofVboMesh mesh;
    ofShader shader;
    float radius;
    DataTail tail;

};
