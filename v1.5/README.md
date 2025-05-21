# Studentų Pažymių Valdymo Sistema

Apie programą
-------------------------------------------------------------------
Ši programa skirta studentų pažymių ir galutinio įvertinimo valdymui. Sistema leidžia įvesti, generuoti, skaityti iš failų bei apdoroti studentų duomenis, apskaičiuoti galutinius įvertinimus ir rūšiuoti studentus pagal įvairius kriterijus.

Funkcionalumas
-------------------------------------------------------------------

Duomenų įvedimas: galimybė rankiniu būdu įvesti studentų vardus, pavardes ir pažymius
Atsitiktinis generavimas: automatinis studentų ir jų pažymių generavimas
Duomenų nuskaitymas: efektyvus didelių duomenų failų nuskaitymas
Duomenų išsaugojimas: rezultatų išsaugojimas į tekstinius failus
Skaičiavimai: galutinio balo skaičiavimas naudojant vidurkį arba medianą
Rūšiavimas: studentų rūšiavimas pagal vardą, pavardę ar galutinį balą
Grupavimas: studentų skirstymas į "kietiakus" (≥5) ir "vargšiukus" (<5)
Efektyvumo testavimas: programos veikimo greičio matavimas ir optimizavimas

-------------------------------------------------------------------
Diegimas ir paleidimas
----------------------------------------------------------------

1. Klonuokite repozitoriją:
```
git clone https://github.com/TitasSp/Vector/tree/v3.0.git
```

2. Pereikite į programos direktoriją:
```
cd C:\"projekto direktorija"
```

3. Sukompiliuokite programą:
```
g++ -o program main.cpp funkcijos.cpp -std=c++17
```

4. Paleiskite programą:
```
./programa
```

Arba naudojant CMake
----------------------------------------------------------------
1. Atidarykite projekto direktoriją terminale:
```
cd C:\"projekto direktorija"
```
2. Sukurkite build direktoriją:
```
mkdir build
```
3. Pereikite į build direktoriją:
```
cd build
```
4. Paleiskite CMake, norint sugeneruoti build failus:
```
cmake ..
```
5. Kompiliuokite projekta:
```
cmake --build .
```
6. Paleiskite faila: 
```
.\ObjCppProject.exe
```

Naudojimas
----------------------------------------------------------------
Programa naudojama per terminalą. Paleidus programą, sekite pateikiamus nurodymus:

Pasirinkite konteinerio tipą (vector, deque arba list)
Pasirinkite duomenų įvedimo būdą:

Įvesti duomenis rankiniu būdu
Generuoti pažymius atsitiktinai
Generuoti ir pažymius, ir studentų vardus/pavardes
Nuskaityti duomenis iš failo


Pasirinkite skaičiavimo būdą (vidurkis arba mediana)
Pasirinkite rezultatų išvesties tipą (konsolė arba failas)
Pasirinkite rūšiavimo būdą

Releasai
----------------------------------------------------------------

## 🔹 v1.5
- `Studentas` klasė paveldi iš abstrakčios `Žmogus` klasės.

---

## 🔹 v1.2
- Įdiegti „Rule of Five“ metodai klasei `Studentas`.

---

## 🔹 v1.1
- `Studentas` perdarytas iš struktūros į klasę.
- Pridėti getteriai ir setteriai.

---

## 🔹 v1.0
- Palaikomi `vector`, `list`, `deque` konteineriai.
- Pridėtas `CMakeLists.txt` diegimui.

---------------------------------------------------------------------------------------------
Testavimo sistemos parametrai:
---------------------------------------------------------------------------------------------
Processor	12th Gen Intel(R) Core(TM) i5-1235U, 1300 Mhz, 10 Core(s), 12 Logical Processor(s)

Installed Physical Memory (RAM)	16.0 GB

SSD	512 GB NVMe Micron_2400_MTFDKBA512QFM

---------------------------------------------------------------------------------------------
Testai su klasemis (naudojant vector)
---------------------------------------------------------------------------------------------
studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3689 ms
Studentu rikiavimas uztruko: 158 ms
Studentu skaidymas ir irasymas i failus uztruko: 2043 ms
Is viso uztruko: 8654 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 20653 ms
Studentu rikiavimas uztruko: 919 ms
Studentu skaidymas ir irasymas i failus uztruko: 14782 ms
Is viso uztruko: 42303 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3414 ms
Studentu rikiavimas uztruko: 157 ms
Studentu skaidymas ir irasymas i failus uztruko: 2561 ms
Is viso uztruko: 7009 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 21611 ms
Studentu rikiavimas uztruko: 904 ms
Studentu skaidymas ir irasymas i failus uztruko: 14855 ms
Is viso uztruko: 42616 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3829 ms
Studentu rikiavimas uztruko: 187 ms
Studentu skaidymas ir irasymas i failus uztruko: 2722 ms
Is viso uztruko: 7787 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 19429 ms
Studentu rikiavimas uztruko: 820 ms
Studentu skaidymas ir irasymas i failus uztruko: 15109 ms
Is viso uztruko: 40092 ms

