#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    receiver.setup(PORT);
    
    es.setup();
    setupDeferred();
    updateDeferredParam();
    
    cam.setFarClip(2000);
    cam.setNearClip(1.0);
    
    theta.set(0.0);
    rho.set(0.0);
    radius.set(700.);
    radius.to(700.);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    es.update();
    updateDeferredParam();
    
    theta.update();
    rho.update();
    radius.update();
    lookAt.update();
    lookAt.to(ofPoint(0.));
    cam.setPosition(radius.get() * sin(rho.get()) * sin(theta.get()),
                    radius.get() * cos(theta.get()),
                    radius.get() * cos(rho.get()) * sin(theta.get()));
    cam.lookAt(lookAt);
    
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        float lat = m.getArgAsFloat(5);
        float lon = m.getArgAsFloat(6);
        
        cout << "Country: " + m.getArgAsString(0) << endl;
        cout << "City: " + m.getArgAsString(1) << endl;
        cout << "Age: " + m.getArgAsString(2) << endl;
        cout << "Sex: " + m.getArgAsString(3) << endl;
        cout << "Reason: " + m.getArgAsString(4) << endl;
        cout << "lat: " + ofToString(lat) << endl;
        cout << "lon: " + ofToString(lon) << endl;
        
        es.addParticle(PI * lat / 180., PI * lon / 180.);
        
        // calc point
        theta.to(PI * lat / 180. - PI/2. + ofRandom(-0.3, 0.1));
        rho.to(PI * lon / 180. + ofRandom(-0.3, 0.3));
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    shadowLightPass->beginShadowMap(true);
    es.draw(shadowLightPass->getCam(), true);
    shadowLightPass->endShadowMap();
    
    deferred.begin(cam, true);
    es.draw(cam, false);
    deferred.end();
    
//    shadowLightPass->debugDraw();
//    deferred.debugDraw();
    
    if (isShow) panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') isShow = !isShow;
    if (key == ' ') es.addParticle(36 / 180. * PI, 136 / 180. * PI);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

void ofApp::setupDeferred(){
    deferred.init(ofGetWidth(), ofGetHeight());
    ssaoPass = deferred.createPass<SsaoPass>().get();
    
    shadowLightPass = deferred.createPass<ShadowLightPass>().get();
    shadowLightPass->lookAt(ofVec3f(0.0));
    shadowLightPass->setCam(70, 0.1, 5000);
    
    lightingPass = deferred.createPass<PointLightPass>().get();
    ofxDeferredShading::PointLight dlight;
    dlight.ambientColor = ofFloatColor(0.0);
    dlight.diffuseColor = ofFloatColor(0.2, 0.2, 0.2);
    dlight.specularColor = ofFloatColor(0.370929, 0.481341, 0.734486);
    dlight.radius = 200;
    dlight.intensity = 0.462755;
    lightingPass->addLight(dlight);
    lightingPass->addLight(dlight);
    
    deferred.createPass<HdrBloomPass>();
    dofPass = deferred.createPass<DofPass>().get();
    
    // gui
    panel.setup();
    
    ao.setName("Ambient Occlusion");
    ao.add(ao_rad.set("Occlusion Radius", 5.0, 0.1, 100.0));
    ao.add(ao_dark.set("Darkness", 0.8, 0.1, 5.0));
    panel.add(ao);
    
    shadow.setName("Shadow Light");
    shadow.add(sha_amb.set("Ambient", 0.0, 0.0, 1.0));
    shadow.add(sha_dif.set("Diffuse", 0.0, 0.3, 1.0));
    shadow.add(sha_dark.set("Shadow Darkness", 0.4, 0.0, 1.0));
    shadow.add(sha_blend.set("Lighting Blend", 0.4, 0.0, 1.0));
    panel.add(shadow);
    
    dof.setName("Defocus Blur");
    dof.add(dof_blur.set("Max Blur", 0.5, 0.0, 1.0));
    dof.add(dof_ape.set("Aperture", 0.1, 0.0, 1.0));
    dof.add(dof_focal.set("Focus Distance", 0.2, 0.0, 1.0));
    panel.add(dof);
    
    panel.loadFromFile("settings.xml");
}

void ofApp::updateDeferredParam(){
    
    vector<Particle> ps = es.getParticles();
    int num = lightingPass->getLightsSize();
    for (int i = 0; i < num; i++) {
        if (ps.size() == i) break;
        lightingPass->getLightRef(i).position = ps[i].pos;
    }
    
    shadowLightPass->setPosition(1500 * sin(ofGetElapsedTimef()*0.1),0, 1500 * cos(ofGetElapsedTimef()*0.1));
    shadowLightPass->lookAt(ofVec3f(0.0));
    
    
    ssaoPass->setOcculusionRadius(ao_rad.get());
    ssaoPass->setDrakness(ao_dark.get());
    
    shadowLightPass->setAmbientColor(ofFloatColor(sha_amb.get()));
    shadowLightPass->setDiffuseColor(ofFloatColor(sha_dif.get()));
    shadowLightPass->setDarkness(sha_dark.get());
    shadowLightPass->setBlend(sha_blend.get());
        
    dofPass->setFocus(dof_focal.get());
    dofPass->setMaxBlur(dof_blur.get());
    dofPass->setAperture(dof_ape.get());
    
}
