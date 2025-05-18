#include "Vector.h"

int main() {
  Vector v1 {2, 1.0}; // sukonstruojame vektorių: (1.0, 1.0)
  std::cout << v1[0] << ", " << v1[1] << std::endl; // Ką gausime?
  const Vector v2 {2, 3.0}; // sukonstruojame vektorių: (3.0, 3.0)
  std::cout << v2[0] << ", " << v2[1] << std::endl; // Ką gausime?
}