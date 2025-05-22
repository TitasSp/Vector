#include "mano_lib.h"
#include "funkcijos.h"
#include "../Vector.h"

int main() {
    
    //TestStudentas(); // testuoja Studentas klase


    try {
        Vector<Studentas> studentai; 

        int konteinerioTipas; 
        cout << "Pasirinkite konteinerio tipa(1 - deque, 2 - list, 3 - vector):\n";
        cin >> konteinerioTipas;
        if (konteinerioTipas == 1) {
            cout << "Naudojamas deque" << endl;
            deque<Studentas> studentai; 
        } else if (konteinerioTipas == 2) {
            cout << "Naudojama list" << endl;
            list<Studentas> studentai;
        } else {
            cout << "Naudojamas vector" << endl;
            Vector<Studentas> studentai; 
        }
    
        auto start = std::chrono::high_resolution_clock::now(); // Start timer
        std::chrono::duration<double> inputWaitDuration(0); // input laukimo laikas
        
        srand(time(0)); // inicializuoja random seeda
        int vid; // ar naudoti vidurki ar mediana
        int iFaila; // ar isvesti i faila
       
        int pasirinkimas;
        int pazymiuSk;
        string failas;
        stringstream buffer;

        while (true) {
            auto inputStart = std::chrono::high_resolution_clock::now(); // pradeda input laukimo laiko skaiciavima
            cout << "Pasirinkite veiksma:\n";
            cout << "1 - Ivesti viska ranka\n";
            cout << "2 - Generuoti pazymius\n";
            cout << "3 - Generuoti ir pazymius ir studentu vardus, pavardes\n";
            cout << "4 - Nuskaityti studentus is failo\n";
            cout << "5 - Baigti darba\n";
            cin >> pasirinkimas;
            inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

            // patikrina ar ivestas skaicius ir ar jis yra tarp 1 ir 5
            try {
                if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 5) {
                    throw invalid_argument("Neteisingas pasirinkimas");
                }
            } catch (invalid_argument& e) {
                cerr << "Ivyko klaida: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (pasirinkimas == 5) break;

            if (pasirinkimas == 1 || pasirinkimas == 2) {
                Studentas studentas;
                auto inputStart = std::chrono::high_resolution_clock::now(); // pratina input laukimo laika
                cout << "Iveskite studento varda: ";
                string vardas;
                cin >> vardas;
                studentas.setVardas(vardas);
                cout << "Iveskite studento pavarde: ";
                string pavarde;
                cin >> pavarde;
                studentas.setPavarde(pavarde);
                inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

                if (pasirinkimas == 1) {
                    int pazymys;
                    while (true) {
                        auto inputStart = std::chrono::high_resolution_clock::now(); // pradeda input laukimo laika
                        cout << "Iveskite pazymi (iveskite -1 norint baigti): ";
                        cin >> pazymys;
                        inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

                        //tikrinam ar ivestas skaicius ir ar jis yra tarp -1 ir 10
                        if (cin.fail() || pazymys < -1 || pazymys > 10) {
                            cout << "Ivyko klaida: netinkama ivestis " << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (pazymys == -1) break;

                        studentas.addPazymys(pazymys);
                    }
                } else {
                    while (true) {
                        try {
                            auto inputStart = std::chrono::high_resolution_clock::now(); // pradeda input laukimo laika
                            cout << "Iveskite pazymiu skaiciu: ";
                            cin >> pazymiuSk;
                            inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

                            if (cin.fail() || pazymiuSk <= 0) {
                                throw invalid_argument("Neteisinga ivestis");
                            }
                            GeneruotiPazymius(pazymiuSk, studentas.getPazymiaiRef());
                            break;
                        } catch (const invalid_argument& e) {
                            cerr << "Ivyko klaida: " << e.what() << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                    }
                }

                while (true) {
                    try {
                        auto inputStart = std::chrono::high_resolution_clock::now(); // pradeda input laukimo laika
                        cout << "Iveskite studento egzamino pazymi: ";
                        int egzaminas;
                        cin >> egzaminas;
                        studentas.setEgzaminas(egzaminas);
                        inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // pridea input laukimo laika

                        if (cin.fail() || studentas.getEgzaminas() < 0 || studentas.getEgzaminas() > 10) {
                            throw invalid_argument("Neteisinga ivestis");
                        }
                        studentai.push_back(studentas);
                        break;
                    } catch (const invalid_argument& e) {
                        cerr << "Ivyko klaida: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                }

            } else if (pasirinkimas == 3) {
                while (true) {
                    try {
                        auto inputStart = std::chrono::high_resolution_clock::now(); // pradeda input laukimo laika
                        cout << "Generuoti studentus i faila? (1 - taip, 0 - ne): ";
                        int iFaila;
                        cin >> iFaila;
                        inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

                        if (cin.fail() || iFaila < 0 || iFaila > 1) {
                            throw invalid_argument("Neteisinga ivestis");
                        }
                        cout << "Iveskite studentu skaiciu: ";
                        int studentuSk;
                        cin >> studentuSk;
                        inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

                        if (cin.fail() || studentuSk <= 0) {
                            throw invalid_argument("Neteisinga ivestis");
                        }

                        if (iFaila) {
                            cout << "Iveskite pazymiu skaiciu: ";
                            cin >> pazymiuSk;
                            if (cin.fail() || pazymiuSk <= 0) {
                                throw invalid_argument("Neteisinga ivestis");
                            }
                            FailuGeneravimas(studentuSk, pazymiuSk);
                        } else {
                            GeneruotiStudentus(studentuSk, studentai);
                        }
                        break;
                    } catch (const invalid_argument& e) {
                        cerr << "Ivyko klaida: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
            } else if (pasirinkimas == 4) {
                while (true) {
                    auto inputStart = std::chrono::high_resolution_clock::now(); // pradeda input laukimo laika
                    cout << "Failai: " << endl;
                    system("dir /b *.txt");
                    cout << endl;
                    cout << "Iveskite failo pavadinima: ";
                    cin >> failas;
                    inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

                    ifstream in(failas);
                    if (!in.is_open()) {
                        cerr << "Nepavyko atidaryti failo" << endl;
                        continue;
                    }
                    in.close();
                    break;
                }

                NuskaitytiStudentusIsFailo(failas, studentai);
            }
        }

        while (true) {
            auto inputStart = std::chrono::high_resolution_clock::now(); // pradeda input laukimo laika
            cout << "Iveskite 1 jei norite skaiciuoti vidurki, 0 jei norite skaiciuoti mediana: ";
            cin >> vid;
            inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

            if (cin.fail() || vid < 0 || vid > 1) {
                cout << "Ivyko klaida: netinkama ivestis " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }

        while (true) {
            auto inputStart = std::chrono::high_resolution_clock::now(); // pradeda input laukimo laika
            cout << "Isvesti atsakymus i faila? (1 - taip, 0 - ne): ";
            cin >> iFaila;
            inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

            if (cin.fail() || iFaila < 0 || iFaila > 1) {
                cout << "Ivyko klaida: netinkama ivestis " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }

        ofstream out;
        if (iFaila) {
            out.open("rezultatai.txt", ios::trunc | ios::out | ios::binary);
            if (!out) {
                cerr << "Nepavyko atidaryti failo rasymui" << endl;
                return 1;
            }
        }

        int rikiavimoPasirinkimas;
        while (true) {
            try {
                auto inputStart = std::chrono::high_resolution_clock::now(); // pradeda input laukimo laika
                cout << "Pasirinkite rikiavimo buda:\n";
                cout << "0 - Nerikiuoti\n";
                cout << "1 - Pagal varda\n";
                cout << "2 - Pagal pavarde\n";
                cout << "3 - Pagal galutini pazymi didejancia tvarka\n";
                cout << "4 - Pagal galutini pazymi mazejancia tvarka\n";
                cin >> rikiavimoPasirinkimas;
                inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

                if (cin.fail() || rikiavimoPasirinkimas < 0 || rikiavimoPasirinkimas > 4) {
                    throw invalid_argument("Neteisinga ivestis");
                }
                break;
            } catch (const invalid_argument& e) {
                cerr << "Ivyko klaida: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }

        if (iFaila) {
            out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
        } else {
            cout << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
        }

        // loopina per kiekviena studenta studentu konteinery ir skaiciuoja galutini pazymi 
        SkaiciuotiGalutini(studentai, vid);

        RikiuotiStudentus(studentai, rikiavimoPasirinkimas);

        // irasoma dalimis, kad neuzimtu per daug atminties
        const size_t chunkSize = 100000; // daliu dydis
        size_t totalStudents = studentai.size();
        auto it = studentai.begin();
        for (size_t i = 0; i < totalStudents; i += chunkSize) {
            size_t end = min(i + chunkSize, totalStudents);
            for (size_t j = i; j < end; ++j, ++it) {
                if (iFaila) {
                    out << left << setw(15) << it->getVardas() << setw(20) << it->getPavarde() << fixed << setprecision(2) << it->getGalutinis() << endl;
                } else {
                    cout << left << setw(15) << it->getVardas() << setw(20) << it->getPavarde() << fixed << setprecision(2) << it->getGalutinis() << endl;
                }
            }
        }

        if (iFaila) {
            bool suskirstyti;
            auto inputStart = std::chrono::high_resolution_clock::now(); // pradeda input laukimo laika
            cout << "Suskirtyti studentus i dvi grupes, pagal pazymius?(1  - taip, 0 - ne) ";
            cin >> suskirstyti;
            inputWaitDuration += std::chrono::high_resolution_clock::now() - inputStart; // prideda input laukimo laika

            if (suskirstyti) {
                StudentuAtskirimas(studentai);
            }
            system("notepad rezultatai.txt");
            out.close();
        }
        auto end = std::chrono::high_resolution_clock::now(); // baigia laiko skaiciavima
        std::chrono::duration<double> duration = end - start - inputWaitDuration; // atema input laukimo laika
       // cout << "Programos vykdymo trukme (be input laukimo): " << duration.count() << " sekundes" << endl;
       
    // pagauna klaida
    } catch (const exception& e) {
        cerr << "Ivyko klaida: " << e.what() << endl;
    }
    return 0;
}