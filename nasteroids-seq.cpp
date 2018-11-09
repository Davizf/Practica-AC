#include <iostream>
#include <random>
#include "SpaceObject.h"
#include <fstream>
#include"math_functionsv1.cpp"
using namespace std;

int num_asteroids;
int num_iterations;
int num_planets;
int seed;
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
  ofstream init;
  init.open("init_conf.txt");
  //Initial configuration
  init << num_asteroids << " " << num_iterations << " " << num_planets << " " << seed << "\n";
  //Asteroids'data
  for(auto &asteroids: asteroids){
    init << asteroids.x << " " << asteroids.y << " " << asteroids.m << "\n";
  }
  //Planets'data
  for(auto &planets: planets){
    init << planets.x << " " << planets.y << " " << planets.m << "\n";
  }
  init.close();
  
  //Implementate the movements of asteroids
  vector<double> forceX (num_asteroids);
  vector<double> forceY (num_asteroids);
  vector<double> forces;
  //Number of iterations
  for(int i = 0; i < num_iterations; i++){
    //Fixing one asteroid to compare itself to others asteroids/planets
    for(int j = 0; j < num_asteroids; j++){
      //Compare with other asteroids     
      for(int k = 0; k < num_asteroids; k++){
        //Proceed the sum of forces if it is not the same asteroid
        if(j != k) {
          if(distance_between_elements(asteroids[j], asteroids[k]) < 2){
            asteroids[j].collides = k;
          }
          forces = normal_movement(asteroids[j], asteroids[k]);
          if(j > k) {
            forceX[j] -= forces[0];
            forceY[j] -= forces[1];
          } else {
            forceX[j] += forces[0];
            forceY[j] += forces[1];
          }
        }     
        //Compare with planets
        for(int l = 0; l < num_planets; l++){
          forces = normal_movement(asteroids[j], planets[l]);
          forceX[j] += forces[0];
          forceY[j] += forces[1];
        }        
      }
    }
    //Update coordinates and speeds
    for(int m = 0; m < asteroids.size(); m++){
      if(asteroids[m].collides == -1){
        change_element_position(&asteroids[m],forceX[m], forceY[m]);
      } else {
        collision_handling(asteroids[m], asteroids[asteroids[m].collides]);
        asteroids[m].collides = -1;
      }
    }       
  }


  //Generating out.txt
  ofstream out;
  out.open("out.txt");
  //Storing final data
  for(auto &asteroids: asteroids){
    out << asteroids.x << " " << asteroids.y << " " << asteroids.vx << " " << asteroids.vy << " " << asteroids.m << "\n";
  }
  out.close();

  return 0;
}
