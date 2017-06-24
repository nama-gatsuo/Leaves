#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofBackground(0);
    
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    de.setup();
    dp.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
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

