/*
 * Author: Ethan Dickey
 * Assignment Title: Assignment 1
 * Assignment Description: This program draws a scalable graph.
 * Due Date: 1/28/2019
 * Date Created: 1/17/2019
 * Date Last Modified: 1/26/2019
 */
#include "line.h"

/**
 * description: line constructor
 * return: none
 * precondition: none
 * postcondition: the line class is initialized with (0,0) for the points
 *  and black for the color
 */
line::line(): p1(point(0,0)), p2(point(0,0)), color(color_rgb(0,0,0)), currentColor(0){}

/**
 * description: line constructor with 2 point arguments
 * return: none
 * precondition: none
 * postcondition: the line class is initialized with pt1 and pt2 for the points
 *  and black for the color
 */
line::line(point pt1, point pt2): p1(pt1), p2(pt2), color(color_rgb(0,0,0)), currentColor(0){}

/**
 * description: line class destructor
 * return: none
 * precondition: line is initialized
 * postcondition: line has been destructed
 */
line::~line(){}

/**
 * description: prints the line to the passed in output stream
 * return: void
 * precondition: line is initialized
 * postcondition: the line has been printed to the passed in output stream
 */
void line::display(ostream& out){
    out << "Point1: ";
    p1.display(out);
    out << " Point2: ";
    p2.display(out);
    out << endl;
}

/**
 * description: Draws a line onto the screen using the SDL_Plotter object
 * return: void
 * precondition: the SDL_Plotter object is instantiated
 * postcondition: the line ending in the 2 points contained in this class is
 *  drawn to the screen in the color specified.
 */
void line::draw(SDL_Plotter& g){
    //if both points are the same, won't work
    // if((p1.getX() != p2.getX()) || (p1.getY() != p2.getY())){
        double dx=abs(p2.getX()-p1.getX()), dy=abs(p2.getY()-p1.getY()), largerChange;
        double x=p1.getX(), y=p1.getY();
        if(p2.getX() < x){
            x=p2.getX();
            y=p2.getY();
        }

        if(dx>=dy)
            largerChange=dx;
        else
            largerChange=dy;

        dx/=largerChange;
        dy/=largerChange;
        y += (dy*largerChange);
        x += (dx*largerChange);

        for(int i=1; i<=largerChange; ++i){
            g.plotPixel(x, g.getRow() - y, color.getR(), color.getG(), color.getB());
            x-=dx;
            y-=dy;
        }
    // } else {
    //     p1.setColor(this->color);
    //     p1.draw(g);
    // }
}

/**
 * description: sets the first point
 * return: void
 * precondition: line is initialized
 * postcondition: the first point has been set
 */
void line::setP1(point p){
    p1 = p;
}

/**
 * description: sets the second point
 * return: void
 * precondition: line is initialized
 * postcondition: the second point has been set
 */
void line::setP2(point p){
    p2 = p;
}

/**
 * description: changes the current color of the line.  This is so the same
 *  line can be used to draw multiple lines with just changing the coordinates.
 * return: void
 * precondition: line is initialized
 * postcondition: The color has been changed (red->green->blue->red)
 */
void line::nextColor(){
    currentColor = (currentColor+1) % 4;
    switch(currentColor){
        case 0: color = color_rgb(255, 0, 0); break;
        case 1: color = color_rgb(0, 255, 0); break;
        case 2: color = color_rgb(0, 0, 255); break;
        case 3: color = color_rgb(0,255,255); break;
    }
}

/**
 * description: resets the color cycle to the first color
 * return: void
 * precondition: line is initialized
 * postcondition: the color cycle has been reset.
 */
void line::resetColor(){
    currentColor = 0;
    color = color_rgb(255, 0, 0);
}

/**
 * description: returns if the line has a slope, and the slope in the variable
 *  if it does
 * return: bool -- whether or not the line has a slope
 * precondition: the line is initialized
 * postcondition: if it has a slope is returned and the slope is returned in m
 */
bool line::slope(double& m){
    bool hasSlope = true;
    if(p1.getX() == p2.getX()){
        hasSlope = false;
    } else {
        m = (p1.getY() - p2.getY())*1.0/(p1.getX() - p2.getX());
    }
    return hasSlope;
}

/**
 * description: if the line has an intercept is returned and if it does the
 *  intercept is returned in b
 * return: bool -- if it has an intercept
 * precondition: line is initialized
 * postcondition: if the line has an intercept is returned and if it does the
 *  intercept is returned in b
 */
bool line::intercept(double& b){
    double m;
    bool hasInter = true;

    if(slope(m)){
        b = (m*p1.getX()) - p1.getY();
    } else {
        hasInter = false;
    }
    return hasInter;
}
