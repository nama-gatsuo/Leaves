#include "LeftChannel.hpp"

void LeftApp::setup(){
    ofBackground(0);

    ofSetVerticalSync(true);

    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    ofSetWindowTitle("Left");
    pe.setup(CANVAS_WIDTH, CANVAS_HEIGHT);
}
void LeftApp::update(){

    if (main->pe.isNega()) pe.enableNega();
    else pe.disableNega();

    if (main->countFromBang < 800) {
        isMap = false;
    } else {
        isMap = true;
    }

}
void LeftApp::draw(){

    pe.begin();

    if (isMap) {
        drawMap();
    } else {
        main->cam.begin(CustomCam::LEFT);

        main->me.draw(main->cam);
        main->dp.draw();
        main->dc.draw();

        main->cam.end();
    }

    pe.end();

    pe.draw(CANVAS_OFFSET, 0);

}

void LeftApp::drawMap(){
    main->me.map.getTexture(0).draw(0,0, CANVAS_WIDTH, CANVAS_WIDTH / 2);

    float alpha = (1. + sin(ofGetElapsedTimef())) * 127.;

    ofVec2f st = main->latest.coord / 180. * (CANVAS_WIDTH / 2);
    st.x = CANVAS_WIDTH / 2 + st.x;
    st.y = CANVAS_WIDTH / 4 - st.y;

    ofSetColor(255, alpha);
    ofDrawLine(0, st.y, CANVAS_WIDTH, st.y);
    ofDrawLine(st.x, 0, st.x, CANVAS_WIDTH / 2);

    if (main->latest.isMale) ofSetColor(0, 128, 255, alpha);
    else ofSetColor(255, 48, 98, alpha);

    ofDrawCircle(st.x, st.y, 6.);

    int lineHeight = 20;
    int startHeight = CANVAS_WIDTH / 2 + 40;
    int startWidth = 50;

    ofSetColor(200);
    ofDrawBitmapString("layer: " + main->me.map.getLayerName(), CANVAS_WIDTH - 260, CANVAS_WIDTH / 2 - 10);

    ofDrawBitmapString("age: ", startWidth, startHeight);
    ofDrawBitmapString("gender: ", startWidth, startHeight += lineHeight);
    ofDrawBitmapString("place: ", startWidth, startHeight += lineHeight);
    ofDrawBitmapString("reason: ", startWidth, startHeight += lineHeight);

    startHeight = CANVAS_WIDTH / 2 + 40;
    startWidth = 130;

    ofSetColor(255);
    ofDrawBitmapString(main->latest.age, startWidth, startHeight);
    ofDrawBitmapString(main->latest.isMale ? "Male" : "Female", startWidth, startHeight += lineHeight);
    ofDrawBitmapString(main->latest.country + " > " + main->latest.city, startWidth, startHeight += lineHeight);
    vector<string> sarray = ofSplitString(main->latest.reason, " > ");
    for (int i = 0; i < sarray.size(); i++) {
        if (sarray[i] == "") continue;
        string s;
        for (int j = 0; j < i; j++) {
            s += ">";
            if (j == i - 1) s += " ";
        }
        s += sarray[i];
        ofDrawBitmapString(s, startWidth, startHeight += lineHeight);
    }
    int y = ofGetYear();
    int m = ofGetMonth();
    int d = ofGetDay();

    int h = ofGetHours();
    string strHour = h < 10 ? "0" + ofToString(h) : ofToString(h);
    int min = ofGetMinutes();
    string strMin = min < 10 ? "0" + ofToString(min) : ofToString(min);
    int s = ofGetSeconds();
    string strSec = s < 10 ? "0" + ofToString(s) : ofToString(s);

    string data = ofToString(y) + "/" + ofToString(m) + "/" + ofToString(d);
    string time = strHour + ":" + strMin + ":" + strSec + " JST";

    ofDrawBitmapString(data, ofGetWidth()/2, startHeight += lineHeight);
    ofDrawBitmapString(time, ofGetWidth()/2, startHeight += lineHeight);
}
