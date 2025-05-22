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


