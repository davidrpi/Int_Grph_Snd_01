//
//  Rectangle.hpp
//  hw2
//
//  Created by Kirsti on 15/10/2.
//
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include "ofMain.h"

class Rectangle {

    
public:
    ofVec2f position;
    ofVec2f size;
    float rotation;
    
    ofColor color;
    
    Rectangle();
    
    void update();
    void draw();

};

#endif /* Rectangle_hpp */
