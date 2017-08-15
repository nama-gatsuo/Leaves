#include "DataPoints.hpp"

DataPoints::DataPoints(){}

void DataPoints::setup(float rad){
    
    radius = rad;
    
    ofxJSONElement json;
    
    if (json.open("data.json")) {
        int n = json.size();
        
        float lat, lon;
        string sex;
        
        for (int i = 0; i < n; i++) {
            
            lat = json[i]["latitude"].asFloat() / 180. * PI;
            lon = json[i]["longitude"].asFloat() / 180. * PI;
            
            sex = json[i]["sex"].asString();
            
            add(lat, lon, sex == "Males");
        }
        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    
    numParticles = mesh.getNumVertices();
    
    shader.load("shader/sprite");

}

void DataPoints::draw(){
    
    t += 0.0012;
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofDisableDepthTest();
    
    shader.begin();
    shader.setUniform1i("last", numParticles-1);
    shader.setUniform1f("t", t);
    mesh.draw();
    shader.end();
    
    ofDisableBlendMode();
}

void DataPoints::add(float lat, float lon, bool isMale){
    
    ofVec3f v;
    lat = - PI/2. + lat;
    //lon += PI/2.;
    v.x = radius * sin(lon) * sin(lat);
    v.z = radius * cos(lon) * sin(lat);
    v.y = radius * cos(lat);
    
    ofVec3f n = v.getNormalized();
    ofVec3f r = ofVec3f(ofRandom(-1.,1.), ofRandom(-1.,1.), ofRandom(-1.,1.)).normalize();
    v += n * 6. + r * 6.;
    
    ofFloatColor c;
    if (isMale) {
        c.setHsb(0.5, 0.9, 0.9);
    } else {
        c.setHsb(0.0, 0.9, 0.9);
    }
    
    mesh.addVertex(v);
    mesh.addColor(c);
    
    numParticles++;
    t = 0.0;
}
