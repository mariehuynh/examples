/***********************************************************
 What is the area of the crescent formed by a small circle
 inside a larger circle?  This short program calculates an
 estimate via a Monte Carlo method.  Note that this example
 does no error checking and makes a lot of assumptions 
 about the input.
 
 - Marie Huynh
   marie@mariehuynh.com
   Nov 3, 2013
 **********************************************************/

#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;


class Circle{
  float radius;
  float offset_x;
  float offset_y;
  
  public:
    Circle(float r, float ox, float oy) {
      radius   = r;
      offset_x = ox;
      offset_y = oy;
    }
  
    // Will return a true if coordinates are within the circle
    // r^2 = x^2 + y^2
    bool inside (float x, float y) {
      float dx = x - offset_x;
      float dy = y - offset_y;
      if(((dx * dx) + (dy * dy)) < (radius * radius))
        return true;
      else return false;
    }
};

float montecarloarea(int num_runs,
                     Circle outer_eq,
                     Circle inner_eq,
                     float x_min,
                     float x_max,
                     float y_min,
                     float y_max) {
  
  int hitctr = 0;
  float xrange = x_max - x_min;
  float yrange = y_max - y_min;
  
  // Seed the random number generator
  srand (time(NULL));
  
  for(int i = 0; i < num_runs; i++) {
    float x = ((float)rand() / RAND_MAX * xrange) + x_min;
    float y = ((float)rand() / RAND_MAX * yrange) + y_min;
    
    if(outer_eq.inside(x,y) 
       && ! inner_eq.inside(x,y)) {
      hitctr++;
    }
  }
  
  return ((float)hitctr / num_runs) * xrange * yrange;
}

int main() {
  float area, rl, xl,yl,rs,xs,ys,num_runs;
  
  cout << "This will use the Monte Carlo method to find the area of the crescent between two overlapping circles.\n";
  cout << "Radius of the larger circle: ";
  cin >> rl;
  cout << "x offset: ";
  cin >> xl;
  cout << "y offset: ";
  cin >> yl;
  cout << "Radius of the smaller circle: ";
  cin >> rs;
  cout << "x offset: ";
  cin >> xs;
  cout << "y offset: ";
  cin >> ys;
  cout << "Number of runs: ";
  cin >> num_runs;
  
  Circle outer_eq (rl, xl, yl);
  Circle inner_eq (rs, xs, ys);
  
  // Minimum box necessary
  float x_min = xl - rl;
  float x_max = xl + rl;
  float y_min = yl - rl;
  float y_max = yl + rl;
  
  area = montecarloarea(num_runs,
                        outer_eq,
                        inner_eq,
                        x_min,
                        x_max,
                        y_min,
                        y_max); 
  
  cout << "The area is " << area;

  return 0;  
}
