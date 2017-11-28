#include "ofMain.h"
#include "ofApp.h"
#include "RightChannel.hpp"
#include "LeftChannel.hpp"
#include "ofAppGLFWWindow.h"

int main( ){
    ofGLFWWindowSettings settings;

    settings.width = WINDOW_WIDTH;
    settings.height = WINDOW_HEIGHT;
    settings.setGLVersion(3, 2);
    settings.setPosition(ofVec2f(200,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> main = ofCreateWindow(settings);

    settings.width = WINDOW_WIDTH;
    settings.height = WINDOW_HEIGHT;
    settings.shareContextWith = main;
    settings.setPosition(ofVec2f(400,0));
    shared_ptr<ofAppBaseWindow> right = ofCreateWindow(settings);
    settings.setPosition(ofVec2f(0,0));
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
