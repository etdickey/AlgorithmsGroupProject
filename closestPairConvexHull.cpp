#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>


#include "SDL_Plotter.h"
#include "point.h"
#include "line.h"
#include "color_rgb.h"
#include "curve.h"

using namespace std;

#define endl '\n'
const int ROW_MAX = 500;
const int COL_MAX = 500;

/**
 * Clears the screen.
 * @param g
 */
void clearScreen(SDL_Plotter& g){
    for(int x=0;x<COL_MAX;x++){
        for(int y=0;y<ROW_MAX;y++){
            g.plotPixel(x, y, 255, 255, 255);
        }
    }
}
/**
 * Draws the points passed in onto the screen
 *
 * @param points the points to be drawn
 * @param g      the plotter to plot onto
 */
void drawPoints(vector<point> points, SDL_Plotter& g){
    for(point p : points){
        if(0 <= p.getX() && p.getX() < COL_MAX && 0 <= p.getY() && p.getY() < ROW_MAX){
            p.draw(g);
        } else {
            cout << "ERROR: POINT OUT OF RANGE: ";
            p.display(cout);
            cout << endl;
        }
    }
}
/**
 * Draws the points passed in onto the screen thicker than normal, to promote visibility
 *
 * @param points the points to be drawn
 * @param g      the plotter to plot onto
 */
void drawThickerPoints(vector<point> points, SDL_Plotter& g, int thickness = 5){
    for(point p : points){
        if(0 <= p.getX() && p.getX() < COL_MAX && 0 <= p.getY() && p.getY() < ROW_MAX){
            p.drawThick(g, thickness);
        } else {
            cout << "ERROR: POINT OUT OF RANGE: ";
            p.display(cout);
            cout << endl;
        }
    }
}
/**
 * Draws the hull passed in
 * @param points the hull to draw
 * @param g      the plotter to plot onto
 */
void drawHull(vector<point> points, SDL_Plotter& g, color_rgb c = color_rgb(0,0,0)){
    line temp;

    for(int i=0;i<points.size();i++){
        temp.setColor(c);

        temp.setP1(points[i]);
        if(i == points.size()-1){
            temp.setP2(points[0]);
        } else {
            temp.setP2(points[i+1]);
        }
        temp.draw(g);
    }
}
/**
 * Draws the hull passed in
 * @param lines  the hull to draw
 * @param g      the plotter to plot onto
 */
void drawHullLines(vector<line> lines, SDL_Plotter& g){
    for(auto i : lines){
        i.draw(g);
    }
}

/**
 * Returns the direction of the point c according to the line between a and b
 *
 * @param endpointA the first point of the line being tested
 * @param endpointB the second point of the line being tested
 * @param testPoint the point being tested to see what side of the line
 *          it is on
 * @return -1 if on the left, 1 if on the right, 0 if on the line
 */
int direction(point a, point b, point c){
    if(a == b){
        return 0;
    }
    int result = (b.getY()-a.getY())*(c.getX()-b.getX()) -
                 (c.getY()-b.getY())*(b.getX()-a.getX());
    if(result == 0){
        return 0;
    }
    if(result > 0){
        return 1;
    }
    return -1;
}

//////////////////////////////////////////////////////////////////////////////// CP-BF
/**
 * Solves the CLosest Pair problem with the brute force solution
 *
 * @author Em Lakin
 *
 * @param points the points to solve the problem
 * @return the closest pair of points
 */
