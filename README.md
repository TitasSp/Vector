# Vector.h

Ši biblioteka pateikia universalią C++ šabloninę `Vector` klasę, kuri imituoja STL `std::vector` elgseną. Ji palaiko dinaminį dydžio valdymą, iteratorius, atminties rezervavimą, įterpimą, pašalinimą ir kt.

## Savybės

- Dinamiškai augantis masyvas su rezervavimo galimybe
- Pilnai palaikoma kopijavimo ir perkėlimo semantika
- Iteratoriai ir reverse iteratoriai
- Prieigos metodai: `at`, `[]`, `front`, `back`, `data`
- Modifikavimo metodai: `insert`, `erase`, `push_back`, `pop_back`, `emplace`, `resize`, `clear`
- Operatoriai: `==`, `!=`, `<`, `<=`, `>`, `>=`
- Palaikomi šablonai, initializer list'ai ir range konstruktoriai
- Atminties valdymas su `reserve` ir `shrink_to_fit`

## Naudojimas

```cpp
#include "Vector.h"
#include <iostream>

int main() {
    Vector<int> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    std::cout << "Vector size: " << vec.size() << "\n";
    std::cout << "First element: " << vec.front() << "\n";
    std::cout << "Last element: " << vec.back() << "\n";

    vec.pop_back();

    for (auto val : vec) {
        std::cout << val << " ";
    }

    return 0;
}

```
# std::vector ir Vector greičio palyginimo lentelė:

![image](https://github.com/user-attachments/assets/dea36c61-9839-45ad-bbd6-aa2921fd6fdf)
![image](https://github.com/user-attachments/assets/4735f25d-8a69-481c-8f5b-5090a6e7c924)

```
std::vector reallocations with 100000000: 28
Vector reallocations with 100000000: 28
Testas 1
studentai100000.txt
Reading file: studentai100000.txt
Studentu nuskaitymas is failo uztruko: 152 ms
Total students read: 100000
Studentu rikiavimas uztruko: 51 ms
Studentu skaidymas ir irasymas i failus uztruko: 437 ms
Is viso uztruko: 898 ms

studentai1000000.txt
Reading file: studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 902 ms
Total students read: 600000
Studentu rikiavimas uztruko: 389 ms
Studentu skaidymas ir irasymas i failus uztruko: 2313 ms
Is viso uztruko: 5065 ms

studentai10000000.txt
Reading file: studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 16171 ms
Total students read: 10000000
Studentu rikiavimas uztruko: 8631 ms
Studentu skaidymas ir irasymas i failus uztruko: 48234 ms
Is viso uztruko: 100677 ms


Testas 2
studentai100000.txt
Reading file: studentai100000.txt
Studentu nuskaitymas is failo uztruko: 186 ms
Total students read: 100000
Studentu rikiavimas uztruko: 59 ms
Studentu skaidymas ir irasymas i failus uztruko: 524 ms
Is viso uztruko: 1165 ms

studentai1000000.txt
Reading file: studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1031 ms
Total students read: 600000
Studentu rikiavimas uztruko: 414 ms
Studentu skaidymas ir irasymas i failus uztruko: 2825 ms
Is viso uztruko: 5914 ms

studentai10000000.txt
Reading file: studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 18119 ms
Total students read: 10000000
Studentu rikiavimas uztruko: 9020 ms
Studentu skaidymas ir irasymas i failus uztruko: 48570 ms
Is viso uztruko: 103486 ms


Testas 3
studentai100000.txt
Reading file: studentai100000.txt
Studentu nuskaitymas is failo uztruko: 213 ms
Total students read: 100000
Studentu rikiavimas uztruko: 63 ms
Studentu skaidymas ir irasymas i failus uztruko: 512 ms
Is viso uztruko: 1130 ms

studentai1000000.txt
Reading file: studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1099 ms
Total students read: 600000
Studentu rikiavimas uztruko: 418 ms
Studentu skaidymas ir irasymas i failus uztruko: 3046 ms
Is viso uztruko: 6155 ms

studentai10000000.txt
Reading file: studentai10000000.txt
Studentu nuskaitymas is failo uztruko: 18393 ms
Total students read: 10000000
Studentu rikiavimas uztruko: 8674 ms
Studentu skaidymas ir irasymas i failus uztruko: 48685 ms
Is viso uztruko: 103587 ms
```