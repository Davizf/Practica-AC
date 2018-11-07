#include <iostream>
#include <random>
#include "SpaceObject.h"
using namespace std;

int num_asteroids;
int num_iteracions;
int num_planets;
int seed;
int width = 200;
int height = 200;
double mass = 1000;
double sdm = 50;
vector<SpaceObject> asteroids;
vector<SpaceObject> planets;

int main() {
  cout << "Enter the number of asteroids:";
  cin >> num_asteroids;
  cout << "Enter the number of iterations:";
  cin >> num_iteracions;
  cout << "Enter the number of planets:";
  cin >> num_planets;
  cout << "Enter the seed number:";
  cin >> seed;

  if(num_asteroids<0 || num_iteracions<0 || num_planets<0 || seed<=0){
    cout << "nasteroids-seq: Wrong arguments.\nCorrect use:\nnasteroid-seq num_asteroids num_iteracions num_planets seed\n";
    return -1;
  }
  
  //Random distributions
  default_random_engine re{semilla};
  uniform_real_distribution<double> xdist{0.0, std::nextafter(width,
                                        std::numeric_limits<double>::max())};
  uniform_real_distribution<double> ydist{0.0, std::nextafter(height,
                                        std::numeric_limits<double>::max())};
  normal_distribution<double> mdist{mass, sdm};
  
  //Creating asteroids...
  for(int i = 0; i < num_asteroides; i++){
    SpaceObject anyKind(xdist(re), ydist(re), 0.0, 0.0, mdist(re));
    anyKind.isAsteroid = true;
    asteroids[i] = anyKind;
  }

  return 0;
}
