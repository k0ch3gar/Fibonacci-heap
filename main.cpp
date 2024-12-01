#include <src/fibonacci_heap.h>
#include <iostream>


int main() {
    kstmc::fibonacci_heap<int> fib;
    for (int i = 0; i < 10; ++i) {
        fib.insert(i);
    }
    kstmc::fibonacci_heap<int>::iterator it = fib.begin();
    kstmc::fibonacci_heap<int>::iterator end = fib.end();
    while (it++ != end) {
        std::cout << *it << std::endl;
    }
}
