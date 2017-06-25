#include "CustomCam.hpp"

CustomCam::CustomCam(){}

void CustomCam::update(){
    
    count++;
    
    if (mode == LOOKING) {
        
        if (count > MAX_COUNT) {
            orbit();
        }
    } else if (mode == ORBITAL) {
        
    }
    
    float t = count / (float)MAX_COUNT;
    
    tpos = center + rad * cos(t) * axisX + rad * sin(t) * axisZ;
    
    la = (tla - la) * 0.04 + la;
    pos = (tpos - pos) * 0.04 + pos;
    
    lookAt(la);
    setPosition(pos);
    
}

void CustomCam::look(float lat, float lon){
    
    count = 0;
    rad = 80.;
    
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
    
    float t = count / (float)MAX_COUNT;
    tpos = center + rad * cos(t) * axisX + rad * sin(t) * axisZ;
    
    mode = LOOKING;
}

void CustomCam::orbit(){
    
    count = 0;
    rad = 700. + ofRandom(300.);
    
    tla = ofVec3f(0.);
    center = ofVec3f(0.);
    
    ofVec3f axis = ofVec3f(ofRandom(-1,1)*0.5, 1., ofRandom(-1,1)*0.5);
    axis.normalize();
    
    axisX = axis.getCrossed(ofVec3f(0,1,0)).normalize();
    axisZ = axisX.getCrossed(axis).normalize();
    
    float t = count / (float)MAX_COUNT;
    tpos = center + rad * cos(t) * axisX + rad * sin(t) * axisZ;
    
    mode = ORBITAL;
}
