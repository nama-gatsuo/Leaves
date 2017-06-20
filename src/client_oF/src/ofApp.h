#pragma once

#include "ofMain.h"
#include "EmitterSphere.hpp"
#include "CommonUtil.hpp"

#include "ofxDeferredShading.h"
#include "ofxGui.h"
#include "ofxOsc.h"

using namespace ofxDeferredShading;

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void windowResized(int w, int h);
	
private:
    
    const int PORT = 8032;
    ofxOscReceiver receiver;
    
    void setupDeferred();
    void updateDeferredParam();
    
    EmitterSphere es;
    
    ofEasyCam cam;
    SmoothValue theta;
    SmoothValue rho;
    SmoothValue radius;
    SmoothPoint lookAt;
    
    ofxDeferredProcessing deferred;
    PointLightPass* lightingPass;
    SsaoPass* ssaoPass;
    ShadowLightPass* shadowLightPass;
    DofPass* dofPass;
    
    // gui
    bool isShow = false;
    ofxPanel panel;
    
    ofParameterGroup ao;
    ofParameter<float> ao_rad;
    ofParameter<float> ao_dark;
    
    ofParameterGroup shadow;
    ofParameter<float> sha_amb;
    ofParameter<float> sha_dif;
    ofParameter<float> sha_dark;
    ofParameter<float> sha_blend;
    
    ofParameterGroup dof;
    ofParameter<float> dof_blur;
    ofParameter<float> dof_ape;
    ofParameter<float> dof_focal;
};
