#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    me.setup(420.);
    dp.setup(420.);
    
    cam.orbit();
    
    pe.setup();
    
    sphere = ofMesh::sphere(410., 40);
    for (int i = 0; i < sphere.getNumVertices(); i++) {
        sphere.addColor(ofFloatColor(0.1));
    }
    
    receiver.setup(PORT);

    warper.setSourceRect(ofRectangle(0, 0, 1280, 640));
    warper.setTopLeftCornerPosition(ofPoint(0, 20));
    warper.setTopRightCornerPosition(ofPoint(1280, 20));
    warper.setBottomLeftCornerPosition(ofPoint(0, 660));
    warper.setBottomRightCornerPosition(ofPoint(1280, 660));
    warper.setup();
    warper.load();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    me.update();
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
    
    cam.end();
    pe.end();
    
    ofMatrix4x4 mat = warper.getMatrix();
    
    ofPushMatrix();
    ofMultMatrix(mat);
    pe.draw();
    ofPopMatrix();
    
    ofSetColor(ofColor::magenta);
    warper.drawQuadOutline();
    ofSetColor(ofColor::yellow);
    warper.drawCorners();
    ofSetColor(ofColor::magenta);
    warper.drawHighlightedCorner();
    ofSetColor(ofColor::red);
    warper.drawSelectedCorner();
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
    else if (key == 'h') warper.toggleShow();
    else if (key == 'l') warper.load();
    else if (key == 's') warper.save();
    
}

