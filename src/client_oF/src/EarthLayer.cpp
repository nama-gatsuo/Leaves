#include "EarthLayer.hpp"

EarthLayer::EarthLayer(){}

void EarthLayer::setup(){
    ofFile file;
    file.open("img/world.svg");
    ofBuffer buffer = file.readToBuffer();
    
    ofXml svg;
    svg.loadFromBuffer(buffer.getText());
    
    int n = svg.getNumChildren();
    
    float width = ofToFloat(svg.getAttribute("width"));
    float height = ofToFloat(svg.getAttribute("height"));
    
    for (int i = 0; i < n; i++) {
        
        CountryData country;
        
        svg.setToChild(i);
        
        country.id = svg.getAttribute("id");
        
        ofVec2f start(0,0);
        country.pathes = createPath(svg, start);
        
        countries.push_back(country);
        
        svg.reset();
        
    }
    
    fbo.allocate(2506.2067, 1396.0625);
    fbo.begin();
    ofClear(0);
    for (int i = 0; i < countries.size(); i++) {
        for (int j = 0; j < countries[i].pathes.size(); j++) {
            countries[i].pathes[j].setColor(ofColor(ofRandom(256),ofRandom(256),ofRandom(256)));
            countries[i].pathes[j].draw();
            
        }
    }
    ofSetColor(255);
    fbo.end();
}

void EarthLayer::setLayer(){}
void EarthLayer::draw(){}

vector<ofPath> EarthLayer::createPath(ofXml &svg, ofVec2f& start){
    int cn = svg.getNumChildren();
    
    vector<ofPath> pathes;
    
    if (cn == 0) {
        
        string d = svg.getAttribute("d");
        ofPath p = stringToPath(d, start);
        pathes.push_back(p);
        
    } else {
        
        ofVec2f trans(0,0);
        string ts = svg.getAttribute("transform");
        if (ts != "") {
            
            ts.erase(ts.begin(), ts.begin()+10);
            ts.pop_back();
            
            vector<string> tss = ofSplitString(ts, ",");
            trans.x = ofToFloat(tss[0]);
            trans.y = ofToFloat(tss[1]);
            //cout << "x: " + tss[0] + ", y: " + tss[1] << endl;
        }
        trans += start;
        
        for (int j = 0; j < cn; j++) {
            svg.setToChild(j);
            
            
            vector<ofPath> pathes2 = createPath(svg, trans);
            
            //copy(pathes2.begin(), pathes2.end(), back_inserter(pathes));
            pathes.insert(pathes.end(), pathes2.begin(), pathes2.end());
            
            svg.setToParent();
        }
        
    }

    return pathes;
}

ofPath EarthLayer::stringToPath(string &s, ofVec2f& start){
    
    vector<string> darray = ofSplitString(s, " ");
    ofPath path;
    path.setCurveResolution(4);
    
    ofVec2f last = start;
    int mode = 0;
    
    for (int i = 0; i < darray.size();) {
        
        if (darray[i] == "m") {
            
            path.moveTo(stringToVec2(darray[i+1]) + last);
            i += 2;
            
            mode = 1;
            
        } else if (darray[i] == "M"){
            path.moveTo(stringToVec2(darray[i+1]));
            i += 2;
            
            mode = 2;
            
        } else if (darray[i] == "c") {
            
            last = getLastPoint(path);
            
            path.bezierTo(stringToVec2(darray[i+1]) + last,
                          stringToVec2(darray[i+2]) + last,
                          stringToVec2(darray[i+3]) + last);
            i += 4;
            
            mode = 3;
            
        } else if (darray[i] == "C") {
            
            path.bezierTo(stringToVec2(darray[i+1]),
                          stringToVec2(darray[i+2]),
                          stringToVec2(darray[i+3]));
            i += 4;
            
            mode = 4;
        
        } else if (darray[i] == "l") {
            
            last = getLastPoint(path);
            path.lineTo(stringToVec2(darray[i+1]) + last);
            i += 2;
            
            mode = 5;
        } else if (darray[i] == "L") {
            
            path.lineTo(stringToVec2(darray[i+1]));
            i += 2;
            
            mode = 6;
            
        } else if (darray[i] == "z" || darray[i] == "Z") {
            
            path.close();
            i++;
            
        } else {
            last = getLastPoint(path);
            
            if (mode == 1) {
                
                path.moveTo(stringToVec2(darray[i]) + last);
                i++;
                
            } else if (mode == 2) {
                    
                path.moveTo(stringToVec2(darray[i]));
                i++;
                
            } else if (mode == 3) {
                
                path.bezierTo(stringToVec2(darray[i+0]) + last,
                              stringToVec2(darray[i+1]) + last,
                              stringToVec2(darray[i+2]) + last);
                i += 3;
            } else if (mode == 4) {
                
                path.bezierTo(stringToVec2(darray[i+0]),
                              stringToVec2(darray[i+1]),
                              stringToVec2(darray[i+2]));
                i += 3;
                
            } else if (mode == 5) {
                
                path.lineTo(stringToVec2(darray[i]) + last);
                i++;
            } else if (mode == 6) {
                
                path.lineTo(stringToVec2(darray[i]));
                i++;
            }
            
        }
        
    }
    
    
    return path;
    
}

ofVec2f EarthLayer::stringToVec2(string &s){
    vector<string> sarray = ofSplitString(s, ",");
    return ofVec2f(ofToFloat(sarray[0]), ofToFloat(sarray[1]));
}

ofVec2f EarthLayer::getLastPoint(ofPath &path){
    
    vector<ofPolyline> polies = path.getOutline();
    ofPolyline poly = polies.at(polies.size()-1);
    
    vector<ofPoint> ps = poly.getVertices();
    ofPoint p = ps.size() > 0 ? ps.at(ps.size()-1) : ofPoint();
    
    return ofVec2f(p.x, p.y);
    
}
