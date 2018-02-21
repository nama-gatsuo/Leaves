#pragma once
#include "ofMain.h"
#include "ofxJSON.h"
#include "DataTail.hpp"
#include "DataMark.hpp"

class DataPoints{
public:
    DataPoints();
    void setup(float rad);
    void update();
    void draw();
    ofVec3f add(float lat, float lon, bool isMale, bool isDefault = false);
    void remark(ofVec3f& p);

private:
    ofVboMesh mesh;
    ofShader shader;
    float radius;
    DataTail tail;
    vector<DataMark> marks;
};
