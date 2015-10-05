#pragma once

#include "ofMain.h"
#include "ofxFFTLive.h"
#include "Rectangle.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofxFFTLive fftLive;
    
    list<Rectangle> rectangles;
    Rectangle myMouse;
    
    ofSoundPlayer wire;
    ofSoundPlayer walking;
    ofSoundPlayer boom_kick;
    ofSoundPlayer alien_bomb_timer;
    
    float *fftSmoothed;
    int nBandsToGet;
    
    ofTrueTypeFont font1;
    ofTrueTypeFont font2;
};
