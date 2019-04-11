/*
 * Author: Ethan Dickey
 * Assignment Title: Assignment 1
 * Assignment Description: This program draws a scalable graph.
 * Due Date: 1/28/2019
 * Date Created: 1/17/2019
 * Date Last Modified: 1/26/2019
 */
#ifndef LINE_H
#define LINE_H
#include "point.h"

class line {
public:
	line();
	line(point p1, point p2);
	virtual ~line();

	void display(ostream&  out);
	void draw(SDL_Plotter& g);

	void setP1(point p);
	void setP2(point p);
	void setColor(color_rgb c){color = c;}

	point getP1(){return p1;}
	point getP2(){return p2;}
	color_rgb getColor(){return color;}

	void nextColor();
	void resetColor();

private:
	point p1, p2;
	color_rgb color;
	bool slope(double& m);
	bool intercept(double& b);
	int currentColor;
};

#endif
