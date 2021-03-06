/*
 * Author: Ethan Dickey
 * Assignment Title: Assignment 1
 * Assignment Description: This program draws a scalable graph.
 * Due Date: 1/28/2019
 * Date Created: 1/17/2019
 * Date Last Modified: 1/26/2019
 */
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "SDL_Plotter.h"
#include "color_rgb.h"

class point {
public:
	point();
	point(int x, int y);
	point(const point& p);
	virtual ~point();
	void setY(int y);
	void setX(int x);
	void setColor(color_rgb c);
	int getX();
	int getY();
	color_rgb getColor();
	point& operator=(const point& rhs);
    bool operator<(const point& rhs){
        if(x != rhs.x){
            return x < rhs.x;
        } else {
            return y < rhs.y;
        }
    }
	void display(ostream&);
	bool operator==(const point& other){
		if(this->x != other.x){
			return false;
		}
		else if(this->y != other.y){
			return false;
		}
		else{
			return true;
		}
	}
	void draw(SDL_Plotter&);
    /**draws a thicker box**/
    void drawThick(SDL_Plotter&, int thickness);

private:
	int x, y;
	color_rgb color;
};

#endif
