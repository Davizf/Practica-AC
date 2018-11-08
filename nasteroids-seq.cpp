#include <iostream>
#include <random>
#include "SpaceObject.h"
using namespace std;

int num_asteroids;
int num_iterations;
int num_planets;
int seed;
int width = 200;
int height = 200;
double mass = 1000;
double sdm = 50;
vector<SpaceObject> asteroids;
vector<SpaceObject> planets;

int main() {
  //Input
  cout << "Enter the number of asteroids:";
  cin >> num_asteroids;
  cerr << "Enter the number of iterations:";
  cin >> num_iterations;
  cerr << "Enter the number of planets:";
  cin >> num_planets;
  cerr << "Enter the seed number:";
  cin >> seed;

  //Check input conditions
  if(num_asteroids<0 || num_iterations<0 || num_planets<0 || seed<=0){
    cout << "nasteroids-seq: Wrong arguments.\nCorrect use:\nnasteroid-seq num_asteroids num_iterations num_planets seed\n";
    return -1;
  }

  //Random distributions
  default_random_engine re{seed};
  uniform_real_distribution<double> xdist{0.0, std::nextafter(width,
                                        std::numeric_limits<double>::max())};
  uniform_real_distribution<double> ydist{0.0, std::nextafter(height,
                                        std::numeric_limits<double>::max())};
  normal_distribution<double> mdist{mass, sdm};

  //Creating asteroids...
  for(int i = 0; i < num_asteroids; i++){
    SpaceObject anyKind(xdist(re), ydist(re), 0.0, 0.0, mdist(re));
    anyKind.isAsteroid = true;
    asteroids[i] = anyKind;
  }

  //Creating planets...
  for(int i = 0; i < num_planets; i++){
    SpaceObject anyKind(0.0,0.0,0.0,0.0,0.0);
    //Clockwise planet placement...
    if(i % 4 == 0){
      SpaceObject anyKind(xdist(re), height, 0.0, 0.0, mdist(re) * 10);
    } else if(i % 4 == 1) {
      SpaceObject anyKind(0, ydist(re), 0.0, 0.0, mdist(re) * 10);
    } else if(i % 4 == 2){
      SpaceObject anyKind(xdist(re), 0, 0.0, 0.0, mdist(re) * 10);
    } else if(i % 4 == 3){
      SpaceObject anyKind(width, ydist(re), 0.0, 0.0, mdist(re) * 10);
    }
    anyKind.isAsteroid = false;
    planets[i] = anyKind;
  }

  return 0;
}
