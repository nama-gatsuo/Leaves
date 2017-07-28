#include "DotEarth.hpp"

DotEarth::DotEarth(){}

void DotEarth::setup(float rad){
    
    img.load("img/earth.jpg");
    
    int w = img.getWidth();
    int h = img.getHeight();
    
    float size = 2.0;
    for (float s = 0.0; s < TWO_PI; s += 0.01) {
        for (float t = 0.0; t < PI; t += 0.01) {
            ofVec3f v;
            v.x = rad * cos(s) * sin(t);
            v.z = rad * sin(s) * sin(t);
            v.y = rad * cos(t);
            
            float l = size * sin(t);
            
            ofVec2f st;
            st.x = w - s / TWO_PI * w;
            st.y = t / PI * h;
            
            ofVec3f n = v.getNormalized();
            
            ofFloatColor c = img.getColor(st.x, st.y);
            c.a = 0.8;
            
            float grey = (c.r+c.g+c.b) / 3.;
            if (grey > 0.07 && c.g > 0.1) {
            
                c.set(c.r);
                
                ofVec3f axisX = n.getCrossed(ofVec3f(0.,1.0,0.)).normalize();
                ofVec3f axisZ = axisX.getCrossed(n).normalize();
                
                mesh.addVertex(v + l * n);
                mesh.addColor(c);
                
                mesh.addVertex(v - l * n);
                mesh.addColor(c);
                
                mesh.addVertex(v + l * axisX);
                mesh.addColor(c);
                
                mesh.addVertex(v - l * axisX);
                mesh.addColor(c);
                
                mesh.addVertex(v + l * axisZ);
                mesh.addColor(c);
                
                mesh.addVertex(v - l * axisZ);
                mesh.addColor(c);
                
                //mesh.addNormal(n);
                //mesh.addTexCoord(st);
            
            }
            
        }
        
    }
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    
    black = ofMesh::sphere(rad * 0.99);
    
}

void DotEarth::draw(){
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    //ofEnableDepthTest();
    ofDisableBlendMode();
    
    //ofPushStyle();
    mesh.draw();
    //ofSetColor(0);
    //black.draw();
    //ofPopStyle();
    
}
