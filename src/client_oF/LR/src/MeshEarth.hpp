#include "ofMain.h"
#include "CommonUtil.hpp"
#include "MapFbo.hpp"

class MeshEarth {
public:
    void setup(float radius){
        
        shader.load("shader/meshEarth");
        
        createMesh(large, radius, 768);
        createMesh(small, radius, 512);
        
        map.setup();
        
    };
    
    void createMesh(ofVboMesh& mesh, float radius, int res){
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        
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
                
            }
        }
        
        for (int si = 0; si < res; si++) {
            for (int ti = 0; ti < res * 2 + 1; ti++) {
                mesh.addIndex(ti + si * (res * 2 + 1));
                mesh.addIndex(ti + (si+1) * (res * 2 + 1));
            }
        }
    };
    
    void update(){
        map.update();
    };
    
    void draw(const ofCamera& cam){
        float dist = cam.getGlobalPosition().length();
        
        ofDisableBlendMode();
        ofEnableDepthTest();
        
        shader.begin();
        shader.setUniformTexture("colorMap", map.getTexture(0), 1);
        shader.setUniformTexture("bumpMap", map.getTexture(1), 2);
        
        // level of detail
        if (dist < 450. && dist > 400.) {
            large.draw(OF_MESH_WIREFRAME);
        } else {
            small.draw(OF_MESH_WIREFRAME);
        }
        
        shader.end();
    };
    
    void setLayer(int next) {
        map.setLayer(next);
    };
    
    MapFbo map;

private:
    ofVboMesh large;
    ofVboMesh small;
    
    ofShader shader;
    
};
