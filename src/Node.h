#include <memory>

#ifndef FIBONACCIHEAP_NODE_H
#define FIBONACCIHEAP_NODE_H

namespace kstmc {
    template<typename Tp>
    struct fibonacci_heap_node {
        typedef fibonacci_heap_node<Tp>* node_pointer;
        typedef Tp value_type;
        value_type data;
        node_pointer left = nullptr;
        node_pointer right = nullptr;
        node_pointer firstChild = nullptr;
        node_pointer lastChild = nullptr;
        node_pointer parent = nullptr;
        int degree = 0;
        bool marked = false;

        explicit fibonacci_heap_node(const value_type data) : data(data) {}

        ~fibonacci_heap_node() = default;
    };
}


#endif //FIBONACCIHEAP_NODE_H
