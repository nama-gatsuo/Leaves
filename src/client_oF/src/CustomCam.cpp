#include "CustomCam.hpp"

CustomCam::CustomCam(){}

void CustomCam::update(){
    
    count++;
    float h;
    
    if (mode == LOOKING) {
        h = 1.1;
        if (count > 600) {
            transition();
        }
    } else if (mode == ORBITAL) {
        h = 1.0;
    } else if (mode == L_TO_O) {
        h = 1.0;
        if (count > 200) {
            orbit();
        }
    }
    
    float t = count / (float)MAX_COUNT;
    
    tpos = center * h + rad * cos(t) * axisX + rad * sin(t) * axisZ;
    
    la = (tla - la) * 0.01 + la;
    pos = (tpos - pos) * 0.01 + pos;
    
    lookAt(la);
    setPosition(pos);
    
}

void CustomCam::look(float lat, float lon){
    
    count = 0;
    rad = 40. + ofRandom(40.);
    
    float radius = 400.;
    lat = - PI/2. + lat;
    lon += PI/2.;
    center.x = radius * sin(lon) * sin(lat);
    center.z = radius * cos(lon) * sin(lat);
    center.y = radius * cos(lat);
    
    tla = center;
    ofVec3f axis = center.getNormalized();
    
    axisX = axis.getCrossed(ofVec3f(0,1,0)).normalize();
    axisZ = axisX.getCrossed(axis).normalize();
    
    mode = LOOKING;
}

void CustomCam::orbit(){
    
    count = ofRandom(300);
    rad = 800. + ofRandom(200.);
    
    ofVec3f axis = ofVec3f(ofRandom(-1,1)*0.5, 1., ofRandom(-1,1)*0.5);
    axis.normalize();
    
    axisX = axis.getCrossed(ofVec3f(0,1,0)).normalize();
    axisZ = axisX.getCrossed(axis).normalize();
    
    tla = ofVec3f(0.);
    center = ofVec3f(0.);
    
    mode = ORBITAL;
}

void CustomCam::transition(){
    count = 0;
    center *= 2.0;
    
    mode = L_TO_O;
}
