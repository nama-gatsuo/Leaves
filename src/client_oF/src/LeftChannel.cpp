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
    
    ofVec2f st = main->latest.coord / 180. * (CANVAS_WIDTH / 2);
    st.x = CANVAS_WIDTH / 2 + st.x;
    st.y = CANVAS_WIDTH / 4 - st.y;
    ofDrawLine(0, st.y, CANVAS_WIDTH, st.y);
    ofDrawLine(st.x, 0, st.x, CANVAS_WIDTH / 2);
    
    int lineHeight = 20;
    int startHeight = CANVAS_WIDTH / 2 + 40;
    int startWidth = 50;
    
    ofSetColor(156);
    ofDrawBitmapString("layer: " + main->me.map.getLayerName(), CANVAS_WIDTH - 260, CANVAS_WIDTH / 2 - 20);
    
    ofDrawBitmapString("age: ", startWidth, startHeight);
    ofDrawBitmapString("gender: ", startWidth, startHeight += lineHeight);
    ofDrawBitmapString("place: ", startWidth, startHeight += lineHeight);
    ofDrawBitmapString("reason: ", startWidth, startHeight += lineHeight);
    
    startHeight = CANVAS_WIDTH / 2 + 40;
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
