#include <iostream>
#include <random>
#include "SpaceObject.h"
#include <fstream>
using namespace std;

int num_asteroids;
int num_iterations;
int num_planets;
int seed;
int width = 200;
int height = 200;
double mass = 1000;
double sdm = 50;
SpaceObject * anyKind;
vector<SpaceObject> asteroids;
vector<SpaceObject> planets;

int main() {
  //Input
  cout << "Enter the number of asteroids:";
  cin >> num_asteroids;
  cout << "Enter the number of iterations:";
  cin >> num_iterations;
  cout << "Enter the number of planets:";
  cin >> num_planets;
  cout << "Enter the seed number:";
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
    anyKind = new SpaceObject(xdist(re), ydist(re), 0.0, 0.0, mdist(re));
    anyKind->isAsteroid = true;
    asteroids.push_back(*anyKind);
    delete anyKind;
  }

  //Creating planets...
  for(int i = 0; i < num_planets; i++){
    //Clockwise planet placement...
    if(i % 4 == 0){
      anyKind = new SpaceObject(0, ydist(re), 0.0, 0.0, mdist(re) * 10);
    } else if(i % 4 == 1) {
      anyKind = new SpaceObject(xdist(re), 0, 0.0, 0.0, mdist(re) * 10);
    } else if(i % 4 == 2){
      anyKind = new SpaceObject(width, ydist(re), 0.0, 0.0, mdist(re) * 10);
    } else if(i % 4 == 3){
      anyKind = new SpaceObject(xdist(re), height, 0.0, 0.0, mdist(re) * 10);
    }
    anyKind->isAsteroid = false;
    planets.push_back(*anyKind);
    delete anyKind;
  }

  //Generating init_conf_txt
  ofstream file;
  file.open("init_conf_txt");
  //Initial configuration
  file << num_asteroids << " " << num_iterations << " " << num_planets << " " << seed << "\n";
  //Asteroids'data
  for(int i = 0; i < num_asteroids; i++){
    file << asteroids[i]->x << " " << asteroids[i]->y << " " << asteroids[i]->m << "\n";
  }
  //Planets'data
  for(int i = 0; i < num_planets; i++){
    file << planets[i]->x << " " << planets[i]->y << " " << planets[i]->m << "\n";
  }


  file.close();

  return 0;
}
