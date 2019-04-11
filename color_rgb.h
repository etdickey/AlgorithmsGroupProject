/*
 * Author: Ethan Dickey
 * Assignment Title: Assignment 1
 * Assignment Description: This program draws a scalable graph.
 * Due Date: 1/28/2019
 * Date Created: 1/17/2019
 * Date Last Modified: 1/26/2019
 */
#ifndef COLOR_RGB_H
#define COLOR_RGB_H

class color_rgb {
public:
	color_rgb();
	color_rgb(int r, int g, int b);
	virtual ~color_rgb();
	int getR();
	int getG();
	int getB();

	void setR(int r);
	void setG(int g);
	void setB(int b);

	void operator=(const color_rgb& c);

private:
	int r,g,b;
};

#endif
