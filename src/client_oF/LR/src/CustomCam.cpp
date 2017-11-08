#include "CustomCam.hpp"

CustomCam::CustomCam(){
}

void CustomCam::setup(float sphereRad){
    ofCamera::setFov(72);
    ofCamera::setNearClip(0.01);
    sphereRadius = sphereRad;
}

void CustomCam::update(){
    
    count++;
    
    if (mode == LOOKING) {
        if (count > 720) {
            transition();
        }
    } else if (mode == ORBITAL) {
        
    } else if (mode == L_TO_O) {
        
        if (count > 360) {
            orbit();
        }
    }
    
    float t = count / (float)MAX_COUNT;
    
    tpos = center + rad * cos(t) * axisX + rad * sin(t) * axisZ;
    
    la = (tla - la) * speed + la;
    pos = (tpos - pos) * speed + pos;
    
    ofVec3f ray = (la - pos).getNormalized();
    ofVec3f side = ray.getCrossed(ofVec3f(0,1,0));
    up = side.getCrossed(ray);
    
    lookAt(la, up);
    setPosition(pos);
    
}

void CustomCam::look(float lat, float lon){
    
    ofSeedRandom(lat + lon);
    
    count = 0;
    rad = 5.;
    speed = 0.006;
    
    lat = - PI/2. + lat;
    
    center.x = sphereRadius * sin(lon) * sin(lat);
    center.z = sphereRadius * cos(lon) * sin(lat);
    center.y = sphereRadius * cos(lat);
    
    tla = center;
    ofVec3f axis = center.getNormalized();
    
    axisX = axis.getCrossed(ofVec3f(0,1,0)).normalize();
    axisZ = axisX.getCrossed(axis).normalize();
    
    mode = LOOKING;
}

void CustomCam::look(ofVec3f& pos) {
    
    count = 0;
    rad = 5.;
    speed = 0.01;
    
    center = pos;
    tla = pos;
    ofVec3f axis = pos.getNormalized();
    
    axisX = axis.getCrossed(ofVec3f(0,1,0)).normalize();
    axisZ = axisX.getCrossed(axis).normalize();
    
    mode = LOOKING;
    
}

void CustomCam::orbit(){
    
    count = ofRandom(300);
    rad = 1000.;
    speed = 0.002;
    
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
    
    speed = 0.002;
    
    mode = L_TO_O;
}

void CustomCam::begin(CustomCam::SideCamMode side) {
    
    ofVec3f to;
    ofVec3f l = getLookAtDir();
    ofVec3f up = getUpDir();
    ofVec3f p = getGlobalPosition();
    float len = (la - p).length();
    
    if (side == CustomCam::RIGHT) {
        to = l.getCrossed(up).getNormalized();
    } else if (side == CustomCam::LEFT) {
        to = - l.getCrossed(up).getNormalized();
    }
    
    lookAt(to * len + p, up);
    ofCamera::begin();
    
}
