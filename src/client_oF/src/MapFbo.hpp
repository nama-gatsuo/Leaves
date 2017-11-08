#pragma once
#include "ofMain.h"
#include "CommonUtil.hpp"

class MapFbo : public ofFbo {
public:
    void setup(){
        ofFbo::Settings s;
        s.width = 2048;
        s.height = 1024;
        s.internalformat = GL_RGB32F;
        s.numColorbuffers = 2;
        
        allocate(s);
        createAndAttachTexture(GL_RGBA32F, 1);
        createAndAttachTexture(GL_RGBA32F, 2);
        
        getTexture(0).setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        getTexture(1).setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        
        texs.assign(9, ofImage());
        texs[0].load("img/color.jpg");
        texs[1].load("img/layer/topography.jpg");
        texs[2].load("img/layer/population-density.jpg");
        texs[3].load("img/layer/gdp-per-capita.png");
        texs[4].load("img/layer/population-growth.png");
        texs[5].load("img/layer/unmarried-rate.png");
        texs[6].load("img/layer/suicide-rate.png");
        texs[7].load("img/layer/aids.png");
        texs[8].load("img/layer/cancer.png");
        
        shader.load("shader/map");
        shader.begin();
        for (int i = 0; i < 9; i++) {
            shader.setUniformTexture("tex" + ofToString(i), texs[i].getTexture(), i + 3);
        }
        shader.end();
        
        begin();
        activateAllDrawBuffers();
        ofClear(0, 255);
        end();
        
        params.assign(8, SmoothValue());
        params[0].to(1.0);
        
        current = 0;
        count = 0;
    };
    
    void update(){
        count ++;
        
        if (count < 100) {
            begin();
            activateAllDrawBuffers();
            ofClear(0, 255);
            
            shader.begin();
            for (int i = 0; i < 8; i++) {
                params[i].update();
                shader.setUniform1f("p" + ofToString(i+1), params[i].getValue());
            }
            draw(0, 0);
            shader.end();
            
            end();
        }
        
    };
    
    void setLayer(int next) {
        params[current].to(0.0);
        params[next].to(1.0);
        current = next;
        count = 0;
    };
    
    string getLayerName(){
        return layerName[current];
    };
    
private:
    
    // 0: topography, 1: population-density, 2: gdp-per-capita
    // 3: population-growth, 4: unmarried-rate, 5: suicide-rate
    // 6: AIDS, 7; Cancer
    vector<ofImage> texs;
    vector<SmoothValue> params;
    ofShader shader;
    string layerName[8] = {
        "Topography","Population density","GDP per Capita", "Population Growth Rate",
        "Unmarried Rate", "Suicide Rate", "Death Rate by AIDS", "Death Rate by Cancer"
    };
    
    int current;
    int count;
};
