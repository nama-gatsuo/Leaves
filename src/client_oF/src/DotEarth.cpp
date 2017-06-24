#include "DotEarth.hpp"

DotEarth::DotEarth(){}

void DotEarth::setup(){
    
    img.load("img/earth.jpg");
    
    int w = img.getWidth();
    int h = img.getHeight();
    
    float size = 2.0;
    float r = 400.;
    for (float s = 0.0; s < TWO_PI; s += 0.01) {
        for (float t = 0.0; t < PI; t += 0.01) {
            ofVec3f v;
            v.x = r * cos(s) * sin(t);
            v.z = r * sin(s) * sin(t);
            v.y = r * cos(t);
            
            float l = size * sin(t);
            
            ofVec2f st;
            st.x = w - s / TWO_PI * w;
            st.y = t / PI * h;
            
            ofVec3f n = v.getNormalized();
            
            ofFloatColor c = img.getColor(st.x, st.y);
            c.a = 0.6;
            
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
    
}

void DotEarth::draw(){
    
    mesh.draw();
}
