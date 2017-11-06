#include "ofMain.h"
#include "CommonUtil.hpp"

class MeshEarth {
public:
    void setup(float radius){
        
        ofImage color;
        color.load("img/color.jpg");
        
        sea.load("img/sea.jpg");
        
        texs.assign(8, ofImage());
        texs[0].load("img/layer/topography.jpg");
        texs[1].load("img/layer/population-density.jpg");
        texs[2].load("img/layer/gdp-per-capita.jpg");
        texs[3].load("img/layer/population-growth.jpg");
        texs[4].load("img/layer/unmarried-rate.jpg");
        texs[5].load("img/layer/suicide-rate.jpg");
        texs[6].load("img/layer/aids.jpg");
        texs[7].load("img/layer/cancer.jpg");
        
        shader.load("shader/meshEarth");
        shader.begin();
        for (int i = 0; i < 8; i++) {
            shader.setUniformTexture("tex" + ofToString(i), texs[i].getTexture(), i + 1);
        }
        shader.setUniformTexture("sea", sea.getTexture(), 9);
        shader.end();
        
        params.assign(8, SmoothValue());
        
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        int res = 600;
        
        for (int si = 0; si < res+1; si++) {
            for (int ti = 0; ti < res*2+1; ti++) {
                float s = PI / res * si;
                float t = PI / res * ti;
                
                ofVec3f v;
                v.x = radius * sin(t) * sin(s);
                v.z = radius * cos(t) * sin(s);
                v.y = radius * cos(s);
                
                mesh.addVertex(v);
                mesh.addTexCoord(ofVec2f(0.5 / res * ti, 1. / res * si));
                
                ofFloatColor c = color.getColor(color.getWidth() / (res*2.) * ti,
                                                color.getHeight() / res * si);
                mesh.addColor(c);
            }
        }
        
        for (int si = 0; si < res; si++) {
            for (int ti = 0; ti < res * 2 + 1; ti++) {
                mesh.addIndex(ti + si * (res * 2 + 1));
                mesh.addIndex(ti + (si+1) * (res * 2 + 1));
            }
        }
        
        params[0].to(1.0);
        current = 0;
    };
    
    void update(){
        for (int i = 0; i < 8; i++) {
            params[i].update();
        }
    };
    
    void draw(){
        ofDisableBlendMode();
        ofEnableDepthTest();
        
        shader.begin();
        for (int i = 0; i < 8; i++) {
            shader.setUniform1f("p" + ofToString(i), params[i].getValue());
        }
        
        mesh.draw(OF_MESH_WIREFRAME);
        shader.end();
    };
    
    void setLayer(int next) {
        
        params[current].to(0.0);
        params[next].to(1.0);
        current = next;
    };
    
private:
    ofVboMesh mesh;
    ofShader shader;
    
    ofImage sea;
    
    // 0: topography, 1: population-density, 2: gdp-per-capita
    // 3: population-growth, 4: unmarried-rate, 5: suicide-rate
    // 6: AIDS, 7; Cancer
    vector<ofImage> texs;
    vector<SmoothValue> params;
    
    int current;
};
