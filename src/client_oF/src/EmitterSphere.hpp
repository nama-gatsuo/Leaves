#pragma once
#include "ofMain.h"

class Particle {
public:
    ofVec3f pos;
    ofVec3f vel;
    ofVboMesh lines;
    
    float life = 700.;
    bool isDead = false;
    float thres;
    float speed;
    
    Particle(ofVec3f v, float s){
        pos = v * 300.;
        vel = v * s;
        speed = s;
        thres = 280.0;
        
        lines.setMode(OF_PRIMITIVE_POINTS);
    };
    
    void update(const ofMesh &sphere){
        life -= speed;
        if (life < 0) isDead = true;
        
        pos += vel;
        
        lines.clearVertices();
        vector<ofVec3f> vs = sphere.getVertices();
        
        for (auto v : vs) {
            
            float length = pos.distance(v);
            if (length < thres) {
                lines.addVertex(v);
            }
            
        }
    }
};

class EmitterSphere {
public:
    void setup(){
        
        gbShader.load("shader/scene/gb");
        
        lShader.setGeometryInputType(GL_POINTS);
        lShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
        lShader.setGeometryOutputCount(24);
        
        lShader.load("shader/scene/lines.vert", "shader/scene/lines.frag", "shader/scene/lines.geom");
        sphere = ofMesh::sphere(300);
        for (int i = 0; i < sphere.getNumVertices(); i++) {
            sphere.addColor(ofFloatColor(1.0));
        }
        p = ofMesh::sphere(10, 3);
        for (int i = 0; i < p.getNumVertices(); i++) {
            p.addColor(ofFloatColor(0.8, 1.2, 1.0));
        }
        
        tex.load("img/earth.jpg");
        
    };
    void update(){
        
        float length;
        vector<Particle>::iterator it = ps.begin();
        
        for (int i = 0; i < ps.size(); i++) {
            
            if (ps[i].isDead) {
                ps.erase(it + i);
            } else {
                ps[i].update(sphere);
            }
        }
        
    };
    void draw(ofCamera cam, bool isShadow){
        
        ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
        
        gbShader.begin();
        gbShader.setUniform1i("isShadow", isShadow?1:0);
        gbShader.setUniformMatrix4f("normalMatrix", normalMatrix);
        gbShader.setUniform1f("farClip", cam.getFarClip());
        gbShader.setUniform1f("nearClip", cam.getNearClip());
        gbShader.setUniformTexture("earthTex", tex.getTexture(), 1);
        
        for (auto part : ps) {
            ofPushMatrix();
            ofTranslate(part.pos);
            p.draw();
            ofPopMatrix();
        }
        
        sphere.draw();
        
        gbShader.end();
        
        for (auto part : ps) {
            
            lShader.begin();
            lShader.setUniform1i("isShadow", isShadow?1:0);
            lShader.setUniform3f("to", part.pos);
            lShader.setUniformMatrix4f("normalMatrix", normalMatrix);
            lShader.setUniform1f("farClip", cam.getFarClip());
            lShader.setUniform1f("nearClip", cam.getNearClip());
            part.lines.draw();
            lShader.end();
        }
        
    };
    
    void addParticle(float lat, float lon){
        ofVec3f v;
//        lon += PI;
        lat = - PI/2. + lat;
        v.x = sin(lon) * sin(lat);
        v.z = cos(lon) * sin(lat);
        v.y = cos(lat);
        v.normalize();
        
        ps.push_back(Particle(v, ofRandom(0.5, 1.)));
    };
private:
    ofShader lShader;
    ofShader gbShader;
    ofImage tex;
    
    ofVboMesh sphere;
    ofVboMesh p;
    vector<Particle> ps;
    
    float thresh = 100.;
};


