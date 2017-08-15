#include "ofMain.h"
#include "CommonUtil.hpp"

class MeshEarth {
public:
    void setup(float radius){
        
        
        ofImage color;
        
        color.load("img/color.jpg");
        topo.load("img/height.jpg");
        sea.load("img/sea.jpg");
        density.load("img/population_density.jpg");
        
        shader.load("shader/meshEarth");
        
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        int res = 1000;
        
        for (int si = 0; si < res+1; si++) {
            for (int ti = 0; ti < res*2+1; ti++) {
                float s = PI / res * si;
                float t = PI / res * ti;
                
//                float h = height.getColor(height.getWidth() / (res*2.) * ti,
//                                          height.getHeight() / res * si).r / 12.;
//                
//                float r = radius * (h * 5000. / 6371000 + 1.);
                
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
            for (int ti = 0; ti < res*2+1; ti++) {
                
                mesh.addIndex(ti + si * (res * 2 + 1));
                mesh.addIndex(ti + (si+1) * (res * 2 + 1));
            }
        }
        
        topoParam.to(1.);
        denseParam.to(0.);
    };
    
    void update(){
        topoParam.update();
        denseParam.update();
    }
    
    void draw(){
        ofDisableBlendMode();
        ofEnableDepthTest();
        
        shader.begin();
        shader.setUniformTexture("topo", topo.getTexture(), 0);
        shader.setUniform1f("topoParam", topoParam.getValue());
        shader.setUniformTexture("density", density.getTexture(), 1);
        shader.setUniform1f("denseParam", denseParam.getValue());
        shader.setUniformTexture("sea", sea.getTexture(), 2);
        mesh.draw(OF_MESH_WIREFRAME);
        shader.end();
    };
    
    void enableDense(){
        topoParam.to(0.);
        denseParam.to(1.);
    }
    void disableDense(){
        topoParam.to(1.);
        denseParam.to(0.);
    }
    
private:
    ofVboMesh mesh;
    ofShader shader;
    
    ofImage sea;
    ofImage density;
    ofImage topo;
    
    SmoothValue topoParam;
    SmoothValue denseParam;
    
};