---------------------------------------------------------------------------------------------
Testai su strukturomis (naudojant vector)
---------------------------------------------------------------------------------------------
studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3392 ms
Studentu rikiavimas uztruko: 159 ms
Studentu skaidymas ir irasymas i failus uztruko: 1433 ms
Is viso uztruko: 6611 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 19578 ms
Studentu rikiavimas uztruko: 783 ms
Studentu skaidymas ir irasymas i failus uztruko: 8246 ms
Is viso uztruko: 36521 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3958 ms
Studentu rikiavimas uztruko: 194 ms
Studentu skaidymas ir irasymas i failus uztruko: 1645 ms
Is viso uztruko: 7404 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 20860 ms
Studentu rikiavimas uztruko: 768 ms
Studentu skaidymas ir irasymas i failus uztruko: 8065 ms
Is viso uztruko: 37336 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 3283 ms
Studentu rikiavimas uztruko: 133 ms
Studentu skaidymas ir irasymas i failus uztruko: 1328 ms
Is viso uztruko: 6050 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 20787 ms
Studentu rikiavimas uztruko: 938 ms
Studentu skaidymas ir irasymas i failus uztruko: 8911 ms
Is viso uztruko: 38931 ms

Flag testai:
---------------------------------------------------------------------------------------------
O1 flag, .exe failo dydis: 309 KB
---------------------------------------------------------------------------------------------
studentai100000.txt
Studentu nuskaitymas is failo uztruko: 261 ms
Studentu rikiavimas uztruko: 31 ms
Studentu skaidymas ir irasymas i failus uztruko: 1184 ms
Is viso uztruko: 3311 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1393 ms
Studentu rikiavimas uztruko: 158 ms
Studentu skaidymas ir irasymas i failus uztruko: 9316 ms
Is viso uztruko: 13442 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 319 ms
Studentu rikiavimas uztruko: 22 ms
Studentu skaidymas ir irasymas i failus uztruko: 1481 ms
Is viso uztruko: 2275 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1406 ms
Studentu rikiavimas uztruko: 180 ms
Studentu skaidymas ir irasymas i failus uztruko: 9146 ms
Is viso uztruko: 13562 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 238 ms
Studentu rikiavimas uztruko: 22 ms
Studentu skaidymas ir irasymas i failus uztruko: 1150 ms
Is viso uztruko: 1909 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1671 ms
Studentu rikiavimas uztruko: 208 ms
Studentu skaidymas ir irasymas i failus uztruko: 9555 ms
Is viso uztruko: 15102 ms

O2 flag, .exe failo dydis: 273 KB
---------------------------------------------------------------------------------------------
studentai100000.txt
Studentu nuskaitymas is failo uztruko: 278 ms
Studentu rikiavimas uztruko: 31 ms
Studentu skaidymas ir irasymas i failus uztruko: 1210 ms
Is viso uztruko: 3395 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1385 ms
Studentu rikiavimas uztruko: 217 ms
Studentu skaidymas ir irasymas i failus uztruko: 9109 ms
Is viso uztruko: 13341 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 239 ms
Studentu rikiavimas uztruko: 31 ms
Studentu skaidymas ir irasymas i failus uztruko: 1452 ms
Is viso uztruko: 2166 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1384 ms
Studentu rikiavimas uztruko: 202 ms
Studentu skaidymas ir irasymas i failus uztruko: 8809 ms
Is viso uztruko: 12908 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 247 ms
Studentu rikiavimas uztruko: 33 ms
Studentu skaidymas ir irasymas i failus uztruko: 1376 ms
Is viso uztruko: 2131 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1365 ms
Studentu rikiavimas uztruko: 198 ms
Studentu skaidymas ir irasymas i failus uztruko: 8973 ms
Is viso uztruko: 13254 ms

O3 flag, .exe failo dydis: 318 KB
---------------------------------------------------------------------------------------------
studentai100000.txt
Studentu nuskaitymas is failo uztruko: 240 ms
Studentu rikiavimas uztruko: 24 ms
Studentu skaidymas ir irasymas i failus uztruko: 1286 ms
Is viso uztruko: 3045 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1463 ms
Studentu rikiavimas uztruko: 293 ms
Studentu skaidymas ir irasymas i failus uztruko: 9018 ms
Is viso uztruko: 13703 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 251 ms
Studentu rikiavimas uztruko: 24 ms
Studentu skaidymas ir irasymas i failus uztruko: 1298 ms
Is viso uztruko: 2056 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1362 ms
Studentu rikiavimas uztruko: 179 ms
Studentu skaidymas ir irasymas i failus uztruko: 8984 ms
Is viso uztruko: 13076 ms

studentai100000.txt
Studentu nuskaitymas is failo uztruko: 249 ms
Studentu rikiavimas uztruko: 23 ms
Studentu skaidymas ir irasymas i failus uztruko: 1282 ms
Is viso uztruko: 2034 ms

studentai1000000.txt
Studentu nuskaitymas is failo uztruko: 1403 ms
Studentu rikiavimas uztruko: 179 ms
Studentu skaidymas ir irasymas i failus uztruko: 8881 ms
Is viso uztruko: 13072 ms
