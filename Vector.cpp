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
    std::cout<< "Element does not exist!"<<std::endl;return;
    }
  elem[id]=val;
}


// get'eriai
int Vector::size() const {return sz;} 

double& Vector::operator[](int i) { 
    if (i < 0 || size() <= i) throw std::out_of_range {"Vector::operator[] out of range!!!"};
    return elem[i]; 
} 
const double& Vector::operator[](int i) const { 
    if (i < 0 || size() <= i) throw std::out_of_range {"Vector::operator[] out of range!!!"};
    return elem[i]; 
} 
// destruktorius: atlaisvina klasės objekto resursus
Vector::~Vector(){ 
  delete[] elem; 
  //std::cout<< "Object destroyed\n"; 
}

// apkeičia du elementus vietomis
void Vector::swap(int i, int j) {
    if (i < 0 || size() <= i || j < 0 || size() <= j) {
        std::cout << "Element does not exist!" << std::endl;
        return;
    }
    double temp = elem[i];
    elem[i] = elem[j];
    elem[j] = temp;
}

// istrina vektorių
void Vector::erase() {
    sz = 0; 
    delete[] elem;
    elem = nullptr;
}

// įterpia elementą į vektorių
void Vector::insert(int i, double val) {
    if (i < 0 || size() < i) {
        throw std::out_of_range("Index out of range in insert()");
        return;
    }
    double* new_elem = new double[sz + 1];
    for (int j = 0; j < sz + 1; ++j) {
        if (j < i) {
            new_elem[j] = elem[j];
        } else if (j == i) {
            new_elem[j] = val;
        } else {
            new_elem[j] = elem[j - 1];
        }
    }
    delete[] elem;
    elem = new_elem;
    sz++;
}

// pašalina paskutinį elementą
void Vector::pop() {
    if (sz == 0) throw std::out_of_range("Pop from empty vector");
    sz--;
}

// išvalo vektorių elementu reiksmes
void Vector::clear() {
    for (int i = 0; i < sz; ++i) {
        elem[i] = 0;
    }
}

// pakeičia vektoriaus dydį
void Vector::resize(int s) {
    if (s < 0) {
        std::cout << "Invalid size!" << std::endl;
        return;
    }
    double* new_elem = new double[s];
    for (int i = 0; i < std::min(sz, s); ++i) {
        new_elem[i] = elem[i];
    }
    delete[] elem;
    elem = new_elem;
    sz = s;
}

// prideda elementą į vektoriaus pabaigą
void Vector::push_back(double val) {
    double* new_elem = new double[sz + 1];
    for (int i = 0; i < sz; ++i) {
        new_elem[i] = elem[i];
    }
    new_elem[sz] = val;
    delete[] elem;
    elem = new_elem;
    sz++;
} 

// sumažina vektoriaus dydį
void Vector::shrink_to_fit() {
    if (sz == 0) return;
    double* new_elem = new double[sz - 1];
    for (int i = 0; i < sz - 1; ++i) {
        new_elem[i] = elem[i];
    }
    delete[] elem;
    elem = new_elem;
    sz--;
}