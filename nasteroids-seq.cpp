#include <iostream>
using namespace std;

int num_asteroids;
int num_iteracions;
int num_planets;
int seed;

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
  return 0;
}
