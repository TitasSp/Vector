#include "Vector.h"

int main() {
  Vector v1 {2, 1.0}; // sukonstruojame vektorių: (1.0, 1.0)
  std::cout << v1[0] << ", " << v1[1] << std::endl; 
  const Vector v2 {2, 3.0}; // sukonstruojame vektorių: (3.0, 3.0)
  std::cout << v2[0] << ", " << v2[1] << std::endl; 

  Vector v3{3, 4.0}; // sukonstruojame vektorių: (4.0, 4.0, 4.0)
  std::cout << v3[0] << ", " << v3[1] << ", " << v3[2] << std::endl;

  v3.setElem(0, 5.0); // v3[0] = 4.0 -> v3[0] = 5.0
  v3.swap(0, 1); // v3[0] = 5.0, v3[1] = 4.0 -> v3[0] = 4.0, v3[1] = 5.0
  std::cout << v3[0] << ", " << v3[1] << std::endl; 

  v3.clear(); // atlaisviname vektoriaus resursus
  std::cout << "Vektoriaus dydis: " << v3.size() << std::endl; 

  v1.insert(0, 15); // įterpiame elementą į vektorių
  std::cout << v1[0] << std::endl; 
}