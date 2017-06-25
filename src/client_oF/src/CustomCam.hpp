#pragma once
#include "ofMain.h"

class CustomCam : public ofCamera {
public:
    CustomCam();
    void update();
    void look(float lat, float lon);
    void orbit();
private:
    ofVec3f la, pos, up;
    ofVec3f tla, tpos, tup;
    
    enum CamMode {
        LOOKING, ORBITAL
    } mode;
    
    const int MAX_COUNT = 600;
    int count = 0;
    
    ofVec3f axisX, axisZ;
    ofVec3f center;
    float rad = 80.;
};
