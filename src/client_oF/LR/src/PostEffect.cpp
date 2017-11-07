#include "PostEffect.hpp"

void PostEffect::setup(){
    
    ofFbo::Settings s;
    s.width = 1024;
    s.height = 768;
    s.internalformat = GL_RGB32F;
    s.useDepth = true;
    s.depthStencilAsTexture = true;
    
    base.allocate(s);
    
    composite.allocate(s.width, s.height, GL_RGB32F);
    
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
    
    negaConv.begin();
    negaConv.setUniform1f("isNega", bNega?1.:0.);
    base.draw(0,0);
    negaConv.end();
    
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
