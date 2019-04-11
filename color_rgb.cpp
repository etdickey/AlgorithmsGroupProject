/*
 * Author: Ethan Dickey
 * Assignment Title: Assignment 1
 * Assignment Description: This program draws a scalable graph.
 * Due Date: 1/28/2019
 * Date Created: 1/17/2019
 * Date Last Modified: 1/26/2019
 */

#include "color_rgb.h"

/**
 * description: color_rgb constructor
 * return: none
 * precondition: none
 * postcondition: the color_rgb class is initialized with black for the color
 */
color_rgb::color_rgb(){ r = g = b = 0;}

/**
 * description: color_rgb constructor
 * return: none
 * precondition: none
 * postcondition: the color_rgb class is initialized with the passed in colors
 */
color_rgb::color_rgb(int red, int green, int blue): r(red), g(green), b(blue){}

/**
 * description: color_rgb class destructor
 * return: none
 * precondition: color_rgb is initialized
 * postcondition: color_rgb has been destructed
 */
color_rgb::~color_rgb(){}

/**
 * description: returns the red value
 * return: int -- red value
 * precondition: color_rgb is initialized
 * postcondition: red value has been returned
 */
int color_rgb::getR(){ return r;}

/**
 * description: returns the green value
 * return: int -- green value
 * precondition: color_rgb is initialized
 * postcondition: green value has been returned
 */
int color_rgb::getG(){ return g;}

/**
 * description: returns the blue value
 * return: int -- blue value
 * precondition: color_rgb is initialized
 * postcondition: blue value has been returned
 */
int color_rgb::getB(){ return b;}

/**
 * description: sets the red value
 * return: void
 * precondition: color_rgb is initialized
 * postcondition: red value has been set
 */
void color_rgb::setR(int r){ this->r = r;}

/**
 * description: sets the green value
 * return: void
 * precondition: color_rgb is initialized
 * postcondition: green value has been set
 */
void color_rgb::setG(int g){ this->g = g;}

/**
 * description: sets the blue value
 * return: void
 * precondition: color_rgb is initialized
 * postcondition: blue value has been set
 */
void color_rgb::setB(int b){ this->b = b;}

/**
 * description: copy assignment operator
 * return: void
 * precondition: the passed in color_rgb is initialized
 * postcondition: this instance of the class is equivalent to the passed in
 *  class
 */
void color_rgb::operator=(const color_rgb& c){
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;
}
