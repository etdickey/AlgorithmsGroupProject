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
const int ROW_MAX = 1000;
const int COL_MAX = 1000;

/**
 * Draws the points passed in onto the screen
 *
 * @param points the points to be drawn
 * @param g      the plotter to plot onto
 */
void drawPoints(vector<point> points, SDL_Plotter& g){
    for(point p : points){
        p.draw(g);
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
        p.drawThick(g, thickness);
    }
}

/**
 * Computes the orientation of a pair triplet: collinear, clockwise, or counterclockwise
 *
 * @param p point one in the triplet
 * @param q point two in the triplet
 * @param r point three in the triplet
 * @return 0 is collinear, 1 for clockwise, 2 for counterclockwise
 */
int orientation(point p, point q, point r){
    int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
              (q.getX() - p.getX()) * (r.getY() - q.getY());

    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1: 2; // clockwise or counterclockwise
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
    // cout << "Runing brute force closest pair" << endl;
    for(point p : points){
        p.display(cout);
        color_rgb c(256,0,99);
        p.setColor(c);
        p.draw(g);

        cout << endl;
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
                double newDist = sqrt(pow((points[j].getX() - points[i].getX()),2)
                + pow((points[j].getY() - points[i].getY()),2));
                if(newDist < minDist){
                    //TODO: Need to compare points to make sure they are not the same point
                    minDist = newDist;
                    closestPair = make_pair(points[i], points[j]);

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
pair<point, point> divideAndConquerClosestPair(vector<point> points){
    pair<point, point> closestPair = make_pair(point(0,0), point(0,0));
    cout << "Runing divide and conquer closest pair" << endl;
    for(point p : points){
        p.display(cout);
        cout << endl;
    }
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
vector<point> brute_forceConvexHull(vector<point> points){
    vector<point> convexHull;
    cout << "Running brute force convex hull" << endl;
    for(point p : points){
        p.display(cout);
        cout << endl;
    }

    int n = points.size();

    // find leftmost point
    int left = 0;
    for(int i=1; i < n; i++){
        if(points[i].getX() < points[left].getX()){
            left = i;
        }
    }

    int p = left;
    int q;

    do{

        convexHull.push_back(points[p]);

        q = (p + 1)%n;
        for(int i=0; i < n; i++){
            if(orientation(points[p], points[i], points[q]) == 2){
                q = i;
            }
        }

        p = q;
    }while(p != left);

    return convexHull;
}

/**
 * Solves the Convex Hull problem with the brute force solution (with animatino)
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
    // for(point p : points){
    //     p.display(cout);
    //     cout << endl;
    // }

    cout << "Drawing points" << endl;
    drawThickerPoints(points, g);

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

        bool rerunAlgorithm = true;
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
                        brute_forceConvexHull(points);
                    } else if(option == "-divide"){
                        divideAndConquerConvexHull(points, g);
                    }
                } else if(algo == "-closest"){
                    if(option == "-brute"){
                        pair<point, point> closestPair = brute_forceClosestPair(points,g);

                        //TODO:: circle them on the plot

                    } else if(option == "-divide"){
                        pair<point, point> closestPair = divideAndConquerClosestPair(points);

                        //TODO:: circle them on the plot

                    }
                }

                rerunAlgorithm = false;
    		}

    		if(g.kbhit()){
    			g.getKey();
    		}

    		if(g.getMouseClick(x,y)){
                //get the point clicked, make a new point with it,
                // add it to the list of points and then rerun the selected algorithm
                points.push_back(point(x, COL_MAX-y));
    			rerunAlgorithm = true;
    		}

    		g.update();
        }
    } else {
        cout << "ERROR: Number of arguments must be 2: [-convex, -closest] [-brute -divide]" << endl;
        return 1;
    }



    return 0;
}
