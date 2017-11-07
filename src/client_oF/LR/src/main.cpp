#include "ofMain.h"
#include "ofApp.h"
#include "RightChannel.hpp"
#include "LeftChannel.hpp"
#include "ofAppGLFWWindow.h"

int main( ){
    ofGLFWWindowSettings settings;
    
    settings.width = 200;
    settings.height = 200;
    settings.setGLVersion(3, 2);
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> main = ofCreateWindow(settings);
    
    
    settings.width = 1024;
    settings.height = 768;
    settings.shareContextWith = main;
    settings.resizable = true;
    settings.setPosition(ofVec2f(200,0));
    shared_ptr<ofAppBaseWindow> right = ofCreateWindow(settings);
    settings.setPosition(ofVec2f(300,0));
    shared_ptr<ofAppBaseWindow> left = ofCreateWindow(settings);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<RightApp> rightApp(new RightApp);
    shared_ptr<LeftApp> leftApp(new LeftApp);
    
    rightApp->main = mainApp;
    leftApp->main = mainApp;
    
    ofRunApp(main, mainApp);
    ofRunApp(right, rightApp);
    ofRunApp(left, leftApp);
    
    ofRunMainLoop();
}
