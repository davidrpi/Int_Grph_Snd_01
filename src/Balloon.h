#include "ofMain.h"
#include "ofMesh.h"
#include "ofxBox2d.h"

class Balloon{
public:
    Balloon(float x, float y, float r, float density, ofxBox2d &physics);
    ~Balloon();

    shared_ptr<ofxBox2dCircle> getShape() {return shape;}
    void inflate(float v);
    void draw();

private:
    shared_ptr<ofxBox2dCircle> shape;
    ofMesh mesh;
    float radius;
};
