#include "RightChannel.hpp"

void RightApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    ofSetWindowTitle("Right");
}
void RightApp::update(){}
void RightApp::draw(){
    
    main->cam.begin(CustomCam::RIGHT);
    
    main->me.draw(main->cam);
    main->dp.draw();
    main->dc.draw();
    
    main->cam.end();
    
}
