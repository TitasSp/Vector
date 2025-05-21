#include "mano_lib.h"
#include "../Vector.h"

void GeneruotiPazymius(int pazymiuSk, Vector<int>& pazymiai);
float Vidurkis(Vector<int> pazymiai);
float Mediana(Vector<int> pazymiai);

// Abstrakti bazinė klasė
class Zmogus {
    protected:
        string vardas;
        string pavarde;
    
    public:
        Zmogus() : vardas(""), pavarde("") {}
        Zmogus(const string& v, const string& p) : vardas(v), pavarde(p) {}
        virtual ~Zmogus() = default;
    
        // virtuali funkcija kad klase butu abstarkti
        virtual void spausdinti() const = 0;
    
        // Getteriai
        string getVardas() const { return vardas; }
        string getPavarde() const { return pavarde; }
    
        // Setteriai
        void setVardas(const string& v) { vardas = v; }
        void setPavarde(const string& p) { pavarde = p; }
    };

class Studentas: public Zmogus {
    private:
       
        Vector<int> pazymiai;
        int egzaminas;
        float galutinis;
    
    public:
        // Constructors
        Studentas() : egzaminas(0), galutinis(0.0f) {} // Default constructor
        Studentas(const string& vardas, const string& pavarde, const Vector<int>& pazymiai, int egzaminas)
            : Zmogus(vardas, pavarde), pazymiai(pazymiai), egzaminas(egzaminas), galutinis(0.0f) {}
    

        // Destructor
        ~Studentas() {
            vardas.clear();
            pavarde.clear();
            pazymiai.clear();
            egzaminas = 0;
            galutinis = 0.0f;
        }
        
         // Copy constructor
        Studentas(const Studentas& other)
            : Zmogus(other.vardas, other.pavarde), pazymiai(other.pazymiai),
                 egzaminas(other.egzaminas), galutinis(other.galutinis) {}
          // Move constructor
        Studentas(Studentas&& other) noexcept
            : Zmogus(move(other.vardas), move(other.pavarde)), pazymiai(move(other.pazymiai)),
                egzaminas(other.egzaminas), galutinis(other.galutinis) {
            other.egzaminas = 0;
            other.galutinis = 0.0f;
            }

            // Copy assignment operator
        Studentas& operator=(const Studentas& other) {
            if (this == &other) return *this; // Self-assignment check
            vardas = other.vardas;
            pavarde = other.pavarde;
            pazymiai = other.pazymiai;
            egzaminas = other.egzaminas;
            galutinis = other.galutinis;
            return *this;
        }

         // Move assignment operator
        Studentas& operator=(Studentas&& other) noexcept {
            if (this == &other) return *this; // Self-assignment check
            vardas = move(other.vardas);
            pavarde = move(other.pavarde);
            pazymiai = move(other.pazymiai);
            egzaminas = other.egzaminas;
            galutinis = other.galutinis;
            other.egzaminas = 0;
            other.galutinis = 0.0f;
            return *this;
        }

        // Getters
        string getVardas() const { return vardas; }
        string getPavarde() const { return pavarde; }
        Vector<int> getPazymiai() const { return pazymiai; }
        Vector<int>& getPazymiaiRef() { return pazymiai; }
        int getEgzaminas() const { return egzaminas; }
        float getGalutinis() const { return galutinis; }
    
        // Setters
        void setVardas(const string& v) { vardas = v; }
        void setPavarde(const string& p) { pavarde = p; }
        void setPazymiai(const Vector<int>& p) { pazymiai = p; }
        void setEgzaminas(int e) { egzaminas = e; }
        void setGalutinis(float g) { galutinis = g; }
    
        void addPazymys(int pazymys) {
            pazymiai.push_back(pazymys);
        }

        // Implementuojame abstrakčią funkciją
        void spausdinti() const override {
            cout << left << setw(15) << vardas << setw(20) << pavarde;

                for (const auto& pazymys : pazymiai) {
                    cout << setw(10) << pazymys;
                }

            cout << setw(10) << egzaminas << fixed << setprecision(2) << galutinis << endl;
        }

