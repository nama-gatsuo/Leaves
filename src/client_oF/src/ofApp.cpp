#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofBackground(0);
    
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    de.setup(400.);
    dp.setup(400.);
    
    cam.orbit();
    
    receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    cam.update();
    
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        float lat = m.getArgAsFloat(5);
        float lon = m.getArgAsFloat(6);
        string sex = m.getArgAsString(3);
        
        if (DEBUG) {
            cout << "Country: " + m.getArgAsString(0) << endl;
            cout << "City: " + m.getArgAsString(1) << endl;
            cout << "Age: " + m.getArgAsString(2) << endl;
            cout << "Sex: " + sex << endl;
            cout << "Reason: " + m.getArgAsString(4) << endl;
            cout << "lat: " + ofToString(lat) << endl;
            cout << "lon: " + ofToString(lon) << endl;
        }
        
        lat = lat / 180. * PI;
        lon = lon / 180. * PI;
        
        dp.add(lat, lon, sex == "Males");
        cam.look(lat, lon);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    de.draw();
    dp.draw();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

