#include "DataPoints.hpp"

DataPoints::DataPoints(){}

void DataPoints::setup(){
    
    ofxJSONElement json;
    
    if (json.open("data.json")) {
        int n = json.size();
        
        float lat, lon;
        string sex;
        float r = 400.;
        for (int i = 0; i < n; i++) {
            
            lat = json[i]["latitude"].asFloat() / 180. * PI;
            lon = json[i]["longitude"].asFloat() / 180. * PI;
            
            sex = json[i]["sex"].asString();
            
            ofVec3f v;
            lat = - PI/2. + lat;
            lon += PI/2.;
            v.x = r * sin(lon) * sin(lat);
            v.z = r * cos(lon) * sin(lat);
            v.y = r * cos(lat);
            
            ofVec3f n = v.getNormalized();
            ofVec3f r = ofVec3f(ofRandom(-1.,1.), ofRandom(-1.,1.), ofRandom(-1.,1.)).normalize();
            v += n * 6. + r * 6.;
            
            ofFloatColor c;
            if (sex == "Males") {
                c.setHsb(0.5, 0.9, 0.9);
            } else {
                c.setHsb(0.0, 0.9, 0.9);
            }
            
            mesh.addVertex(v);
            mesh.addColor(c);
        }
        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    
    shader.load("shader/sprite");

}

void DataPoints::draw(){
    shader.begin();
    mesh.draw();
    shader.end();
}
