/*
 * Author: Ethan Dickey
 * Assignment Title: Assignment 1
 * Assignment Description: This program draws a scalable graph.
 * Due Date: 1/28/2019
 * Date Created: 1/17/2019
 * Date Last Modified: 1/26/2019
 */
#include "point.h"

/**
 * description: point constructor
 * return: none
 * precondition: none
 * postcondition: the point class is initialized with (0,0) for the points
 *  and black for the color
 */
point::point(): x(0), y(0), color(color_rgb(0,0,0)){}

/**
 * description: point constructor
 * return: none
 * precondition: none
 * postcondition: the point class is initialized with (0,0) for the points
 *  and black for the color
 */
point::point(int ex, int why): x(ex), y(why), color(color_rgb(0,0,0)){}

/**
 * description: copy constructor
 * return: none
 * precondition: the passed in point is initialized
 * postcondition: this instance of the class is equivalent to the passed in
 *  class
 */
point::point(const point& p){
    this->x = p.x;
    this->y = p.y;
    this->color = p.color;
}

/**
 * description: point class destructor
 * return: none
 * precondition: point is initialized
 * postcondition: point has been destructed
 */
point::~point(){}

/**
 * description: sets the y value
 * return: void
 * precondition: point is initialized
 * postcondition: y has been set
 */
void point::setY(int y){this->y = y;}

/**
 * description: sets the x value
 * return: void
 * precondition: point is initialized
 * postcondition: x has been set
 */
void point::setX(int x){this->x = x;}

/**
 * description: sets the color_rgb value
 * return: void
 * precondition: point is initialized
 * postcondition: the color_rgb value has been set
 */
void point::setColor(color_rgb c){this->color = c;}

/**
 * description: returns the x value
 * return: int -- x value
 * precondition: point is initialized
 * postcondition: x value has been returned
 */
int point::getX(){return x;}

/**
 * description: returns the y value
 * return: int -- y value
 * precondition: point is initialized
 * postcondition: y value has been returned
 */
int point::getY(){return y;}

/**
 * description: returns the color value
 * return: color_rgb -- color value
 * precondition: point is initialized
 * postcondition: color value has been returned
 */
color_rgb point::getColor(){return color;}

/**
 * description: copy assignment operator
 * return: point& -- this class to promote chaining
 * precondition: the passed in point is initialized
 * postcondition: this instance of the class is equivalent to the passed in
 *  class
 */
point& point::operator=(const point& rhs){
    this->x = rhs.x;
    this->y = rhs.y;
    this->color = rhs.color;
    return *this;
}

/**
 * description: displays the point to the passed in output stream (x, y)
 * return: void
 * precondition: the point class is initialized
 * postcondition: the point has been displayed on the output stream (x, y)
 */
void point::display(ostream& out){
    out << "( " << x << ", " << y << ")";
}

/**
 * description: draws the point in the passed in SDL_Plotter class
 * return: void
 * precondition: the point class is initialized
 * postcondition: the point has been drawn on the screen usin the SDL_Plotter
 *  class
 */
void point::draw(SDL_Plotter& g){
    g.plotPixel(x, g.getRow()-y, color.getR(), color.getG(), color.getB());
}

/**
 * description: draws a thick point in the passed in SDL_Plotter class
 * return: void
 * precondition: the point class is initialized
 * postcondition: the thick point has been drawn on the screen usin the SDL_Plotter
 *  class
 */
void point::drawThick(SDL_Plotter& g, int thickness){
    for(int dx = 0; dx < thickness && x + dx < g.getCol(); dx++ ){
        for(int dy = 0; dy < thickness && y + dy < g.getRow(); dy++ ){
            g.plotPixel( x + dx, g.getRow() - (y + dy), color.getR(), color.getG(), color.getB());
        }
    }
}
