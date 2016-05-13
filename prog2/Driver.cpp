#include "Map.hpp"

int main(int argc, char* argv[]) {
//Map<int, double> int_double_map {{1, 1.0}, {3, 5.67}, {13, 6.9}};
    cs540::Map<int, int> m;
    m.insert({10, 10});
    m.insert({3, 3});
    m.insert({20, 20});
    m.insert({15, 15}); 

    cs540::Map<int, int>::Iterator it = m.begin();
    while (true) { //(it != m.end()) { 
    std::cout << (*it).first << " " << (*it).second << std::endl;
    ++it;
    }

   std::cout << "word frequency:\n";
    for (auto& count : m) { // uses .begin() and .end()
        std::cout << count.first << ": " << count.second << '\n';
    }	
return 0;
}
