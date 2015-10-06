#include "Balloon.h"

Balloon::Balloon(float x, float y, float r, float density, ofColor color, ofxBox2d &physics){
    init(x, y, r, density, physics);
    mesh = ofMesh::sphere(r);
    radius = r;
    this->density = density;
    this->color = color;
}

Balloon::~Balloon(){

}

void Balloon::init(float x, float y, float r, float density, ofxBox2d &physics){
    shape = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle());
    shape->setPhysics(density, 0.53, .1);
    shape->setMassFromShape = true;
    shape->setup(physics.getWorld(), x, y, r);
}

void Balloon::draw(){
    ofPushMatrix();
        ofTranslate(shape->getPosition());
        ofRotateZ(shape->getRotation());
        ofScale(radius, radius, radius);
        ofSetColor(color);
        mesh.draw();
        // ofSetColor(ofColor::black);
        // mesh.drawWireframe();
    ofPopMatrix();

    shape->draw();
}

void Balloon::inflate(float v){
    shape->setRadius(shape->getRadius() + v);
    radius += v;
    // shape->body->mass = 4.0/3.0 * 3.14159 * radius * radius * radius;
}

void Balloon::tieOff(ofxBox2d &physics){
    ofVec3f pos = shape->getPosition();
    shape->setup(physics.getWorld(),pos.x, pos.y, radius);
    shape->setPhysics(density, 0.53, .1);
    shape->setMassFromShape = true;
}