        // Input operator
        friend istream& operator>>(istream& in, Studentas& studentas) {
            studentas.pazymiai.clear(); // Clear previous data

            // Read vardas and pavarde
            in >> studentas.vardas >> studentas.pavarde;
            if (in.fail()) return in; // Return if reading failed

            // Read grades and exam score
            int pazymys;
            Vector<int> tempPazymiai;
            while (in >> pazymys) {
                tempPazymiai.push_back(pazymys);
            }

            // Handle the case where no grades or exam score are provided
            if (tempPazymiai.empty()) {
                in.clear(); // Clear fail state
                return in;
            }

            // Treat the last integer as the exam score
            studentas.egzaminas = tempPazymiai.back();
            tempPazymiai.pop_back(); // Remove the exam score from the grades
            studentas.pazymiai = tempPazymiai;

            // Clear the stream state for the next read
            in.clear(); // Clear fail state but do not ignore the next line

            return in;
        }

        // Output operator
    friend ostream& operator<<(ostream& out, const Studentas& studentas) {
        out << left << setw(15) << studentas.vardas
            << setw(20) << studentas.pavarde;
        for (const auto& pazymys : studentas.pazymiai) {
            out << setw(10) << pazymys;
        }
        out << setw(10) << studentas.egzaminas
            << fixed << setprecision(2) << studentas.galutinis;
        return out;
    }
    };


    template <typename Container>
    void GeneruotiStudentus(int studentuSk, Container& studentai) {
        if (studentuSk <= 0) {
            throw invalid_argument("Studentu skaicius turi buti teigiamas");
        }
        Vector<string> vardai = {"Jonas", "Petras", "Antanas", "Tomas", "Marius"};
        Vector<string> pavardes = {"Jonaitis", "Petraitis", "Antanaitis", "Tomaitis", "Maraitis"};
    
        for (int i = 0; i < studentuSk; i++) {
            Studentas studentas;
            studentas.setVardas(vardai[rand() % vardai.size()]);
            studentas.setPavarde(pavardes[rand() % pavardes.size()]);
            
            Vector<int> pazymiai;
            GeneruotiPazymius(rand() % 10 + 1, pazymiai);
            studentas.setPazymiai(pazymiai);
            
            studentas.setEgzaminas(rand() % 10 + 1);
            studentai.push_back(studentas);
        }
    }
    template <typename Container>
    void NuskaitytiStudentusIsFailo(string failas, Container& studentai) {
        auto start = high_resolution_clock::now();

        ifstream in(failas);
        if (!in.is_open()) {
            throw runtime_error("Nepavyko atidaryti failo");
        }

        cout << "Reading file: " << failas << endl;
        string line;
        getline(in, line); // Skip the header line

        if constexpr (is_same<Container, Vector<Studentas>>::value) {
            studentai.reserve(10000000); // Reserve memory for vector or deque
        }

        int studentCount = 0; // Counter to track the number of students read
        while (true) {
            Studentas studentas;
            in >> studentas; // Use input operator
            if (in.fail()) {
                break; // Stop reading if the stream is in a fail state
            }
            studentai.push_back(std::move(studentas)); // Use move semantics
            studentCount++;
        }

        in.close();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Studentu nuskaitymas is failo uztruko: " << duration.count() << " ms" << endl;

        // Print the total number of students read
        cout << "Total students read: " << studentCount << endl; 
    }

template <typename Container>
void RikiuotiStudentus(Container& studentai, int pasirinkimas) {
    auto start = high_resolution_clock::now();

    switch (pasirinkimas) {
        case 0:
            // nerikiuoti
            break;
        case 1:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.getVardas() < b.getVardas();
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.getVardas() < b.getVardas();
                });
            }
            break;
        case 2:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.getPavarde() < b.getPavarde();
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.getPavarde() < b.getPavarde();
                });
            }
            break;
        case 3:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.getGalutinis() < b.getGalutinis();
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.getGalutinis() < b.getGalutinis();
                });
            }
            break;
        case 4:
            if constexpr (is_same<Container, list<Studentas>>::value) {
                studentai.sort([](const Studentas& a, const Studentas& b) {
                    return a.getGalutinis() > b.getGalutinis();
                });
            } else {
                sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.getGalutinis() > b.getGalutinis();
                });
            }
            break;
        default:
            throw invalid_argument("Neteisingas rikiavimo pasirinkimas");
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Studentu rikiavimas uztruko: " << duration.count() << " ms" << endl;
}

template <typename Container>
void SkaiciuotiGalutini(Container& studentai, bool vid) {
    for (auto& studentas : studentai) {
        if (vid) {
            studentas.setGalutinis(0.4 * Vidurkis(studentas.getPazymiai()) + 0.6 * studentas.getEgzaminas());
        } else {
            studentas.setGalutinis(0.4 * Mediana(studentas.getPazymiai()) + 0.6 * studentas.getEgzaminas());
        }
    }
}

