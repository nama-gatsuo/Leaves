#pragma once
#include "ofMain.h"

class CustomCam : public ofCamera {
public:
    CustomCam();
    void update();
    void look(float lat, float lon);
    void orbit();
    void transition();
private:
    ofVec3f la, pos, up;
    ofVec3f tla, tpos, tup;
    float speed = 0.01;
    
    enum CamMode {
        LOOKING, ORBITAL, L_TO_O
    } mode;
    
    const int MAX_COUNT = 600;
    int count = 0;
    
    ofVec3f axisX, axisZ;
    ofVec3f center;
    float rad = 80.;
};
