#include "DataPoints.hpp"

DataPoints::DataPoints(){}

void DataPoints::setup(float rad){
    
    radius = rad;
    
    ofxJSONElement json;
    
    if (json.open("data.json")) {
        
        ofSeedRandom(0);
        
        int n = json.size();
        
        float lat, lon;
        string sex;
        
        for (int i = 0; i < n; i++) {
            
            lat = json[i]["latitude"].asFloat() / 180. * PI;
            lon = json[i]["longitude"].asFloat() / 180. * PI;
            
            sex = json[i]["sex"].asString();
            
            add(lat, lon, sex == "Males", true);
        }
        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    
    shader.load("shader/sprite");

}

void DataPoints::update(){
    tail.update();
    if (!tail.isEnd()) {
        mesh.setVertex(mesh.getNumVertices()-1, tail.getHead());
    }
}

void DataPoints::draw(){
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofDisableDepthTest();
    
    shader.begin();
    mesh.draw();
    shader.end();
    
    tail.draw();
    
    ofDisableBlendMode();
}

ofVec3f DataPoints::add(float lat, float lon, bool isMale, bool isDefault){
    
    ofVec3f to;
    ofVec3f from;
    
    lat = - PI/2. + lat;
    
    to.x = radius * sin(lon) * sin(lat);
    to.z = radius * cos(lon) * sin(lat);
    to.y = radius * cos(lat);
    
    ofVec3f r = ofVec3f(ofRandom(-1.,1.), ofRandom(-0.5,0.5), ofRandom(-1.,1.));
    ofMatrix4x4 mat;
    mat.makeRotationMatrix(ofVec3f(0,1,0), to.getNormalized());
    
    to += r * mat * 5.;
    
    ofFloatColor c;
    if (isMale) {
        c.setHsb(0.5, 0.9, 0.9);
    } else {
        c.setHsb(0.0, 0.9, 0.9);
    }
    
    if (!isDefault) {
        tail.clear();
        tail.setup(to, c);
        from = tail.getHead();
    } else {
        from = to;
    }
    
    mesh.addVertex(from);
    mesh.addColor(c);
    
    return to;
}
