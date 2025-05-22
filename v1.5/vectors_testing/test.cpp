// Test vector performance
#include "../../Vector.h"
#include "../mano_lib.h"

template <typename V>
int count_reallocations(V& vec, size_t N) {
    size_t reallocs = 0;
    size_t old_cap = vec.capacity();

    for (size_t i = 0; i < N; ++i) {
        vec.push_back(static_cast<int>(i));
        if (vec.capacity() != old_cap) {
            ++reallocs;
            old_cap = vec.capacity();
        }
    }

    return reallocs;
}

main(){
    vector<int> size = {10000, 100000, 1000000, 10000000, 100000000};

    for(int sz : size){
        cout << "Irasoma " << sz << " elementu" << endl;
        vector<int> v1;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 1; i <= sz; ++i) v1.push_back(i);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        cout << "std::vector uztruko: " << duration.count() << " ms" << endl;
    
        //////////////////////////////////////////////////////////////////////////////
    
        Vector<int> v2;
        auto start2 = std::chrono::high_resolution_clock::now();
        for (int i = 1; i <= sz; ++i) v2.push_back(i);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
        cout << "Vector uztruko: " << duration2.count() << " ms" << endl;
        cout << endl;
    
    }

    const size_t N = 100000000;

    vector<int> stdvec;
    Vector<int> myvec;

    int std_reallocs = count_reallocations(stdvec, N);
    cout << "std::vector reallocations with 100000000: " << std_reallocs << "\n";

    int my_reallocs = count_reallocations(myvec, N);
    cout << "Vector reallocations with 100000000: " << my_reallocs << "\n";

    return 0;
}
 
