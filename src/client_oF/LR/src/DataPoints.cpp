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

void DataPoints::add(float lat, float lon, bool isMale, bool isDefault){
    
    ofVec3f v;
    lat = - PI/2. + lat;
    
    v.x = radius * sin(lon) * sin(lat);
    v.z = radius * cos(lon) * sin(lat);
    v.y = radius * cos(lat);
    
    ofVec3f r = ofVec3f(ofRandom(-1.,1.), ofRandom(-1.,1.), ofRandom(-1.,1.)).normalize();
    v += r * 6.;
    
    ofFloatColor c;
    if (isMale) {
        c.setHsb(0.5, 0.9, 0.9);
    } else {
        c.setHsb(0.0, 0.9, 0.9);
    }
    if (!isDefault) {
        tail.clear();
        tail.setup(v, c);
        v = tail.getHead();
    }
    mesh.addVertex(v);
    mesh.addColor(c);
    
}
