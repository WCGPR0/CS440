#include <initializer_list>
#include <utility>

class MyPairs {
public:
    MyPairs(std::initializer_list<std::pair<char, int> > init) : pairs(init) {}
    
private:
    std::pair<char, int> pairs;
};

int main() {
    
    MyPairs p1{ 
        std::pair<char, int>('a', 1),
        std::pair<char, int>('b', 2)
    };
    
    MyPairs p2{ 
        { 'c',3 }
    };
    
    MyPairs p3{ 
        { 'd',6 },
        { 'e',5 }
    };
}
