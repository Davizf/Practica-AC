#include <iostream>
using namespace std;

int num_asteroides;
int num_iteraciones;
int num_planetas;
int semilla;

int main() {
  cout << "Enter the number of asteroids:";
  cin >> num_asteroides;
  cout << "Enter the number of iterations:";
  cin >> num_iteraciones;
  cout << "Enter the number of planets:";
  cin >> num_planetas;
  cout << "Enter the seed number:";
  cin >> semilla;

  if(num_asteroides<0 || num_iteraciones<0 || num_planetas<0 || semilla<=0){
    cout << "nasteroids-seq: Wrong arguments.\nCorrect use:\nnasteroid-seq num_asteroides num_iteraciones num_planetas semilla\n";
    return -1;
  }
  return 0;
}