pair<point, point> brute_forceClosestPair(vector<point> points, SDL_Plotter& g){
    pair<point, point> closestPair;// = make_pair(point(0,0), point(0,0));
    line testingLine;
    line closestLine;
    color_rgb c1(200,20,20);
    color_rgb c2(20,200,20);
    color_rgb c3(20,20,200);
    color_rgb white(255,255,255);
    line whiteLine;
    whiteLine.setColor(white);
    testingLine.setColor(c2);
    closestLine.setColor(c1);
    // cout << "Runing brute force closest pair" << endl;
    for(point p : points){
        p.display(cout);
        p.setColor(c3);
        p.drawThick(g, 5);

        cout << endl;
    }
    for(int i = 0; i < points.size(); i++){
        points[i].drawThick(g, 5);
    }
    //g.update();

    //distance = sqrt(pow((two.getX() - one.getX()),2) + pow((two.getY() - one.getY()),2))

    cout << "There are: " << points.size() << " points" << endl;
    if(points.size() == 0){
        //yikes, can this happen:
        closestPair = make_pair(point(0,0), point(0,0));
    }
    else if(points.size() == 1){
        closestPair = make_pair(points[0], points[0]);
    }
    else if(points.size() == 2){
        closestPair = make_pair(points[0], points[1]);
    }
    else{
        //point one = points[0], two = points[1];
        double minDist = sqrt(pow((points[1].getX() - points[0].getX()),2) + pow((points[1].getY() - points[0].getY()),2));
        for(int i = 0; i < points.size(); i++){
            for(int j = i+1; j < points.size(); j++){
                points[i].setColor(c3);
                points[j].setColor(c3);
                double newDist = sqrt(pow((points[j].getX() - points[i].getX()),2)
                + pow((points[j].getY() - points[i].getY()),2));
                closestLine.draw(g);
                if(!(testingLine == closestLine)){

                    whiteLine.setP1(testingLine.getP1());
                    whiteLine.setP2(testingLine.getP2());

                    whiteLine.draw(g);
                    whiteLine.getP1().drawThick(g,5);
                    whiteLine.getP2().drawThick(g,5);
                    g.update();
                }
                testingLine.setP1(points[i]);
                testingLine.setP2(points[j]);

                testingLine.draw(g);
                testingLine.display(cout);
                cout << endl;
                g.update();
                g.Sleep(1000);
                if(newDist < minDist){
                    if(!(points[i] == points[j])){
                        closestLine.draw(g);
                        g.Sleep(1000);
                        minDist = newDist;
                        closestPair = make_pair(points[i], points[j]);
                        whiteLine.setP1(closestLine.getP1());
                        whiteLine.setP2(closestLine.getP2());
                        whiteLine.draw(g);
                        whiteLine.getP2().drawThick(g,5);
                        whiteLine.getP1().drawThick(g,5);
                        // /cout << "CLOSE WHITE LINE DRAWN" << endl;
                        //g.update();
                    //    g.Sleep(1000);

                        closestLine.setP1(closestPair.first);
                        closestLine.getP1().drawThick(g,5);
                        closestLine.setP2(closestPair.second);
                        closestLine.getP2().drawThick(g,5);
                        cout << "Drawing closest pair line: " ;
                        closestLine.getP1().display(cout);
                        closestLine.getP2().display(cout);
                        closestLine.setColor(c1);
                        closestLine.draw(g);
                        g.update();

                    }

                }

            }
        }
    }

    cout << "Closest Pair: " ;
    closestPair.first.display(cout);
    cout << " x " ;
    closestPair.second.display(cout);
    cout << endl;
    return closestPair;
}



