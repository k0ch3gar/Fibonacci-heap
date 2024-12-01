#include <src/fibonacci_heap.h>
#include <iostream>


int main() {
    kstmc::fibonacci_heap<int> fib;
    for (int i = 0; i < 100; ++i) {
        fib.insert(i);
    }
    for (auto i : fib) {
        std::cout << i << std::endl;
    }
}
