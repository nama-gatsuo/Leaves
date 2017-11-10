#include "RightChannel.hpp"

void RightApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    ofSetWindowTitle("Right");
    
    cam.setNearClip(0.01);
    cam.setFov(90);
    
    pe.setup(CANVAS_WIDTH, CANVAS_HEIGHT);
}
void RightApp::update(){
    
    if (main->pe.isNega()) pe.enableNega();
    else pe.disableNega();
    
    if (main->countFromBang < 800) {
        isFocus = false;
    } else {
        if (!isFocus) {
            la = main->latest.pos;
            up = la.getNormalized();
            
            ofVec3f axis = la.getNormalized();
            mat.makeRotationMatrix(ofVec3f(0,1,0), axis);
            
        }
        isFocus = true;
        
        float t = main->countFromBang * 0.003;
        cam.setPosition(ofVec3f(10. * sin(t), 0, 10. * cos(t)) * mat + la);
        cam.lookAt(la, up);
    }
    
}
void RightApp::draw(){
    
    pe.begin();
    
    if (isFocus) {
        cam.begin();
        
        main->me.draw(cam);
        main->dp.draw();
        main->dc.draw();
        
        cam.end();
        
    } else {
        main->cam.begin(CustomCam::RIGHT);
        
        main->me.draw(main->cam);
        main->dp.draw();
        main->dc.draw();
        
        main->cam.end();
    }
    pe.end();
    
    pe.draw(CANVAS_OFFSET, 0);
}
