#include "header/Vector.h"
#include <iostream>

int main(){
    Vector<int> test;
    int x = 5;
    test.push_back(x);

    Vector<int> test2;
    test2 = std::move(test);


    std::cout << test2.size() << ' ' << test2[0] << '\n';
}