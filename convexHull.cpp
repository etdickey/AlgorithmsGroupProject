#include <iostream>
#include <vector>

#include "SDL_Plotter.h"
#include "point.h"

using namespace std;

#define endl '\n'
const int ROW_MAX = 500;
const int COL_MAX = 1000;

/**
 * Solves the Convex Hull problem with the brute force solution
 *
 * @param  points the set of points to solve the problem for.
 * @return        the convex hull surrounding all the points
 */
vector<point> brute_force(vector<point> points){
    vector<point> convexHull;

    return convexHull;
}

/**
 * Solves the Convex Hull problem with the brute force solution (with animatino)
 *
 * @param  points the set of points to solve the problem for.
 * @return        the convex hull surrounding all the points
 */
// vector<point> brute_force(vector<point> points, SDL_Plotter& g){
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
vector<point> divideAndConquer(vector<point> points){
    vector<point> convexHull;

    return convexHull;
}

/**
 * Solves the Convex Hull problem with the divide and conquer solution (with animation)
 *
 * @param  points the set of points to solve the problem for.
 * @return        the convex hull surrounding all the points
 */
// vector<point> divideAndConquer(vector<point> points, SDL_Plotter& g){
//     vector<point> convexHull;
//
//     return convexHull;
// }

int main(int argc, char** argv){
    //define variables
    SDL_Plotter g(ROW_MAX,COL_MAX);
    cout << "Hello amazin world" << endl;
    //import data (multiple data sets?)

    //run brute force with animation and time for fun

    //run divide and conquer with animation and time for fun


    return 0;
}