//////////////////////////////////////////////////////////////////////////////// CP-DC
/**
 * Solves the Closest Pair problem with a Divide and Conquer strategy
 *
 * @author Josh Holland
 *
 * @param points the set of points to solve the problem for
 * @return the closest pair of points
 */
 double distanceTo(point &thisone, point& other){
     return sqrt((thisone.getX()-other.getX())*(thisone.getX()-other.getX())+(thisone.getY()-other.getY())*(thisone.getY()-other.getY()));
 }

 bool sort_by_x(point& a, point& b){
     return a.getX() < b.getX();
 }

 bool sort_by_y(point& a, point& b){
     return a.getY() < b.getY();
 }


 pair<point,point> divideAndConquerClosestPair_recurse(vector<point> points, int left, int right){
     //right is 1 more than the index that it stops at
     int size = right-left;
     if(size == 2){
         return make_pair(points[left],points[left+1]);
     }
     point middle = points[left+size/2];

     //subarray 1: left,left+size/2
     //subarray 2: left+size/2+1,right

     pair<point,point> result;

     result = divideAndConquerClosestPair_recurse(points,left,left+size/2+1);
     double minLeft = distanceTo(result.first,result.second);
     double min_d = minLeft;

     if(right-(left+size/2+1) > 1){
         pair<point,point> rightone = divideAndConquerClosestPair_recurse(points,left+size/2+1,right);
         double minRight= distanceTo(rightone.first,rightone.second);

         if(minRight < min_d){
             min_d = minRight;
             result = rightone;
         }
     }

     int middle_index = left+size/2;

     double vertical_line_x = points[middle_index].getX() + (points[middle_index+1].getX()-points[middle_index].getX())/2;
     // = points[left].getX() + (points[right-1].getX()-points[left].getX())/2;

     vector<point> closer_to_line;
     for(point point: points) {
         if(abs(point.getX()-vertical_line_x) < min_d) {
             closer_to_line.push_back(point);
         }
     }

     if(closer_to_line.size() < 2){
         return result;
     }
     //sort by y:
     sort(closer_to_line.begin(),closer_to_line.end(),sort_by_y);
     double min_middle = distanceTo(closer_to_line[1],closer_to_line[0]);
     pair<point,point> min_middle_set = make_pair(closer_to_line[1],closer_to_line[0]);

     for(int i = 0; i < closer_to_line.size(); i++){
         for(int j = i+1; j < closer_to_line.size(); j++){
             if(distanceTo(closer_to_line[i],closer_to_line[j]) < min_middle){
                 min_middle = distanceTo(closer_to_line[i],closer_to_line[j]);
                 min_middle_set = make_pair(closer_to_line[i],closer_to_line[j]);
             }
         }
     }

     if(min_middle < min_d){
         min_d = min_middle;
         result = min_middle_set;
     }

     return result;

 }


 pair<point, point> divideAndConquerClosestPair(SDL_Plotter& g,vector<point> points){
     pair<point, point> closestPair;
     cout << "Runing divide and conquer closest pair" << endl;
     closestPair = divideAndConquerClosestPair_recurse(points,0,points.size());
     for(point p : points){
         p.display(cout);
         cout << endl;
     }
     closestPair.first.setColor(color_rgb(255, 0, 0));
     closestPair.second.setColor(color_rgb(255, 0, 0));

     closestPair.first.drawThick(g,5);
     closestPair.second.drawThick(g,5);
     return closestPair;
 }

/**
 * Solves the Closest Pair problem with a Divide and Conquer strategy (with animation)
 *
 * @param points the set of points to solve the problem for
 * @return the closest pair of points
 */
// pair<point, point> divideAndConquerClosestPair(vector<point> points, SDL_Plotter& g){
//     pair<point, point> closestPair = make_pair(point(0,0), point(0,0));
//
//     return closestPair;
// }

//////////////////////////////////////////////////////////////////////////////// CH-BF
/**
 * Solves the Convex Hull problem with the brute force solution
 *
 * @author Mackenna Semeyn
 *
 * @param  points the set of points to solve the problem for.
 * @return        the convex hull surrounding all the points
 */
