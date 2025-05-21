#include "funkcijos.h"

float Vidurkis(vector<int> pazymiai) {
    if (pazymiai.empty()) {
        throw invalid_argument("Pazymiu sarasas yra tuscias");
    }
    float suma = 0;
    for (int pazymys : pazymiai) {
        suma += pazymys;
    }
    return suma / pazymiai.size();
}

float Mediana(vector<int> pazymiai) {
    if (pazymiai.empty()) {
        throw invalid_argument("Pazymiu sarasas yra tuscias");
    }
    sort(pazymiai.begin(), pazymiai.end());
    int pazSk = pazymiai.size();
    if (pazSk % 2 == 0) {
        return (pazymiai[pazSk / 2 - 1] + pazymiai[pazSk / 2]) / 2.0;
    } else {
        return pazymiai[pazSk / 2];
    }
}

void GeneruotiPazymius(int pazymiuSk, vector<int>& pazymiai) {
    if (pazymiuSk <= 0) {
        throw invalid_argument("Pazymiu skaicius turi buti teigiamas");
    }
    for(int i = 0; i < pazymiuSk; i++){
        pazymiai.push_back(rand() % 10 + 1);
        cout << pazymiai[i] << " ";
    }
    cout << endl;
}

void FailuGeneravimas(int studentuSk, int pazymiuSk) {
    auto startVisas = high_resolution_clock::now();
    ofstream out("studentai" + to_string(studentuSk) + ".txt");
    ostringstream buffer;

    buffer << left << setw(25) << "Vardas" << setw(25) << "Pavarde";
    for (int i = 1; i <= pazymiuSk; i++) {
        buffer << setw(10) << ("ND " + to_string(i));
    }
    buffer << setw(10) << "Egz." << endl;
    out << buffer.str();
    buffer.str(""); // isvalo bufferi

    auto startGeneravimas = high_resolution_clock::now();
    auto totalIrasymasDuration = milliseconds(0);

    // generuoja studentus su pazymiais
    for (int i = 1; i <= studentuSk; i++) {
        
        buffer << left << setw(25) << ("Vardas" + to_string(i)) << setw(25) << ("Pavarde" + to_string(i));
        for (int j = 0; j < pazymiuSk; j++) {
            buffer << setw(10) << (rand() % 10 + 1);
        }
        buffer << setw(10) << (rand() % 10 + 1) << endl;

        if (i % 100000 == 0) { // iraso i faila kas 100000 irasu
            auto startIrasymas = high_resolution_clock::now();
            out << buffer.str();
            buffer.str(""); // isvalo bufferi
            auto endIrasymas = high_resolution_clock::now();
            totalIrasymasDuration += duration_cast<milliseconds>(endIrasymas - startIrasymas);
        }
    }
    auto endGeneravimas = high_resolution_clock::now();
    auto durationGeneravimas = duration_cast<milliseconds>(endGeneravimas - startGeneravimas);

    auto startIrasymas = high_resolution_clock::now();
    // likusius irasom i faila
    out << buffer.str();
    out.close();
    auto endIrasymas = high_resolution_clock::now();
    totalIrasymasDuration += duration_cast<milliseconds>(endIrasymas - startIrasymas);
    
    auto endVisas = high_resolution_clock::now();
    auto durationVisas = duration_cast<milliseconds>(endVisas - startVisas);

    cout << "Studentu generavimas uztruko: " << (durationGeneravimas.count() - totalIrasymasDuration.count()) << " ms" << endl;
    cout << "Studentu irasymas i faila uztruko: " << totalIrasymasDuration.count() << " ms" << endl;
    cout << "Is viso uztruko: " << durationVisas.count() << " ms" << endl;
}

///////////////////////////////////////////////////////////////////////////
void Test1() {
    vector<int> studentuSkaiciai = {1000, 10000, 100000, 1000000, 10000000};
    int pazymiuSk = 10; // pazymiu skaicius
    
    for (int studentuSk : studentuSkaiciai) {
        cout << "Generuojami " << studentuSk << " studentu" << endl;
        
        FailuGeneravimas(studentuSk, pazymiuSk);
       
    }
}

