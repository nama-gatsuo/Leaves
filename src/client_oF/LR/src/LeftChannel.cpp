#include "LeftChannel.hpp"

void LeftApp::setup(){
    ofBackground(0);
    ofSetWindowTitle("Left");
}
void LeftApp::update(){}
void LeftApp::draw(){
    
    main->me.map.getTexture(0).draw(0,0, 1024, 512);
    
    ofVec2f st = main->latest.coord / 180. * 512.;
    st.x = 512 + st.x;
    st.y = 256 - st.y;
    ofDrawLine(0, st.y, 1024, st.y);
    ofDrawLine(st.x, 0, st.x, 512);
    
    int lineHeight = 20;
    int startHeight = 560;
    int startWidth = 50;
    
    ofSetColor(156);
    ofDrawBitmapString("layer: " + main->me.map.getLayerName(), 1024 - 260, 512 - 20);
    
    ofDrawBitmapString("age: ", startWidth, startHeight);
    ofDrawBitmapString("gender: ", startWidth, startHeight += lineHeight);
    ofDrawBitmapString("place: ", startWidth, startHeight += lineHeight);
    ofDrawBitmapString("reason: ", startWidth, startHeight += lineHeight);
    
    startHeight = 560;
    startWidth = 180;
    
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
    
    
}
