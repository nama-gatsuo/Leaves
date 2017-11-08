#pragma once
#include "ofMain.h"

class CustomCam : public ofCamera {
public:
    enum SideCamMode { CENTER, LEFT, RIGHT } side;
    
    CustomCam();
    void setup(float sphereRad);
    void update();
    void look(float lat, float lon);
    void look(ofVec3f& pos);
    void orbit();
    void transition();
    void begin(SideCamMode side);
    
private:
    ofVec3f la, pos, up, ray;
    ofVec3f tla, tpos;
    float speed = 0.01;
    
    enum CamMode {
        LOOKING, ORBITAL, L_TO_O
    } mode;
    
    const int MAX_COUNT = 600;
    int count = 0;
    
    ofVec3f axisX, axisY, axisZ;
    ofVec3f center;
    float rad = 80.;
    float sphereRadius;
};
