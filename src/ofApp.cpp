#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetDepthTest(true);
    ofBackground(ofColor(15, 8, 37));
    physics.init();
    physics.setGravity(0, -9.8);
    // physics.createBounds();
    physics.setFPS(60);
    fftLive.setMirrorData(false);
    fftLive.setup();
    currentCircle.reset();

    anchor = shared_ptr<Balloon>(new Balloon(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/200, 0.0, ofColor::lightYellow, physics));

    ofEnableLighting();
    pointLight.setPointLight();
    pointLight.setAttenuation(0.9f);
    pointLight.setPosition(anchor->getShape()->getPosition());

    soundSustained = false;

    sunMat = ofMaterial();
    sunMat.setEmissiveColor(ofFloatColor(255, 215, 0));

    easyCam.setTarget(anchor->getShape()->getPosition());
    easyCam.setFarClip(10000);
}

//--------------------------------------------------------------
void ofApp::update(){

    physics.update();
    fftLive.update();

    float * audioData = new float[16];
    fftLive.getFftPeakData(audioData, 16);
    soundSustained = false;

    for (int i = 0; i < 16; i++){
        if (audioData[i] > 0.6){
            //to account for small bits of sound
            soundSustained = true;
        }
        if (audioData[i] > 0.99){
            if (!currentCircle){
                ofColor color(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0,255));
                shared_ptr<Balloon> b(new Balloon(ofRandom(0, ofGetWidth()), 3*ofGetHeight()/4, 1, 3.0, color, physics));
                objects.push_back(b);
                currentCircle = b;
                //cout << "NEW BALLOON!" << endl;
            }
            currentCircle->inflate(audioData[i]);
        }
    }
    if (!soundSustained){
        if (currentCircle){
            shared_ptr<ofxBox2dJoint> joint(new ofxBox2dJoint);
            // currentCircle->tieOff(physics);
            joint->setup(physics.getWorld(), anchor->getShape()->body, currentCircle->getShape()->body);
        }
        currentCircle.reset();
    }
    delete[] audioData;
}

//--------------------------------------------------------------
void ofApp::draw(){
    // fftLive.draw();

    easyCam.begin();
    // ofQuaternion startRotation(90, ofVec3f(0,1,0));     //quaternion to rotate camera to start position looking straight at the anchor
    pointLight.enable();

    for (int i = 0; i < objects.size(); i++){
        objects[i]->draw();
    }
    // for (int i = 0; i < joints.size(); i++){
    //     ofSetHexColor(0x444342);
    //     joints[i]->draw();
    // }
    sunMat.begin();
    anchor->draw();
    sunMat.end();

    ofSetColor(ofColor::white);

    ofPushMatrix();
    ofTranslate(anchor->getShape()->getPosition());
    ofNoFill();
    ofCircle(0, 0, 100.0);
    ofFill();
    ofPopMatrix();

    physics.drawGround();

    pointLight.disable();
    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofVec3f lookAtDir = 9.8 * easyCam.getLookAtDir();   //sets gravity to looking direction
    switch (key) {
        case ' ':
            physics.setGravity(0,0);
            break;
        case OF_KEY_UP:
            physics.setGravity(lookAtDir);
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
