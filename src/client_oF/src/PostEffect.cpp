#include "PostEffect.hpp"

void PostEffect::setup(int w, int h){

    ofFbo::Settings s;
    s.width = w;
    s.height = h;
    s.internalformat = GL_RGB32F;
    s.useDepth = true;
    s.depthStencilAsTexture = true;

    base.allocate(s);

    composite.allocate(s.width, s.height, GL_RGB32F);

    negaConv.load("shader/pfx/passThru.vert", "shader/pfx/NegativeConv.frag");

}

void PostEffect::begin(){

    base.begin();
    ofClear(0);

}
void PostEffect::end(){

    base.end();

    composite.begin();
    ofClear(0);

    if (bNega) negaConv.begin();
    base.draw(0,0);
    if (bNega) negaConv.end();

    composite.end();

}

void PostEffect::draw(int x, int y){
    ofSetColor(255);
    composite.draw(x, y);
}

ofFbo* PostEffect::getFbo() { return &composite; }

void PostEffect::enableNega() { bNega = true; }
void PostEffect::disableNega() { bNega = false; }

bool PostEffect::isNega() { return bNega; }