vector<point> brute_forceConvexHull(vector<point> points, SDL_Plotter& g){
    vector<line> convexHullLines;
    vector<point> convexHull;
    point final;
    line toAdd;

    cout << "\nRunning brute force convex hull on " << points.size() << " points" << endl;
    for(point p : points){
        p.display(cout);
    }
    cout << endl;

    for(int i=0; i < points.size(); i++){
        for(int j=0; j < points.size(); j++){
            if(i == j){
                continue;   // go to next pair of points
            }

            point pI = points[i];
            point pJ = points[j];

            bool rightSideOfTheLine = true, firstTime = true;
            int sideOfLine;
            for(int k=0; k < points.size(); k++){//see if all the other points are on the other side of the line
                if(k == i || k == j){
                    continue;
                }

                int position = direction(pI, pJ, points[k]);
                if(firstTime){
                    sideOfLine = position;
                    firstTime = false;
                } else if(!(position == 0 || sideOfLine == position)){//if it's not on the line or on the same side of the line as before, stop
                    rightSideOfTheLine = false;
                    break;
                }
                // if(position < 0){//this needs to be just if they are all on one side of the line, not necessarily on the right side
                //     rightSideOfTheLine = false;
                //     break;
                // }
            }

            if(rightSideOfTheLine){
                toAdd.setP1(pI);
                toAdd.setP2(pJ);
                if(find(convexHullLines.begin(), convexHullLines.end(), toAdd) == convexHullLines.end()){
                    toAdd.setP1(pJ);
                    toAdd.setP2(pI);
                    if(find(convexHullLines.begin(), convexHullLines.end(), toAdd) == convexHullLines.end()){
                        convexHullLines.push_back(toAdd);
                    }
                }
                // if(find(convexHull.begin(), convexHull.end(), pI) != convexHull.end()){
                //     convexHull.push_back(pI);
                //     final = pJ;
                // }
            }
        }
    }

    // convexHull.push_back(final); // add last point to hull

    // cout << "Convex hull: " << endl;
    // for(auto p : convexHullLines){
    //     p.display(cout);
    // }
    drawHullLines(convexHullLines, g);

    //return them in cyclic order
    convexHull.clear();
    point prevPoint = convexHullLines.front().getP2();
    point curr;
    vector<line> tempHull(convexHullLines);

    while(tempHull.size() > 0){//repeat until all lines are accounted for
        //start with the second point of the last line
        curr = prevPoint;
        //find the other line with that point and add the other point in that
        for(int i=0;i<tempHull.size();i++){
            if(tempHull[i].getP1() == curr){
                //add the other to the set
                convexHull.push_back(tempHull[i].getP2());
                prevPoint = tempHull[i].getP2();
                tempHull.erase(tempHull.begin() + i);
                break;
            } else if(tempHull[i].getP2() == curr){
                //add the other to the set and remove it from the remaining ones
                convexHull.push_back(tempHull[i].getP1());
                prevPoint = tempHull[i].getP1();
                tempHull.erase(tempHull.begin() + i);
                break;
            }
        }
    }
    if(convexHull.size() > 2 && direction(convexHull[0], convexHull[1], convexHull[2]) >= 0){//if it's a right turn
        //reverse it
        reverse(convexHull.begin(), convexHull.end());
    }

    cout << "Convex hull: " << endl;
    for(auto i : convexHull){
        i.display(cout);
    }
    cout << endl << endl;

    return convexHull;
}

/**
 * Solves the Convex Hull problem with the brute force solution (with animation)
 *
 * @param  points the set of points to solve the problem for.
 * @return        the convex hull surrounding all the points
 */
// vector<point> brute_forceConvexHull(vector<point> points, SDL_Plotter& g){
//     vector<point> convexHull;
//
//     return convexHull;
// }

