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
  // destruktorius: atlaisvina klasės objekto resursus
  ~Vector();
};