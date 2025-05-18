#include <iostream>
class Vector{
private:
  int sz;        // elementų skaičius 
  double *elem;  // rodyklė į elementus
public:
  // konstruktoriai  
  Vector();
  Vector(int s);
  Vector(int s, double val);
  // set'eriai
  void setElem (int id, double val);
  // get'eriai
  int size() const;
  double getElem (int id);
  double& operator[](int i);
  const double& operator[](int i) const;
  
  // destruktorius: atlaisvina klasės objekto resursus
  ~Vector();

  // funkcijos
  void swap(int i, int j); // apkeičia du elementus vietomis
  void erase(); // istrina vektorių
  void insert(int i, double val); // įterpia elementą į vektorių
  void pop(); // pašalina paskutinį elementą iš vektoriaus
  void clear(); // išvalo vektorių elementu reiksmes
};