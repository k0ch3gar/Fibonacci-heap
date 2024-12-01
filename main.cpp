#include <src/fibonacci_heap.h>
#include <iostream>


int main() {
    kstmc::fibonacci_heap<int> fib;
    for (int i = 0; i < 10; ++i) {
        fib.insert(i);
    }
    for (int i = 0; i < 11; ++i) {
        auto ans = fib.get_min();
        std::cout << ans.value_or(-1) << '\n';
        fib.remove_min();
    }
}