//////////////////////////////////////////////////////////////////////////////// CH-DC
vector<point> mergeConvexHullDC(vector<point> leftHull, vector<point> rightHull, SDL_Plotter& g){
    //define helper variables
    int n1 = leftHull.size(), n2 = rightHull.size();
    int rightmostLeft = 0,//*max_element(leftHull.begin(), leftHull.end(), [](point& p1, point& p2) {return p1.getX() < p2.getX();}),
        leftmostRight = 0;//*min_element(rightHull.begin(), rightHull.end(), [](point& p1, point& p2) {return p1.getX() < p2.getX();});

    //find the right most of the left hull
    for(int i=0;i<leftHull.size();i++){
        if(leftHull[i].getX() > leftHull[rightmostLeft].getX()){
            rightmostLeft = i;
        }
    }
    //find the left most of the right hull
    for(int i=0;i<rightHull.size();i++){
        if(rightHull[i].getX() < rightHull[leftmostRight].getX()){
            leftmostRight = i;
        }
    }

    //push the beams up to the top -- move right most on left upwards and see if it makes a left turn
    int upTanLeft = rightmostLeft, upTanRight = leftmostRight;
    bool done = false;
    while (!done) {// finding the upper tangent
        done = true;
        //move along the circle in ccw direction
        while (direction(rightHull[upTanRight], leftHull[upTanLeft], leftHull[(upTanLeft+1)%n1]) >=0) {
            upTanLeft = (upTanLeft + 1) % n1;
        }
        //move along the right convex hull in cw direction
        while (direction(leftHull[upTanLeft], rightHull[upTanRight], rightHull[(n2+upTanRight-1)%n2]) <=0) {
            upTanRight = (n2+upTanRight-1)%n2;
            done = false;
        }
    }
    // cout << "Upper tangent: ";
    // leftHull[upTanLeft].display(cout);
    // cout << " and ";
    // rightHull[upTanRight].display(cout);
    // cout << endl;
    line temp(leftHull[upTanLeft], rightHull[upTanRight]);
    temp.setColor(color_rgb(255,255,0));
    temp.draw(g);


    //push beam to the bottom -- right most on left down and see if it makes a right turn
    int lowTanLeft = rightmostLeft, lowTanRight = leftmostRight;
    done = false;
    while (!done) {//finding the lower tangent
        done = true;
        //move right hull down in ccw direction
        while (direction(leftHull[lowTanLeft], rightHull[lowTanRight], rightHull[(lowTanRight+1)%n2]) >= 0) {
            lowTanRight = (lowTanRight+1)%n2;
        }
        //move left hull down in cw direction
        while (direction(rightHull[lowTanRight], leftHull[lowTanLeft], leftHull[(n1+lowTanLeft-1)%n1]) <= 0) {
            lowTanLeft = (n1+lowTanLeft-1)%n1;
            done = false;
        }
    }
    // cout << "Lower tangent: ";
    // leftHull[lowTanLeft].display(cout);
    // cout << " and ";
    // rightHull[lowTanRight].display(cout);
    // cout << endl;
    temp = line(leftHull[lowTanLeft], rightHull[lowTanRight]);
    temp.setColor(color_rgb(255,255,0));
    temp.draw(g);


    //go from bottom index
    vector<point> merged;
    //start from upper left tangent, ccw around the left to the lower left tangent
    for(int i=upTanLeft; i != lowTanLeft; i = (i+1)%n1){
        merged.push_back(leftHull[i]);
    }
    merged.push_back(leftHull[lowTanLeft]);//add the last one

    //then go from lower right tangent ccw up to the upper right tangent
    for(int i=lowTanRight; i!= upTanRight; i = (i+1)%n2){
        merged.push_back(rightHull[i]);
    }
    merged.push_back(rightHull[upTanRight]);

    return merged;
}

/**
 * Executes the recursion aspect of the convex hull divide and conquer solution
 *
 * ASSUMES DATA IS SORTED BY X VALUE
 *
 * @param  points the points to solve
 * @return        the convex hull of the points
 */
vector<point> convexHullRecurse(vector<point> points, SDL_Plotter& g){
    //it is much easier and virtually the same efficiency to brute force when the hull is 5 or less points
    if(points.size() < 6){
        if(points.size() <= 3){
            if(points.size() > 2 && direction(points[0], points[1], points[2]) >= 0){//if it's a right turn
                //reverse it
                reverse(points.begin(), points.end());
            }
            return points;
        }

        // cout << "Running brute force with " << points.size() << " points" << endl;
        return brute_forceConvexHull(points, g);
    } else {
        vector<point> left, right;
        //split the problem
        for(int i=0;i<points.size()/2;i++){
            left.push_back(points[i]);
        }
        for(int i=points.size()/2;i<points.size();i++){
            right.push_back(points[i]);
        }

        //recurse
        vector<point> leftHull = convexHullRecurse(left, g),
                      rightHull = convexHullRecurse(right, g);
        // cout << "Left hull: ";
        // for(point p : leftHull){ p.display(cout); cout << " "; }
        // cout << endl;
        // cout << "Right hull: ";
        // for(point p : rightHull){ p.display(cout); cout << " "; }
        // cout << endl;
        // cout << "Drawing left hull (red, " << leftHull.size() << ") and right hull (green " << rightHull.size() << ")" << endl;
        clearScreen(g);
        drawThickerPoints(points, g);
        drawHull(leftHull, g, color_rgb(255, 0, 0));
        drawHull(rightHull, g, color_rgb(0, 255, 0));
        g.update();
        //merge
        vector<point> temp = mergeConvexHullDC(leftHull, rightHull, g);
        // cout << "Drawing merged (blue) " << endl;
        drawHull(temp, g, color_rgb(0,0,255));
        g.update();
        // if(temp.size() == 1){
            // g.Sleep(200000);
        // }
        return temp;
    }
}

