#include "ofMain.h"

class DataCloud {
public:
    void setup(){
        ofSeedRandom(0);
        shader.load("shader/sprite");
        
        vbo.setMode(OF_PRIMITIVE_POINTS);
        for (int i = 0; i < totalNum; i++) {
            ofVec3f v = ofVec3f(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1)).normalize();
            v *= ofRandom(700, 1200);
            
            vbo.addVertex(v);
            vbo.addColor(ofFloatColor(0.5, 1.0));
        }
    };
    
    void draw(){
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        
        shader.begin();
        vbo.draw();
        shader.end();
        
        ofDisableBlendMode();
    };
private:
    int totalNum = 4000;
    ofShader shader;
    ofVboMesh vbo;
};

