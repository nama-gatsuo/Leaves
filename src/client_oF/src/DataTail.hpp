#include "ofMain.h"

class TailNode {
public:
    TailNode(const ofVec3f& pos, const ofFloatColor& col, int index):p(pos){
        
        c = col * 0.01;
        float s = ofMap(index, 0, 100, 0.1, 1.5);
        ofVec3f axis = pos.getNormalized();
        
        ofMatrix4x4 matrix;
        matrix.glTranslate(pos);
        matrix.glRotate(index * 8., axis.x, axis.y, axis.z);
        matrix.glScale(s, s, s);
        
        vector<ofVec3f> varray = {
            ofVec3f(1, 1, 1), ofVec3f(-1, -1, 1), ofVec3f(-1, 1, - 1), ofVec3f(1, -1, -1)
        };
        
        for (int i = 0; i < 4; i++) {
            varray[i] = varray[i] * matrix;
        }
        
        vector<ofIndexType> indices = {
            2, 1, 0,   0, 3, 2,   1, 3, 0,   2, 3, 1
        };
        
        vector<ofFloatColor> carray = {c, c, c, c};
        
        mesh.addVertices(varray);
        mesh.addIndices(indices);
        mesh.addColors(carray);
        
    }
    void update(){
        count++;
        float opacity = (float)(max_count - count) / (float)max_count;
        
        for (int i = 0; i < 4; i++) {
            mesh.setColor(i, c * opacity);
        }
    }
    void draw(){
        mesh.draw(OF_MESH_FILL);
    }
    
    bool isDead(){
        return count > max_count;
    }
    
private:
    ofVec3f p;
    ofFloatColor c;
    float angle;
    int count = 0;
    int max_count = 800; // sequence frame count
    ofVboMesh mesh;
    
};

class DataTail {
public:
    void setup(const ofVec3f& endPos, const ofFloatColor& col){
        float startRatio = 0.96;
        head = endPos * startRatio;
        delta = endPos * (1. - startRatio) * (1. / max_count);
        c = col;
        count = 0;
    };
    void update(){
        
        if (count <= max_count) {
            
            count ++;
            
            head += delta;
            
            if (count % interval == 0) {
                TailNode t(head, c, nodes.size());
                nodes.push_back(t);
            }
            
        }
        
        // check life
        for (int i = 0; i < nodes.size(); i++){
            nodes[i].update();
            if (nodes[i].isDead()) {
                nodes.erase( nodes.begin() + i );
            }
        }
        
    };
    void draw(){
        
        for (int i = 0; i < nodes.size(); i++) {
            nodes[i].draw();
        }
        
    };
    ofVec3f& getHead(){
        return head;
    };
    
    void clear(){
        nodes.clear();
    };
    
    bool isEnd(){
        return count > max_count;
    }
private:
    ofVec3f head;
    ofVec3f delta;
    int interval = 5;
    int count = 801;
    const int max_count = 800; // sequence frame count
    ofFloatColor c;
    vector<TailNode> nodes;
};