template <typename Container>
void StudentuAtskirimas(Container& studentai) {
    ofstream outVargsiukai("stud_b.txt");
    ofstream outKieti("stud_g.txt");

    if (!outVargsiukai.is_open() || !outKieti.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo");
    }

    Vector<Studentas> vargsiukai;
    Vector<Studentas> kieti;

    auto start = high_resolution_clock::now();

    // Separate students into two vectors
    for (const auto& studentas : studentai) {
        if (studentas.getGalutinis() < 5) {
            vargsiukai.push_back(studentas);
        } else {
            kieti.push_back(studentas);
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Studentu suskirstymas uztruko: " << duration.count() << " ms" << endl;

    auto start2 = high_resolution_clock::now();

    // Write "vargsiukai" to file
    outVargsiukai << left << setw(15) << "Vardas" << setw(20) << "Pavarde";
    if (!vargsiukai.empty()) {
        for (size_t i = 1; i <= vargsiukai[0].getPazymiai().size(); i++) {
            outVargsiukai << setw(10) << ("ND " + to_string(i));
        }
    }
    outVargsiukai << setw(10) << "Egz." << endl;

    for (const auto& studentas : vargsiukai) {
        outVargsiukai << left << setw(15) << studentas.getVardas()
                      << setw(20) << studentas.getPavarde();
        for (const auto& pazymys : studentas.getPazymiai()) {
            outVargsiukai << setw(10) << pazymys;
        }
        outVargsiukai << setw(10) << studentas.getEgzaminas() << endl;
    }

    // Write "kieti" to file
    outKieti << left << setw(15) << "Vardas" << setw(20) << "Pavarde";
    if (!kieti.empty()) {
        for (size_t i = 1; i <= kieti[0].getPazymiai().size(); i++) {
            outKieti << setw(10) << ("ND " + to_string(i));
        }
    }
    outKieti << setw(10) << "Egz." << endl;

    for (const auto& studentas : kieti) {
        outKieti << left << setw(15) << studentas.getVardas()
                 << setw(20) << studentas.getPavarde();
        for (const auto& pazymys : studentas.getPazymiai()) {
            outKieti << setw(10) << pazymys;
        }
        outKieti << setw(10) << studentas.getEgzaminas() << endl;
    }

    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end2 - start2);
    cout << "Studentu irasymas i failus uztruko: " << duration2.count() << " ms" << endl;

    outVargsiukai.close();
    outKieti.close();
}

template <typename Container>
void SkaidytiStudentus3Strategija(Container& studentai) {
    auto start = high_resolution_clock::now();
    Container vargsiukai;
    // Naudojame std::partition, kad "vargšiukai" būtų konteinerio gale
    auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& studentas) {
        return studentas.getGalutinis() >= 5; // Use getter
    });

    // Kopijuojame "vargšyku" į naują konteinerį
    vargsiukai.insert(vargsiukai.end(), it, studentai.end());

    // Pašaliname "vargšyku" iš pradinio konteinerio
    studentai.erase(it, studentai.end());

    // Įrašome "vargšyku" į failą
    ofstream outVargsiukai("stud_b.txt");
    if (!outVargsiukai.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo");
    }
    outVargsiukai << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
    for (const auto& studentas : vargsiukai) {
        outVargsiukai << left << setw(15) << studentas.getVardas() << setw(20) << studentas.getPavarde()
                      << fixed << setprecision(2) << studentas.getGalutinis() << endl;
    }
    outVargsiukai.close();

    // Įrašome "kietiakus" į failą
    ofstream outKietiakai("stud_g.txt");
    if (!outKietiakai.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo");
    }
    outKietiakai << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << "Galutinis" << endl;
    for (const auto& studentas : studentai) {
        outKietiakai << left << setw(15) << studentas.getVardas() << setw(20) << studentas.getPavarde()
                     << fixed << setprecision(2) << studentas.getGalutinis() << endl;
    }
    outKietiakai.close();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Studentu skaidymas ir irasymas i failus uztruko: " << duration.count() << " ms" << endl;
}


void FailuGeneravimas(int studentuSk, int pazymiuSk);
void Test1();
void Test2();
void Test3();
void TestStudentas();