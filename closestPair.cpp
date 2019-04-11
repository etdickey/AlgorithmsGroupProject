#include <iostream>
#include <vector>

#include "SDL_Plotter.h"
#include "point.h"


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
pair<point, point> brute_force(vector<point> points){
    pair<point, point> closestPair = make_pair(point(0,0), point(0,0));

    return closestPair;
}

/**
 * Solves the CLosest Pair problem with the brute force solution (and animates it)
 * @param points [description]
 */
// pair<point, point> brute_force(vector<point> points, SDL_Plotter& g){
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
pair<point, point> divideAndConquer(vector<point> points){
    pair<point, point> closestPair = make_pair(point(0,0), point(0,0));

    return closestPair;
}

/**
 * Solves the Closest Pair problem with a Divide and Conquer strategy (with animation)
 *
 * @param points the set of points to solve the problem for
 * @return the closest pair of points
 */
// pair<point, point> divideAndConquer(vector<point> points, SDL_Plotter& g){
//     pair<point, point> closestPair = make_pair(point(0,0), point(0,0));
//
//     return closestPair;
// }

int main(int argc, char** argv){
    //set up variables
    SDL_Plotter g(ROW_MAX,COL_MAX);
    cout << "Hello amazin world" << endl;
    //import the data (multiple data sets?)

    //run brute force with animation (AND TIME) -- timing is for fun

    //run divide and conquer with animation (AND TIME) -- timing is for fun



    return 0;
}
