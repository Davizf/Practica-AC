#include <iostream>
#include <random>
#include "SpaceObject.h"
#include <fstream>
#include "math_functionsv1.cpp"
using namespace std;
#include <iomanip>
#include <omp.h>

int num_asteroids;
int num_iterations;
int num_planets;
int seed;
SpaceObject * anyKind;
vector<SpaceObject> asteroids;
vector<SpaceObject> planets;

//Random distributions
default_random_engine re{seed};
uniform_real_distribution<double> xdist{0.0, std::nextafter(width,
                                    	std::numeric_limits<double>::max())};
uniform_real_distribution<double> ydist{0.0, std::nextafter(height,
                                        std::numeric_limits<double>::max())};
normal_distribution<double> mdist{mass, sdm};

void create_asteroids(){
  for(int i = 0; i < num_asteroids; i++){
    anyKind = new SpaceObject(xdist(re), ydist(re), 0.0, 0.0, mdist(re), num_asteroids);
    anyKind->isAsteroid = true;
    asteroids.push_back(*anyKind);
    delete anyKind;
  }
}

void create_planets(){
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
}

void create_init_conf(){
  ofstream init;
  init.open("init_conf.txt");
  //Initial configuration
  init << num_asteroids << " " << num_iterations << " " << num_planets << " " << seed << "\n";
  //Asteroids'data
  for(auto &asteroids: asteroids){
    init << fixed << setprecision(3)  << asteroids.x << " " << asteroids.y << " " << asteroids.m << "\n";
  }
  //Planets'data
  for(auto &planets: planets){
    init << fixed << setprecision(3) << planets.x << " " << planets.y << " " << planets.m << "\n";
  }
  init.close();
}

void create_out(){
  ofstream out;
  out.open("out.txt");
  //Storing final data
  for(auto &asteroids: asteroids){
    out << fixed << setprecision(3) << asteroids.x << " " << asteroids.y << " " << asteroids.vx << " " << asteroids.vy << " " << asteroids.m << "\n";
  }
  out.close();	
}

int main(int argc, char *argv[]) {
  //Check input conditions
  if(argc == 5){
    num_asteroids = atoi(argv[1]);
    num_iterations = atoi(argv[2]);
    num_planets = atoi(argv[3]);
    seed = atoi(argv[4]);
    if(num_asteroids<0 || num_iterations<0 || num_planets<0 || seed<=0){
      cout << "nasteroids-seq: Wrong arguments.\nCorrect use:\nnasteroid-seq num_asteroids num_iterations num_planets seed\n";
      return -1;
    }
  }else{
    cout << "nasteroids-seq: Wrong arguments.\nCorrect use:\nnasteroid-seq num_asteroids num_iterations num_planets seed\n";
    return -1;
  }
  
  #pragma omp parallel num_threads(4){

  //Creating asteroids...
  create_asteroids();

  //Creating planets...
  create_planets();

  //Generating init_conf_txt
  create_init_conf();

  //Implementate the movements of asteroids
  vector<double> forceX (num_asteroids);
  vector<double> forceY (num_asteroids);
  vector<double> forces (2);

  //Number of iterations
  for(int i = 0; i < num_iterations; i++){
  	cout << "Nº iteracion: " << i << "\n";
  	fill(forceX.begin(), forceX.end(), 0);
  	fill(forceY.begin(), forceY.end(), 0);
    //Fixing one asteroid to compare itself to others asteroids/planets
    for(int j = 0; j < num_asteroids; j++){
      asteroids[j].before_vx = asteroids[j].vx;
      asteroids[j].before_vy = asteroids[j].vy;
      asteroids[j].before_x = asteroids[j].x;
      asteroids[j].before_y = asteroids[j].y;
      //Compare with other asteroids
      for(int k = 0; k < num_asteroids; k++){
        //Proceed the sum of forces if it is not the same asteroid
        if((j != k) && (j < k)) {
          if(distance_between_elements(asteroids[j], asteroids[k]) > 2){
            forces = normal_movement(asteroids[j], asteroids[k]);
            forceX[j] += forces[0];
            forceY[j] += forces[1];
            forceX[k] -= forces[0];
            forceY[k] -= forces[1];
          }
        }
      }
      //Planet forces
      for(int l = 0; l < num_planets; l++){
        if(distance_between_elements(asteroids[j], planets[l]) > 2){
       	  forces = normal_movement(asteroids[j], planets[l]);
       	  forceX[j] += forces[0];
          forceY[j] += forces[1];
        }
      }
  	}

    //Update coordinates and speeds
	for(int m = 0; m < num_asteroids; m++){
		change_element_position(&asteroids[m], forceX[m], forceY[m]);
	}

	//Possible collisions
	for(int n = 0; n < num_asteroids; n++){
	  for(int o = 0; o < num_asteroids; o++){
	    if((n != o) && (n < o)){
		  if((distance_between_elements(asteroids[n], asteroids[o]) <= 2) && (i > 0)){
		    collision_handling(&asteroids[n], &asteroids[o]);
		    asteroids[n].collisions++;
		    asteroids[o].collisions++;
		  }
		}
	  }
	}

    //If there are collisions position changes
    for(int p = 0; p < num_asteroids; p++){
      if(asteroids[p].collisions != 0){
        asteroids[p].x = asteroids[p].before_x;
        asteroids[p].y = asteroids[p].before_y;
        change_element_position(&asteroids[p], forceX[p], forceY[p]);
        asteroids[p].collisions = 0;
      }
    }
  }


  //Generating out.txt
  create_out();
 }

  return 0;
}