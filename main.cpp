#include <src/FibHeap.h>
#include <iostream>


int main() {
    kstmc::FibonacciHeap<int> fib;
    for (int i = 0; i < 10; ++i) {
        fib.insert(i);
    }
    for (int i = 0; i < 11; ++i) {
        auto ans = fib.getMin();
        std::cout << ans.value_or(-1) << '\n';
        fib.removeMin();
    }
}
