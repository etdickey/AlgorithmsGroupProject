/*
 * Author: Ethan Dickey
 * Assignment Title: Assignment 1
 * Assignment Description: This program draws a scalable graph.
 * Due Date: 1/28/2019
 * Date Created: 1/17/2019
 * Date Last Modified: 1/26/2019
 */
#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include "line.h"

typedef vector<pair<int,long double>> DataSet_t;
typedef vector<DataSet_t> Data_t;

class curve {
public:
	curve();
	virtual ~curve();
	void display(Data_t data, ostream&);
	void draw(Data_t data, SDL_Plotter&);
	bool getSameScale(){ return sameScale;}
	void setSameScale(bool t){sameScale = t;}

private:
	void plotAxis(int margin, int maxX, int maxY, SDL_Plotter& g);
	void plotTickMarks(int margin, int maxX, int maxY, SDL_Plotter& g);
	bool goodPoints(line a, int margin, SDL_Plotter& g);
	bool sameScale;

};

#endif
