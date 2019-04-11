/*
 * Author: Ethan Dickey
 * Assignment Title: Assignment 1
 * Assignment Description: This program draws a scalable graph.
 * Due Date: 1/28/2019
 * Date Created: 1/17/2019
 * Date Last Modified: 1/26/2019
 */

#include "curve.h"
#include <algorithm>

/**
 * description: curve constructor
 * return: none
 * precondition: none
 * postcondition: the curve class is initialized with false for same scale
 */
curve::curve(): sameScale(false){}

/**
 * description: curve class destructor
 * return: none
 * precondition: curve is initialized
 * postcondition: curve has been destructed
 */
curve::~curve(){}

/**
 * description: displays the curve of data points to the passed in
 *  output stream
 * return: void
 * precondition: the data is initialized
 * postcondition: all of the points have been displayed to the output stream
 */
void curve::display(Data_t data, ostream& out){
    int a=0;
    for(auto i : data){
        out << "Data set " << a << endl;
        for(auto j : i){
            out << j.first << " " << j.second << endl;
        }
        out << endl;
        ++a;
    }
}

/**
 * description: draws the curves to the passed in SDL_Plotter class with
 *  different colors for each line and if same scale is set, all scaled to the
 *  screen individually.
 * return: void
 * precondition: the point class is initialized and the data is valid
 * postcondition: the curves have been drawn (scaled or not) in different colors
 */
void curve::draw(Data_t data, SDL_Plotter& g){
    //need to plot axis -- need to go through all data and find maxX and maxY
    int margin = 50, MAX_ROW = g.getRow(), MAX_COL = g.getCol();
    int maxX[data.size()], maxY[data.size()];
    line a;
    point p1, p2;

    // define max elements as smallest possible in the data set
    for(int i=0;i<data.size();++i){
        maxX[i] = maxY[i] = 0;
    }

    // define the max elements for each set
    for(int i=0;i<data.size();++i){
        for(auto j : data[i]){
            if(maxX[i] < j.first){//&& j.second < MAX_ROW-margin*2 && j.first < MAX_COL-margin*2
                maxX[i] = j.first;
            }
            if(maxY[i] < j.second){// && j.second < MAX_ROW-margin*2 && j.first < MAX_COL-margin*2
                maxY[i] = j.second;
            }
        }
    }
    plotAxis(margin, maxX[0], maxY[0], g);//the maxX and maxY don't matter because they aren't actually used

    double xScale[data.size()], yScale[data.size()];
    for(int i=0;i<data.size();++i){
        xScale[i] = yScale[i] = 1.0;
    }

    double mX = *max_element(maxX, maxX+data.size()), mY = *max_element(maxY, maxY+data.size());
    for(int i=0;i<data.size();++i){
        if(sameScale){
            xScale[i] *= (MAX_COL-margin*2)/(1.0*maxX[i]);
            yScale[i] *= (MAX_ROW-margin*2)/(1.0*maxY[i]);
        } else {
            xScale[i] *= (MAX_COL-margin*2)/(1.0*mX);
            yScale[i] *= (MAX_ROW-margin*2)/(1.0*mY);
        }
    }

    for(int i=0;i<data.size();++i){
        for(int j=0;j<data[i].size()-1;++j){
            p1.setX(data[i][j].first * xScale[i] + margin);
            p1.setY(data[i][j].second * yScale[i] + margin);

            p2.setX(data[i][j+1].first * xScale[i] + margin);
            p2.setY(data[i][j+1].second * yScale[i] + margin);

            a.setP1(p1);
            a.setP2(p2);
            //draw the lines
            //assumes that a is already scaled
            if(goodPoints(a, margin, g)){
                a.draw(g);
            }

        }
        a.nextColor();
        // g.update();
        // system("pause");
    }
}

/**
 * description: draws the axis to the screen
 * return: void
 * precondition: the curve class is initialized
 * postcondition: the axis have been drawn to the screen
 */
void curve::plotAxis(int margin, int maxX, int maxY, SDL_Plotter& g){
    //axis go from
    line temp;
    temp.setP1(point(margin, margin));
    temp.setP2(point(g.getCol()-margin, margin));
    temp.draw(g);

    temp.setP1(point(margin, margin));
    temp.setP2(point(margin, g.getRow()-margin));
    temp.draw(g);

    plotTickMarks(margin, maxX, maxY, g);
}

/**
 * description: draws the tick marks on the axis to the screen
 * return: void
 * precondition: the curve class is initialized
 * postcondition: the tick marks have been drawn to the screen
 */
void curve::plotTickMarks(int margin, int maxX, int maxY, SDL_Plotter& g){
    const int SCALE = 100;
    int numTicks = 10;
    int deltaX = (g.getCol() - 2*margin)*1.0/numTicks, deltaY = (g.getRow() - 2*margin)*1.0/numTicks;
    line temp;

    int x=0, y=0;
    while(x+2*margin <= g.getCol()){
        temp.setP1(point(x + margin, margin - 5));
        temp.setP2(point(x + margin, margin + 5));
        temp.draw(g);
        x += deltaX;
    }

    while(y+2*margin <= g.getRow()){
        temp.setP1(point(margin-5, margin + y));
        temp.setP2(point(margin+5, margin + y));
        temp.draw(g);
        y += deltaY;
    }
}

/**
 * description: checks whether a point is within the bounds of the screen
 * return: bool -- if it's inside the screen
 * precondition: the SDL_Plotter class is initialized
 * postcondition: whether or not the point can be drawn to the screen is returned
 */
bool curve::goodPoints(line a, int margin, SDL_Plotter& g){
    bool goodP = true;
    if((a.getP1().getX() < 0) || (a.getP1().getX() > (g.getCol() - margin))
     ||(a.getP1().getY() < 0) || (a.getP1().getY() > (g.getRow() - margin))
     ||(a.getP2().getX() < 0) || (a.getP2().getX() > (g.getCol() - margin))
     ||(a.getP2().getY() < 0) || (a.getP2().getY() > (g.getRow() - margin))){
        goodP = false;
    }
    return goodP;
}
