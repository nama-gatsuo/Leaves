#pragma once
#include "ofMain.h"

struct CountryData{
    string id;
    vector<ofPath> pathes;
};

class EarthLayer{
public:
    EarthLayer();
    void setup();
    void setLayer();
    void draw();
     ofFbo fbo;
private:
    vector<ofPath> createPath(ofXml &svg, ofVec2f& start);
    ofPath stringToPath(string &s, ofVec2f& start);
    ofVec2f stringToVec2(string &s);
    ofVec2f getLastPoint(ofPath &path);
    
    int w, h;
    ofVboMesh mesh;
    ofShader shader;
    
   
    
    vector<CountryData> countries;
    
};
