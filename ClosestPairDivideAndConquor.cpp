#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>

//Josh Holland

using namespace std;

struct Point{
    int x,y;
    
    bool operator<(Point& other){
        return this->x < other.x;
    }
    
    double distanceTo(Point& other){
        return sqrt((this->x-other.x)^2+(this->y-other.y)^2);
    }
};

bool sort_by_x(const Point& a, const Point& b){
    return a.x < b.x;
}

bool sort_by_y(const Point& a, const Point& b){
    return a.y < b.y;
}


double algorithm_thing_recurse(vector<Point> points, int left, int right){
    //right is 1 more than the index that it stops at 
    int size = right-left;
    if(size == 2){
        return points[left].distanceTo(points[left+1]);
    }
    Point middle = points[left+size/2];
    
    //subarray 1: left,left+size/2
    //subarray 2: left+size/2+1,right
    
    
    double minLeft = algorithm_thing_recurse(points,left,left+size/2);
    double minRight= algorithm_thing_recurse(points,left+size/2+1,right);
    
    double min_d = minLeft;
    if(minRight < min_d){
        min_d = minRight;
    }
    
    double vertical_line_x = points[left].x + (points[right-1].x-points[left].x)/2;
    
    vector<Point> closer_to_line;
    for(Point point: points) {
        if(abs(point.x-vertical_line_x) < min_d) {
            closer_to_line.push_back(point);
        }
    }
    
    if(closer_to_line.size() < 2){
        return min_d;
    }
    //sort by y:
    sort(closer_to_line.begin(),closer_to_line.end(),sort_by_y);
    double min_middle = closer_to_line[1].distanceTo(closer_to_line[0]);
    
    for(int i = 0; i < closer_to_line.size(); i++){
        for(int j = i+1; j < closer_to_line.size(); j++){
            if(closer_to_line[i].distanceTo(closer_to_line[j]) < min_middle){
                min_middle = closer_to_line[i].distanceTo(closer_to_line[j]);
            }
        }
    }
    
    if(min_middle < min_d){
        min_d = min_middle;
    }
    
    return min_d;
    
}

double algorithm_thing(vector<Point> points){
    //it is assumed that points is not empty
    
    //sort points by x coordinate 
    sort(points.begin(),points.end(),sort_by_x);
    return algorithm_thing_recurse(points,0,points.size());
    
}

int main(){
    cout << "whoopee" << endl;
}