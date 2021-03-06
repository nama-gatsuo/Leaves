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
    
    vector<DataMark>::iterator it;
    for (it = marks.begin(); it < marks.end(); it++) {
        if (it->isDead) {
            marks.erase(it);
        } else {
            it->update();
        }
    }
    
}

void DataPoints::draw(){

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofDisableDepthTest();

    shader.begin();
    mesh.draw();
    shader.end();

    tail.draw();
    vector<DataMark>::iterator it;
    for (it = marks.begin(); it < marks.end(); it++) {
        it->draw();
    }
    
    ofDisableBlendMode();
}

ofVec3f DataPoints::add(float lat, float lon, bool isMale, bool isDefault){

    ofVec3f to;
    ofVec3f from;

    lat = - PI/2. + lat;

    to.x = radius * sin(lon) * sin(lat);
    to.z = radius * cos(lon) * sin(lat);
    to.y = radius * cos(lat);

    float r = ofRandom(0., 5.);
    float t = ofRandom(0., TWO_PI);
    ofVec3f offset = ofVec3f(r * cos(t), r * ofRandom(-0.5,0.5), r * sin(t));
    ofMatrix4x4 mat;
    mat.makeRotationMatrix(ofVec3f(0,1,0), to.getNormalized());

    to += offset * mat;

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

void DataPoints::remark(ofVec3f& p){
    
    marks.push_back(DataMark(p));
    if (marks.size() > 10) {
        marks.erase(marks.begin());
    }
    
}
