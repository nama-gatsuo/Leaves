#include "ofMain.h"

class DataMark : public ofNode{
public:
    DataMark(ofVec3f& p) : count(0), max_count(300) {
        opacity = 0.;
        isDead = false;
        c = ofFloatColor(1.);
        
        ofVec3f ov[6] = {
            ofVec3f(3,0,0), ofVec3f(-3,0,0), ofVec3f(0,3,0),
            ofVec3f(0,-3,0), ofVec3f(0,0,48), ofVec3f(0,0,-12)
        };
        unsigned oi[24] = {
            0, 2, 4, 0, 4, 3, 0, 3, 5, 0, 5, 2,
            1, 2, 5, 1, 5, 3, 1, 3, 4, 1, 4, 2
        };
        
        for (int i = 0; i < 6; i++) {
            ofVec3f v = ov[i];
            
            mesh.addVertex(v);
            mesh.addColor(ofFloatColor(1.));
        }
        for (int i = 0; i < 24; i++) {
            mesh.addIndex(oi[i]);
        }
        
        ofVec3f dir = p.getNormalized();
        ofNode::lookAt(dir);
        ofNode::setPosition(p);
    };
    void update(){
        
        count++;
        if (count > max_count) isDead = true;
        
        float opacity = (float)(max_count - count) / (float)max_count;
        
        for (int i = 0; i < 6; i++) {
            mesh.setColor(i, c * opacity);
        }
        
    };
    void customDraw(){
        
        mesh.draw(OF_MESH_WIREFRAME);
        
    };
    
    bool isDead;
private:

    float opacity;
    ofVboMesh mesh;
    int count;
    int max_count;
    
    ofFloatColor c;
};
