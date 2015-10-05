#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(246, 177, 169);
    
    ofSetFrameRate(70);
    
    //Draw rectangles
    myMouse = Rectangle();
    myMouse.size.x = 80;
    myMouse.size.y = 80;
    myMouse.rotation = (myMouse.position.x+myMouse.position.y)*5;
    myMouse.color = ofColor(ofRandom(201, 202), ofRandom(231, 252), ofRandom(235, 251));
    
    //Load in sounds
    wire.loadSound("wire.wav");
    walking.loadSound("walking.wav");
    boom_kick.loadSound("boom-kick.wav");
    alien_bomb_timer.loadSound("alien-bomb-timer.wav");
    
    //Smooth out the fft
    fftLive.setMirrorData(false);
    fftLive.setup();
    fftSmoothed = new float[8192];
    for (int i=0; i<8192; ++i){
        fftSmoothed[i]=0;
    }
    nBandsToGet = 128;
    
    //Text
    font1.loadFont("SnellRoundhand.ttc", 30);
    font2.loadFont("Phosphate.ttc", 30);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float*audioData = new float[8];
    fftLive.getFftPeakData(audioData, 8);
    
    //When getting the sound, larger the rectangles and change color
    for (int i=0; i<8; i++){
        if (audioData[i] > 0.9){
            for (list<Rectangle>::iterator it = rectangles.begin(); it!=rectangles.end(); ++it) {
                it->color = ofColor(ofRandom(10, 202), ofRandom(186, 252), ofRandom(181, 251));
                it->size.x += 3;
                it->size.y += 3;
                if(it->size.x > 600){
                    it = rectangles.erase(it);
                    --it;
                }
            }
        }
    }
    
    fftLive.update();
    
    delete [] audioData;
    
    ofSoundUpdate();
    
    //Check the sound already been load
    bool load_wire = false;
    bool load_walking = false;
    bool load_boom_kick = false;
    bool load_alien_bomb_timer = false;
    
    //Load sound when rectangles touch the borden
    for (list<Rectangle>::iterator it = rectangles.begin(); it!=rectangles.end(); ++it) {
        if(it->position.x<0 && !load_wire){
            wire.play();
            load_wire = true;
            it = rectangles.erase(it);
            --it;
        }
        if(it->position.x>ofGetWidth() && !load_walking){
            walking.play();
            load_walking = true;
            it = rectangles.erase(it);
            --it;
        }
        if(it->position.y<0 && !load_boom_kick){
            boom_kick.play();
            load_boom_kick = true;
            it = rectangles.erase(it);
            --it;
            
        }
        if (it->position.y>ofGetHeight() && !load_alien_bomb_timer){
            alien_bomb_timer.play();
            load_alien_bomb_timer = true;
            it = rectangles.erase(it);
            --it;
        }
    }
    
    //Set volume
    wire.setVolume(5);
    walking.setVolume(5);
    boom_kick.setVolume(5);
    alien_bomb_timer.setVolume(5);
    
    //Put fft into a smoothed array
    float *val = ofSoundGetSpectrum(nBandsToGet);
    for (int i=0; i<nBandsToGet; ++i){
        //Let smoothed calue sink to zero
        fftSmoothed[i] *= 0.96f;
        //Take the max of smoothed or incoming
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
    }

    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //Show mouse
    ofFill();
    for (list<Rectangle>::iterator it = rectangles.begin(); it!=rectangles.end(); ++it) {
        it->draw();
    }
    ofNoFill();
    myMouse.draw();
    
    //Show volume
    ofEnableAlphaBlending();
    ofSetColor(0,0,0,100);
    ofDisableAlphaBlending();
    float width = (float)(5*128) / nBandsToGet;
    for (int i = 0;i < nBandsToGet; i++){
        ofRect(700+i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
    }
    
    //Show text
    font1.drawString("Drag mouse to play.", 48, 240);
    font1.drawString("Touch borden to trigger sounds.", 48, 280);
    font1.drawString("Press key to clear screen.", 48, 320);
    font2.drawString("Leying Hu", 50, 160);
    font2.drawString("Interactivity && Graphics && Sound", 50, 100);
    font2.drawString("___________", 50, 180);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //Clear all rectangles on the screen
    while (rectangles.size() > 0) {
        rectangles.pop_front();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    myMouse.position.x = x;
    myMouse.position.y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    
    //Add rotated rectangles with random blue colors
    Rectangle r =  Rectangle();
    r.position.x = x;
    r.position.y = y;
    r.size.x = 90;
    r.size.y = 90;
    r.color = ofColor(ofRandom(201, 202), ofRandom(231, 252), ofRandom(235, 251));
    r.rotation = (x+y)*5;
    rectangles.push_back(r);
    
    //Delete old rectangles
    while (rectangles.size() > 90) {
        rectangles.pop_front();
    }
    
    //Show mouse
    myMouse.position.x = x;
    myMouse.position.y = y;
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
