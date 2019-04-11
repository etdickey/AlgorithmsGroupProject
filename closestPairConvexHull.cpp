#include <iostream>
#include <fstream>
#include <vector>

#include "SDL_Plotter.h"
#include "point.h"
#include "line.h"
#include "color_rgb.h"
#include "curve.h"

using namespace std;

#define endl '\n'
const int ROW_MAX = 500;
const int COL_MAX = 1000;

/**
 * Solves the CLosest Pair problem with the brute force solution
 *
 * @param points the points to solve the problem
 * @return the closest pair of points
 */
pair<point, point> brute_forceClosestPair(vector<point> points){
    pair<point, point> closestPair = make_pair(point(0,0), point(0,0));

    return closestPair;
}

/**
 * Solves the CLosest Pair problem with the brute force solution (and animates it)
 *
 * @param points the points to solve the problem
 * @return the closest pair of points
 */
// pair<point, point> brute_forceClosestPair(vector<point> points, SDL_Plotter& g){
//     pair<point, point> closestPair = make_pair(point(0,0), point(0,0));
//
//     return closestPair;
// }

/**
 * Solves the Closest Pair problem with a Divide and Conquer strategy
 *
 * @param points the set of points to solve the problem for
 * @return the closest pair of points
 */
pair<point, point> divideAndConquerClosestPair(vector<point> points){
    pair<point, point> closestPair = make_pair(point(0,0), point(0,0));

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

/**
 * Solves the Convex Hull problem with the brute force solution
 *
 * @param  points the set of points to solve the problem for.
 * @return        the convex hull surrounding all the points
 */
vector<point> brute_forceConvexHull(vector<point> points){
    vector<point> convexHull;

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

/**
 * Solves the Convex Hull problem with the divide and conquer solution
 *
 * @param  points the set of points to solve the problem for.
 * @return        the convex hull surrounding all the points
 */
vector<point> divideAndConquerConvexHull(vector<point> points){
    vector<point> convexHull;

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
    }

    //run brute force with animation and time for fun
    if(argc == 3){
        string algo(argv[1]);
        string option(argv[2]);
        if(algo == "-convex"){
            if(option == "-brute"){
                //call brute force convex hull, it does all the work
                brute_forceConvexHull(points);
            } else if(option == "-divide"){
                divideAndConquerConvexHull(points);
            } else {
                cout << "Invalid first argument: [-brute -divide] expected" << endl;
                return 1;
            }
        } else if(algo == "-closest"){
            if(option == "-brute"){
                pair<point, point> closestPair = brute_forceClosestPair(points);

                //TODO:: circle them on the plot

            } else if(option == "-divide"){
                pair<point, point> closestPair = divideAndConquerClosestPair(points);

                //TODO:: circle them on the plot

            } else {
                cout << "Invalid first argument: [-brute -divide] expected" << endl;
                return 1;
            }
        } else {
            cout << "Invalid first argument: [-convex, -closest] expected" << endl;
            return 1;
        }

        bool stopped = false;
        bool colored = false;
        int x,y, xd, yd;
        int R,G,B;
        
        while (!g.getQuit())
        {
    		if(!stopped){
        			x = rand()%g.getCol();
    			y = rand()%g.getRow();
    			R = rand()%256;
    			G = rand()%256;
    			B = rand()%256;
    			for(xd = 0; xd < 10 && x + xd < g.getCol(); xd++ ){
    				for(yd = 0; yd < 10 && y + yd < g.getRow(); yd++ ){
    					if(colored){
    						g.plotPixel( x + xd, y + yd, R, G, B);
    					}
    					else{
    					    g.plotPixel( x + xd, y + yd, 0, G, 0);
    					}

    				}
    			}
    		}

    		if(g.kbhit()){
    			g.getKey();
    		}

    		if(g.getMouseClick(x,y)){
    			stopped = !stopped;
    		}

    		g.update();
        }
    } else {
        cout << "ERROR: Number of arguments must be 2: [-convex, -closest] [-brute -divide]" << endl;
        return 1;
    }



    return 0;
}
