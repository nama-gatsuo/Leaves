#include "PostEffect.hpp"

void PostEffect::setup(){
    
    ofFbo::Settings s;
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGB32F;
    
    base.allocate(s);
    
    composite.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F);
    
    
    negaConv.load("shader/pfx/passThru.vert", "shader/pfx/NegativeConv.frag");
}

void PostEffect::begin(){
    
    base.begin();
    ofClear(0,0);
    
}
void PostEffect::end(){
    
    base.end();
    
    composite.begin();
    ofClear(0,0);
    ofSetColor(255);
    
    if (bNega) negaConv.begin();
    base.draw(0,0);
    if (bNega) negaConv.end();
    
    composite.end();
    
}

void PostEffect::draw(){
    ofSetColor(255);
    composite.draw(0,0);
}

ofFbo* PostEffect::getFbo() { return &composite; }

void PostEffect::enableNega() { bNega = true; }
void PostEffect::disableNega() { bNega = false; }

bool PostEffect::isNega() { return bNega; }
