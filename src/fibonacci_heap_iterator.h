#ifndef FIBONACCIHEAP_FIBONACCI_HEAP_ITERATOR_H
#define FIBONACCIHEAP_FIBONACCI_HEAP_ITERATOR_H

#include "fibonacci_heap_node.h"
#include "stack"

namespace kstmc {
template <typename Tp>
    class fibonacci_heap_iterator {
    public:
        typedef fibonacci_heap_iterator iterator;
        typedef fibonacci_heap_node<Tp> node_type;
        typedef node_type* node_pointer;
        typedef node_type::value_type value_type;
        typedef node_type::reference reference;
        typedef node_type::const_reference const_reference;
        typedef node_type::pointer pointer;
        typedef node_type::difference_type difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;

        explicit fibonacci_heap_iterator(node_pointer node) {
            _node = node;
            if (_node->right != nullptr) _next_stack.push(node->right);
            if (_node->firstChild != nullptr) _next_stack.push(node->firstChild);
            if (_node->left != nullptr) _prev_stack.push(node->left);
            if (_node->lastChild != nullptr) _next_stack.push(node->lastChild);
        }

        reference operator*() const {
            return _node->data;
        }

        iterator& operator++() {
            increase();
            return *this;
        }

        iterator& operator++(int) {
            increase();
            return *this;
        }

        iterator& operator--() {
            decrease();
            return *this;
        }

        iterator& operator--(int) {
            decrease();
            return *this;
        }

        bool operator==(const iterator& other) {
            if (this->_next_stack.empty() != other._next_stack.empty()) return false;
            if (this->_prev_stack.empty() != other._prev_stack.empty()) return false;
            if (this->_next_stack.empty()) return true;
            if (this->_prev_stack.empty()) return true;
            return this->_node == other._node;
        }

        bool operator!=(const iterator& other) {
            return this->_node != other._node;
        }

        node_pointer get_node() const {
            return _node;
        }

    private:
        void increase() {
            if (_node != nullptr) _prev_stack.push(_node);
            if (_next_stack.empty()) {
                _node = nullptr;
                return;
            }
            while (_next_stack.top()->lastChild == _node) {
                _node = _next_stack.top();
                _next_stack.pop();
                _prev_stack.push(_node);
            }
            _node = _next_stack.top();
            _next_stack.pop();
            if (_next_stack.empty() || _next_stack.top() != _node->firstChild) {
                if (_node->right != nullptr) _next_stack.push(_node->right);
                if (_node->firstChild != nullptr) _next_stack.push(_node->firstChild);
            }
        }

        void decrease() {
            if (_node != nullptr) _next_stack.push(_node);
            if (_prev_stack.empty()) {
                _node = nullptr;
                return;
            }
            _next_stack.push(_node);
            while (_prev_stack.top()->firstChild == _node) {
                _node = _prev_stack.top();
                _prev_stack.pop();
                _prev_stack.push(_node);
            }
            _node = _prev_stack.top();
            _prev_stack.pop();
            if (_prev_stack.empty() || _prev_stack.top() != _node->lastChild) {
                if (_node->left != nullptr) _prev_stack.push(_node->left);
                if (_node->lastChild != nullptr) _prev_stack.push(_node->lastChild);
            }
        }

        node_pointer _node = nullptr;
        std::stack<node_pointer> _next_stack;
        std::stack<node_pointer> _prev_stack;
    };
}

#endif //FIBONACCIHEAP_FIBONACCI_HEAP_ITERATOR_H