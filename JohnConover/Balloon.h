#include "ofMain.h"
#include "ofMesh.h"
#include "ofxBox2d.h"

class Balloon{
public:
    Balloon(float x, float y, float r, float density, ofColor color, ofxBox2d &physics);
    ~Balloon();

    shared_ptr<ofxBox2dCircle> getShape() {return shape;}


    void inflate(float v);
    void tieOff(ofxBox2d &physics);
    void draw();

private:
    void init(float x, float y, float r, float density, ofxBox2d &physics);

    ofxBox2d *physics;
    ofColor color;
    shared_ptr<ofxBox2dCircle> shape;
    ofMesh mesh;
    float radius;
    float density;
};