/**
 * Solves the Convex Hull problem with the divide and conquer solution (with animation if selected)
 *
 * @author Ethan Dickey
 *
 * @param  points the set of points to solve the problem for.
 * @return        the convex hull surrounding all the points
 */
vector<point> divideAndConquerConvexHull(vector<point> points, SDL_Plotter& g, bool runAnimation = true){
    cout << "Runing divide and conquer convex hull" << endl;
    vector<point> convexHull;
    sort(points.begin(), points.end());
    for(point p : points){
        p.display(cout);
        cout << endl;
    }

    // cout << "Drawing points" << endl;
    drawThickerPoints(points, g);

    convexHull = convexHullRecurse(points, g);
    drawHull(convexHull, g, color_rgb(0, 0, 255));

    return convexHull;
}

/**
 * Solves the Convex Hull problem with the divide and conquer solution (with animation)
 *
 * @param  points the set of points to solve the problem for.
 * @return        the convex hull surrounding all the points
 */
// vector<point> divideAndConquerConvexHull(vector<point> points, SDL_Plotter& g){
//     vector<point> convexHull;
//
//     return convexHull;
// }

int main(int argc, char** argv){
    cout << "Hello amazin world" << endl;
    //define variables
    SDL_Plotter g(ROW_MAX,COL_MAX);

    vector<point> points;
    ifstream in("input1.in");
    int x, y;

    //import data (multiple data sets?)
    while(in >> x >> y){
        points.push_back(point(x, y));
        //TODO::     //sic em green
            // R = 29;
            // G = 60;
            // B = 52;
    }

    //run brute force with animation and time for fun
    if(argc == 3){
        string algo(argv[1]);
        string option(argv[2]);

        if(algo != "-convex" && algo != "-closest"){
            cout << "Invalid first argument: [-convex, -closest] expected" << endl;
            return 1;
        }
        if(option != "-divide" && option != "-brute"){
            cout << "Invalid first argument: [-brute -divide] expected" << endl;
            return 1;
        }

        bool rerunAlgorithm = true, update = true;
        bool colored = false;
        int x,y, xd, yd;
        int R,G,B;

        while (!g.getQuit())
        {
    		if(rerunAlgorithm){
                //todo: run the selected algorithm and animate it
        		// x = rand()%g.getCol();
    			// y = rand()%g.getRow();
    			// R = rand()%256;
    			// G = rand()%256;
    			// B = rand()%256;
    			// for(xd = 0; xd < 10 && x + xd < g.getCol(); xd++ ){
    			// 	for(yd = 0; yd < 10 && y + yd < g.getRow(); yd++ ){
    			// 		if(colored){
    			// 			g.plotPixel( x + xd, y + yd, R, G, B);
    			// 		}
    			// 		else{
    			// 		    g.plotPixel( x + xd, y + yd, 0, G, 0);
    			// 		}
                //
    			// 	}
    			// }

                if(algo == "-convex"){
                    if(option == "-brute"){
                        //call brute force convex hull, it does all the work
                        drawThickerPoints(points, g);
                        brute_forceConvexHull(points, g);
                        // drawHull(brute_forceConvexHull(points, g), g);
                    } else if(option == "-divide"){
                        divideAndConquerConvexHull(points, g);
                    }
                } else if(algo == "-closest"){
                    if(option == "-brute"){
                        pair<point, point> closestPair = brute_forceClosestPair(points,g);

                        //TODO:: circle them on the plot

                    } else if(option == "-divide"){
                        drawThickerPoints(points, g);
                        pair<point, point> closestPair = divideAndConquerClosestPair(g,points);

                        //TODO:: circle them on the plot

                    }
                }

                rerunAlgorithm = false;
                g.update();
    		}

    		if(g.kbhit()){
    			g.getKey();
    		}

    		if(g.getMouseClick(x,y)){
                //get the point clicked, make a new point with it,
                // add it to the list of points and then rerun the selected algorithm
                points.push_back(point(x, COL_MAX-y));
    			rerunAlgorithm = true;
                clearScreen(g);
                g.update();
    		}
        }
    } else {
        cout << "ERROR: Number of arguments must be 2: [-convex, -closest] [-brute -divide]" << endl;
        return 1;
    }



    return 0;
}
