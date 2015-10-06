#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxFFTLive.h"
#include "Balloon.h"

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
		void createNewCircle(float x, float y, float r);

		shared_ptr<Balloon> anchor;
		bool soundSustained;
		shared_ptr<Balloon> currentCircle;

		ofLight pointLight;
		ofxBox2d physics;
		ofxFFTLive fftLive;

		vector<shared_ptr<Balloon> > objects;
		vector<shared_ptr<ofxBox2dJoint> > joints;

        ofMaterial sunMat;
        ofEasyCam easyCam;

};
