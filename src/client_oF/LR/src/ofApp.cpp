#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofSetVerticalSync(true);
    
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    me.setup(420.);
    dp.setup(420.);
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
            
            pe.enableNega();
            fcnt = 0.0;
        
        } else if (addr == "/layer") {
            
            int id = m.getArgAsInt(0);
            
            if (DEBUG) {
                cout << "layer: " + ofToString(id) << endl;
            }
            
            me.setLayer(id);
            
        }
        
    }
    
    if (pe.isNega()) {
        fcnt += 0.03;
        if (fcnt > 1.0) pe.disableNega();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    pe.begin();
    cam.begin();
    
    me.draw();
    dp.draw();
    dc.draw();
    
    cam.end();
    pe.end();
    
    //pe.draw();

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

