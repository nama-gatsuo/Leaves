#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofSetVerticalSync(true);
    
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    me.setup(420.);
    dp.setup(426.);
    dc.setup();
    cam.setup(420.);
    
    cam.orbit();
    
    pe.setup();
    
    receiver.setup(PORT);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    me.update();
    dp.update();
    cam.update();
    
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        string addr = m.getAddress();
        
        if (addr == "/new") {
        
            float lat = m.getArgAsFloat(5);
            float lon = m.getArgAsFloat(6);
            string sex = m.getArgAsString(3);
            
            latest.coord = ofVec2f(lon, lat);
            latest.country = m.getArgAsString(0);
            latest.city = m.getArgAsString(1);
            latest.age = m.getArgAsString(2);
            latest.isMale = sex == "Males";
            latest.reason = m.getArgAsString(4);
            
            lat = lat / 180. * PI;
            lon = lon / 180. * PI;
            
            ofVec3f pos = dp.add(lat, lon, sex == "Males");
            cam.look(pos);
            
            pe.enableNega();
            fcnt = 0;
        
        } else if (addr == "/layer") {
            
            int id = m.getArgAsInt(0);
            me.setLayer(id);
            
        }
        
    }
    
    if (pe.isNega()) {
        fcnt ++;
        if (fcnt > 30) pe.disableNega();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    pe.begin();
    cam.ofCamera::begin();
    
    me.draw(cam);
    dp.draw();
    dc.draw();
    
    cam.end();
//    pe.end();
    
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 10, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') cam.look(ofRandom(PI), ofRandom(TWO_PI));
    else if (key == '0') me.setLayer(0);
    else if (key == '1') me.setLayer(1);
    else if (key == '2') me.setLayer(2);
    else if (key == '3') me.setLayer(3);
    else if (key == '4') me.setLayer(4);
    else if (key == '5') me.setLayer(5);
    else if (key == '6') me.setLayer(6);
    else if (key == '7') me.setLayer(7);
    
}

