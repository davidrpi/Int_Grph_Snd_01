#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetDepthTest(true);

    physics.init();
    physics.setGravity(0, -9.8);
    physics.createBounds();
    physics.setFPS(60);
    fftLive.setMirrorData(false);
    fftLive.setup();
    currentCircle.reset();

    bump = shared_ptr<Balloon>(new Balloon(ofGetWidth()/2, ofGetHeight(), ofGetWidth()/4, physics));

    soundSustained = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    physics.update();
    fftLive.update();

    float * audioData = new float[16];
    fftLive.getFftPeakData(audioData, 16);
    soundSustained = false;

    for (int i = 0; i < 16; i++){
        if (audioData[i] > 0.7){
            //to account for small bits of sound
            soundSustained = true;
        }
        if (audioData[i] > 0.9){
            if (!currentCircle){
                shared_ptr<Balloon> b(new Balloon(ofRandom(0, ofGetWidth()), ofGetHeight()/2, 1, physics));
                objects.push_back(b);
                currentCircle = b;
                //cout << "NEW BALLOON!" << endl;
            }
            currentCircle->inflate(0.5);
        }
    }
    if (!soundSustained){
        if (currentCircle){
            shared_ptr<ofxBox2dJoint> joint(new ofxBox2dJoint);
            joint->setup(physics.getWorld(), bump->getShape()->body, currentCircle->getShape()->body);
        }
        currentCircle.reset();
    }
    delete[] audioData;
}

//--------------------------------------------------------------
void ofApp::draw(){
    //fftLive.draw();

    for (int i = 0; i < objects.size(); i++){
        objects[i]->draw();
    }
    for (int i = 0; i < joints.size(); i++){
        ofSetHexColor(0x444342);
        joints[i]->draw();
    }
    bump->draw();

    physics.drawGround();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

/*void ofApp::createNewCircle(float x, float y, float r){
    shared_ptr<ofxBox2dCircle> newCircle(new ofxBox2dCircle());
    newCircle->setPhysics(3.0, 0.53, .1);
    newCircle->setMassFromShape = true;
    newCircle->setup(physics.getWorld(), x, y, r);
    objects.push_back(newCircle);
    currentCircle = newCircle;
}*/
