// Test vector performance
#include "../../Vector.h"
#include "../mano_lib.h"

main(){
    vector<int> size = {10000, 100000, 1000000, 10000000, 100000000};

    for(int sz : size){
        
        std::vector<int> v1;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 1; i <= sz; ++i) v1.push_back(i);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "std::vector uztruko: " << duration.count() << " ms" << std::endl;
    
        //////////////////////////////////////////////////////////////////////////////
    
        Vector<int> v2;
        auto start2 = std::chrono::high_resolution_clock::now();
        for (int i = 1; i <= sz; ++i) v2.push_back(i);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
        std::cout << "Vector uztruko: " << duration2.count() << " ms" << std::endl;
    
    }

}
 
