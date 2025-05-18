#include "Vector.h"
// konstruktoriai   
Vector::Vector() { 
  sz=0; 
  elem =new double[sz];
}
Vector::Vector(int s) {
  sz=s; 
  elem=new double[s]; 
}
Vector::Vector(int s, double val) {
  sz=s; 
  elem=new double[s];
  std::fill_n(elem,s,val);  
}
// set'eriai
void Vector::setElem (int id, double val){
  if (id<0 || id >= sz) {
    std::cout<< "Element does not exist!"<<std::endl;return;}
  elem[id]=val;
}
// get'eriai
int Vector::size() const {return sz;} 
double& Vector::operator[](int i) { 
    if (i < 0 || size() <= i) throw std::out_of_range {"Vector::operator[] out of range!!!"};
    return elem[i]; 
 } 
// destruktorius: atlaisvina klasės objekto resursus
Vector::~Vector(){ 
  delete[] elem; 
  std::cout<< "Object destroyed\n"; 
}