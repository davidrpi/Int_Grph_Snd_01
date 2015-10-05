//
//  Rectangle.cpp
//  hw2
//
//  Created by Kirsti on 15/10/2.
//
//

#include "Rectangle.hpp"


Rectangle::Rectangle(){};

void Rectangle::update() {
    
}

void Rectangle::draw() {
    
    ofPushMatrix();
    
    ofSetColor(color);
    ofTranslate(position.x, position.y);//Move
    ofRotateZ(rotation);//Turn
    ofRect(0, 0, size.x, size.y);
    
    ofPopMatrix();
}