#ifndef FIBONACCIHEAP_NODE_H
#define FIBONACCIHEAP_NODE_H

#include <memory>

namespace kstmc {
    template<typename Tp>
    struct fibonacci_heap_node {
        typedef fibonacci_heap_node<Tp>* node_pointer;
        typedef uint64_t size_type;
        typedef Tp value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        value_type data;
        node_pointer left = nullptr;
        node_pointer right = nullptr;
        node_pointer firstChild = nullptr;
        node_pointer lastChild = nullptr;
        node_pointer parent = nullptr;
        size_type degree = 0;
        bool marked = false;

        explicit fibonacci_heap_node(const_reference data) : data(data) {}

        ~fibonacci_heap_node() = default;
    };
}

#endif //FIBONACCIHEAP_NODE_H