void Test2() {
    vector<string> failai = {"studentai1000.txt", "studentai10000.txt", "studentai100000.txt", "studentai1000000.txt", "studentai10000000.txt"};

    
    for (string failas : failai) {
        cout << failas << endl;
        auto start = high_resolution_clock::now();
        ofstream out;
        
        out.open("rezultatai.txt", ios::trunc | ios::out | ios::binary);
          
        vector<Studentas> studentai;
        NuskaitytiStudentusIsFailo(failas, studentai);
        
        
        out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
        
        // loopina per kiekviena studenta studentu vektoriuje ir skaiciuoja galutini pazymi 
        for (auto& studentas : studentai) {
           
                studentas.setGalutinis(0.4 * Vidurkis(studentas.getPazymiai()) + 0.6 * studentas.getEgzaminas());
        }

        RikiuotiStudentus(studentai, 0);

        // irasoma dalimis, kad neuzimtu per daug atminties
        const size_t chunkSize = 100000; // daliu dydis
        size_t totalStudents = studentai.size();
        for (size_t i = 0; i < totalStudents; i += chunkSize) {
            size_t end = min(i + chunkSize, totalStudents);
            for (size_t j = i; j < end; ++j) {
          
                out << left << setw(15) << studentai[j].getVardas() << setw(20) << studentai[j].getPavarde() << fixed << setprecision(2) << studentai[j].getGalutinis() << endl;
               
            }
        }
        StudentuAtskirimas(studentai);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Is viso uztruko: " << duration.count() << " ms" << endl;
        cout << endl;
    }

}

void Test3() {
    //vector<string> failai = {"studentai1000.txt", "studentai10000.txt", "studentai100000.txt", "studentai1000000.txt", "studentai10000000.txt"};
    vector <string> failai = {"studentai100000.txt", "studentai1000000.txt"};
    for (string failas : failai) {
        cout << failas << endl;
        auto start = high_resolution_clock::now();
        ofstream out;
        
        out.open("rezultatai.txt", ios::trunc | ios::out | ios::binary);
          
        vector<Studentas> studentai;
        //deque<Studentas> studentai;
        //list<Studentas> studentai;
        NuskaitytiStudentusIsFailo(failas, studentai);
        
        
        out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
        
        // loopina per kiekviena studenta studentu vektoriuje ir skaiciuoja galutini pazymi 
        for (auto& studentas : studentai) {
           
                studentas.setGalutinis ( 0.4 * Vidurkis(studentas.getPazymiai()) + 0.6 * studentas.getEgzaminas());
        }

        RikiuotiStudentus(studentai, 3);

        // rasoma dalimis, kad neuzimtu per daug atminties
        const size_t chunkSize = 100000; // daliu dydis
        size_t totalStudents = studentai.size();
        auto it = studentai.begin(); // Initialize an iterator for the list
        
        for (size_t i = 0; i < totalStudents; i += chunkSize) {
            size_t end = min(i + chunkSize, totalStudents);
            for (size_t j = i; j < end; ++j, ++it) { // Increment the iterator directly
                out << left << setw(15) << it->getVardas() << setw(20) << it->getPavarde() << fixed << setprecision(2) << it->getGalutinis() << endl;
            }
        }
        //StudentuAtskirimas(studentai);
        SkaidytiStudentus3Strategija(studentai);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Is viso uztruko: " << duration.count() << " ms" << endl;
        cout << endl;
    }

}

void TestStudentas() {
    vector<int> pazymiai = {8, 9, 10};
    int egzaminas = 9;
    Studentas s("Jonas", "Jonaitis", pazymiai, egzaminas);

    // Tikrinam get/set metodus
    assert(s.getVardas() == "Jonas");
    assert(s.getPavarde() == "Jonaitis");
    assert(s.getPazymiai() == pazymiai);
    assert(s.getEgzaminas() == 9);

    // Tikrinam kopijavimo konstruktorių
    Studentas s2(s);
    assert(s2.getVardas() == "Jonas");
    assert(s2.getPavarde() == "Jonaitis");

    // Tikrinam move konstruktorių
    Studentas s3(std::move(s2));
    assert(s3.getVardas() == "Jonas");
    assert(s3.getPavarde() == "Jonaitis");
    // Neklauskime apie s2 — jis validus, bet nenumatytos būsenos

    // Tikrinam copy assignment
    Studentas s4;
    s4 = s;
    assert(s4.getPavarde() == "Jonaitis");

    // Tikrinam move assignment
    Studentas s5;
    s5 = std::move(s4);
    assert(s5.getVardas() == "Jonas");
    // Nesitikim nieko iš s4

    // Tikrinam operator>>
    stringstream ss("Petras Petraitis 10 8 7 9");
    Studentas s6;
    ss >> s6;
    assert(s6.getVardas() == "Petras");
    assert(s6.getPavarde() == "Petraitis");
    assert(s6.getPazymiai() == vector<int>({10, 8, 7}));
    assert(s6.getEgzaminas() == 9);

    // Tikrinam operator<<
    stringstream out;
    out << s6;
    string result = out.str();
    assert(result.find("Petras") != string::npos);
    assert(result.find("Petraitis") != string::npos);
    assert(result.find("9") != string::npos);  // egzaminas

    cout << "Viskas veikia" << endl;
}
