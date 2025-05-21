#include "Vector.h"

int main() {
    Vector v1 {2, 1.0}; // sukonstruojame vektorių: (1.0, 1.0)
    std::cout << "Vector: ";
    std::cout << v1[0] << ", " << v1[1] << std::endl; 

    const Vector v2 {2, 3.0}; // sukonstruojame vektorių: (3.0, 3.0)
    std::cout << "Const vector: ";
    std::cout << v2[0] << ", " << v2[1] << std::endl; 

    Vector v3{3, 4.0}; // sukonstruojame vektorių: (4.0, 4.0, 4.0)
    std::cout << "Vector: ";
    std::cout << v3[0] << ", " << v3[1] << ", " << v3[2] << std::endl;

    v3.setElem(0, 5.0); // v3[0] = 4.0 -> v3[0] = 5.0
    v3.swap(0, 1); // v3[0] = 5.0, v3[1] = 4.0 -> v3[0] = 4.0, v3[1] = 5.0
    std::cout << "Swap: ";
    std::cout << v3[0] << ", " << v3[1] << std::endl; 

    v3.erase(); // atlaisviname vektoriaus resursus
    std::cout << "Erase: ";
    std::cout << "Vektoriaus dydis: " << v3.size() << std::endl; 

    v1.insert(0, 15); // įterpiame elementą į vektorių
    std::cout << "Insert: ";
    std::cout << v1[0] << std::endl; 

    v1.pop_back(); // pašaliname paskutinį elementą iš vektoriaus
    //std::cout << v1[0] << " " << v1[1] << " " << v1[2] << std::endl;
  
    v1.clear(); // išvalome vektorių
    std::cout << "Clear: ";
    std::cout << v1[0] << std::endl;
   
    v3.resize(5); // pakeičiame vektoriaus dydį
    std::cout << "Resize: ";
    std::cout << v3.size() << std::endl;

    v3.push_back(10); // pridedame elementą į vektoriaus pabaigą
    std::cout << "Push_back: ";
    std::cout << v3[5] << std::endl;
}