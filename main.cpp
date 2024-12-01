#include <src/fibonacci_heap.h>
#include <iostream>


int main() {
    kstmc::fibonacci_heap<int> fib;
    for (int i = 0; i < 10; ++i) {
        fib.insert(i);
    }
    for (int i : fib) {
        std::cout << i << std::endl;
    }
}
