#include "ofMain.h"

class DataCloud {
public:
    void setup(){
        ofSeedRandom(0);
        shader.load("shader/sprite");
        
        vbo.setMode(OF_PRIMITIVE_POINTS);
        for (int i = 0; i < totalNum; i++) {
            ofVec3f v = ofVec3f(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1)).normalize();
            v *= ofRandom(800, 1500);
            
            vbo.addVertex(v);
            vbo.addColor(ofFloatColor(0.5, 1.0));
        }
    };
    
    void draw(){
        
        shader.begin();
        vbo.draw();
        shader.end();
        
    };
private:
    int totalNum = 10000;
    ofShader shader;
    ofVboMesh vbo;
};

