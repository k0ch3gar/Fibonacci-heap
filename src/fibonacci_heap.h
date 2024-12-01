#ifndef FIBONACCIIHEAP_LIBRARY_H
#define FIBONACCIIHEAP_LIBRARY_H

#include <cstdint>
#include <optional>
#include <unordered_set>
#include <expected>
#include <vector>
#include "fibonacci_heap_node.h"
#include "fibonacci_heap_iterator.h"

namespace kstmc {
    template <
        typename Tp,
        typename Comp = std::less<Tp>,
        typename Alloc = std::allocator<fibonacci_heap_node<Tp>>
    >
    class fibonacci_heap {
    public:
        typedef fibonacci_heap<Tp, Comp> heap_type;
        typedef std::shared_ptr<heap_type> heap_pointer;
        typedef fibonacci_heap_node<Tp> node_type;
        typedef node_type::node_pointer node_pointer;
        typedef node_type::value_type value_type;
        typedef node_type::reference reference;
        typedef node_type::const_reference const_reference;
        typedef node_type::size_type size_type;
        typedef Comp key_compare;
        typedef key_compare value_compare;
        typedef Alloc allocator_type;

        // unimplemented typedefs
        typedef fibonacci_heap_iterator<value_type> iterator;
        typedef node_type insert_return_type;

        typedef const iterator const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        // construct/copy/destroy
        fibonacci_heap() = default;

        fibonacci_heap(const_reference value) {
            insert(value);
        }

        explicit fibonacci_heap(const key_compare comp) {
            _comp = comp;
        }

        template <class InputIterator>
        fibonacci_heap(InputIterator first, InputIterator last, const key_compare& comp = key_compare()) {
            throw std::logic_error("Constructor is unimplemented");
        }

        fibonacci_heap(std::initializer_list<value_type> il, const key_compare& comp = key_compare()) {
            throw std::logic_error("Constructor is unimplemented");
        }

        void swap(heap_type& other) {
            throw std::logic_error("fibonacci::swap method is unimplemented");
        }

        static void swap(heap_type& a, heap_type& b) {
            throw std::logic_error("fibonacci::swap method is unimplemented");
        }

        ~fibonacci_heap() {
            clear();
        }

        // iterators
        iterator begin() {
            return iterator(_first);
        }

        iterator end() {
            return ++iterator(find_last());
        }

        const_iterator begin() const {
            return iterator(_first);
        }

        const_iterator end() const {
            return ++iterator(find_last());
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        const_iterator cbegin() const {
            return begin();
        }

        const_iterator cend() const {
            return end();
        }

        const_reverse_iterator crbegin() const {
            return rbegin();
        }

        const_reverse_iterator crend() const {
            return rend();
        }

        // comparison
        bool operator==(const heap_type& other) const {
            throw std::logic_error("fibonacci::operator== method is unimplemented");
        }

        bool operator!=(const heap_type& other) const {
            throw std::logic_error("fibonacci::operator!= method is unimplemented");
        }

        // observers
        key_compare key_comp() {
            return _comp;
        }

        value_compare value_comp() {
            return _comp;
        }

        allocator_type get_alloc() {
            return _alloc;
        }

        // capacity
        [[nodiscard]] size_type size() const {
            return _size;
        }

        [[nodiscard]] size_type max_size() const {
            return ULONG_MAX;
        }

        [[nodiscard]] bool empty() const {
            return _size == 0;
        }

        // modifiers
        template <class... Args>
        std::pair<iterator, bool> emplace(Args&&... args) {
            throw std::logic_error("fibonacci::emplace method is unimplemented");
        }

        template <class... Args>
        iterator emplace_hint(const_iterator position, Args&&... args) {
            throw std::logic_error("fibonacci::emplace_hint method is unimplemented");
        }
//        should be implemented too, but it conflicts with the original insert method
//        std::pair<iterator, bool> insert(const_reference value) {
//            throw std::logic_error("fibonacci::insert method is unimplemented");
//        }

        void insert(const_reference value) {
            node_pointer newNode = allocate(value);

            if (_size == 1) {
                _first = newNode;
                _last = newNode;
                _minNode = _first;
                return;
            }

            append_to_list(_first, _last, newNode);
            if (_minNode->data > value) _minNode = newNode;
        }

        iterator insert(const_iterator position, const_reference value) {
            throw std::logic_error("fibonacci::insert method is unimplemented");
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last) {
            throw std::logic_error("fibonacci::insert method is unimplemented");
        }

        void insert(std::initializer_list<value_type> il) {
            insert<value_type>(il.begin(), il.end());
        }

        insert_return_type insert(node_type node) {
            throw std::logic_error("fibonacci::insert method is unimplemented");
        }

        iterator insert(const_iterator position, node_type node) {
            throw std::logic_error("fibonacci::insert method is unimplemented");
        }

        node_type extract(const_reference key) {
            throw std::logic_error("fibonacci::extract method is unimplemented");
        }

        node_type extract(const_iterator position) {
            throw std::logic_error("fibonacci::extract method is unimplemented");
        }

        void merge(heap_type& other) {
            throw std::logic_error("fibonacci::merge method not implemented");
        }

        size_type erase(const_reference key) {
            throw std::logic_error("fibonacci::erase method is unimplemented");
        }

        iterator erase(const_iterator position) {
            throw std::logic_error("fibonacci::erase method is unimplemented");
        }

        iterator erase(const_iterator first, const_iterator last) {
            throw std::logic_error("fibonacci::erase method is unimplemented");
        }

        void clear() {
            throw std::logic_error("fibonacci::clear method is unimplemented");
        }

        // operations
        iterator find(const_reference key) {
            throw std::logic_error("fibonacci::find method is unimplemented");
        }

        const_iterator find(const_reference key) const {
            throw std::logic_error("fibonacci::find method is unimplemented");
        }

        size_type count(const_reference key) {
            throw std::logic_error("fibonacci::count method is unimplemented");
        }

        bool contains(const_reference key) {
            throw std::logic_error("fibonacci::contains method is unimplemented");
        }

        iterator lower_bound(const_reference key) {
            throw std::logic_error("fibonacci::lower_bound method is unimplemented");
        }

        const_iterator lower_bound(const_reference key) const {
            throw std::logic_error("fibonacci::lower_bound method is unimplemented");
        }

        iterator upper_bound(const_reference key) {
            throw std::logic_error("fibonacci::upper_bound method is unimplemented");
        }

        const_iterator upper_bound(const_reference key) const {
            throw std::logic_error("fibonacci::upper_bound method is unimplemented");
        }

        std::pair<iterator, iterator> equal_range(const_reference key) {
            throw std::logic_error("fibonacci::equal_range method is unimplemented");
        }

        std::pair<const_iterator, const_iterator> equal_range(const_reference key) const {
            throw std::logic_error("fibonacci::equal_range method is unimplemented");
        }

        // extra
        void remove_min() {
            if (_size == 0) return;

            while (_minNode->firstChild != nullptr) {
                auto child = _minNode->firstChild;
                cut(child);
            }

            if (_size == 1) {
                deallocate(_minNode);
                _first = _last = _minNode = nullptr;
                return;
            }

            remove_from_list(_first, _last, _minNode);
            deallocate(_minNode);
            _minNode = _first;

            auto currentNode = _first;
            while (currentNode != nullptr) {
                auto next = currentNode->right;
                consolidate(currentNode);

                _minNode = (!_comp(_minNode->data, currentNode->data) ? currentNode : _minNode);
                currentNode = next;
            }

            for (auto &x: _degreeTree) x = nullptr;
        }

        std::optional<value_type> get_min() {
            if (_size == 0) {
                return std::nullopt;
            }
            return _minNode->data;
        }

        void decrease_key(const_reference prevValue, const_reference newValue) {
            auto foundNode = find(_first, prevValue);
            if (foundNode == nullptr) return;
            foundNode->data = newValue;
            if (foundNode->parent == nullptr) {
                _minNode = _comp(_minNode->data, newValue) ? _minNode : foundNode;
                return;
            }
            if (foundNode->parent->data < newValue) return;

            auto parent = foundNode->parent;

            cut(foundNode);
            cascade_cut(parent);

            _minNode = _comp(_minNode->data, newValue) ? _minNode : foundNode;
        }

        void copy_to(heap_type& insFibHeap) {
            heap_pointer ptr = std::make_shared<heap_type>(insFibHeap);
            dfs_copy(_first, ptr);
        }

    private:
        // idk if it even is needed
        node_pointer find_last() {
            node_pointer tmp_node = _last;
            while (tmp_node->right != nullptr || tmp_node->lastChild != nullptr) {
                if (tmp_node->right != nullptr) tmp_node = tmp_node->right;
                else tmp_node = tmp_node->lastChild;
            }
            return tmp_node;
        }

        void dfs_copy(node_pointer& current, heap_pointer& newHeap) {
            if (current == nullptr) return;
            newHeap->insert(current->data);
            dfs_copy(current->firstChild, newHeap);
            dfs_copy(current->right, newHeap);
        }

        void append_to_list(node_pointer& firstNode, node_pointer& lastNode, node_pointer& newNode) {
            if (firstNode == nullptr) {
                firstNode = newNode;
                lastNode = newNode;
                firstNode->left = nullptr;
                firstNode->right = nullptr;
                return;
            }

            lastNode->right = newNode;
            newNode->left = lastNode;
            lastNode = newNode;
            newNode->right = nullptr;
            newNode->parent = firstNode->parent;
        }

        void remove_from_list(node_pointer& firstNode, node_pointer& lastNode, node_pointer& listNode) {
            auto l = listNode->left;
            auto r = listNode->right;
            if (l != nullptr) l->right = r;
            else {
                firstNode = firstNode->right;
                if (firstNode) firstNode->left = nullptr;
            }
            if (r != nullptr) r->left = l;
            else {
                lastNode = lastNode->left;
                if (lastNode) lastNode->right = nullptr;
            }
            listNode->right = nullptr;
            listNode->left = nullptr;
        }

        node_pointer find(node_pointer& currentNode, Tp val) {
            if (currentNode == nullptr) return nullptr;
            if (currentNode->data == val) return currentNode;
            auto foundNode = find(currentNode->firstChild, val);
            if (foundNode != nullptr) return foundNode;
            return find(currentNode->right, val);
        }

        void cascade_cut(node_pointer& current) {
            if (current == nullptr) return;
            if (current->marked) {

                auto parent = current->parent;
                cut(current);
                cascade_cut(parent);

                return;
            }
            current->marked = true;
        }

        void cut(node_pointer& childToCut) {
            if (childToCut == nullptr || childToCut->parent == nullptr) return;

            auto parent = childToCut->parent;

            remove_from_list(parent->firstChild, parent->lastChild, childToCut);
            append_to_list(_first, _last, childToCut);

            childToCut->parent = nullptr;
            childToCut->marked = false;
            --parent->degree;
        }

        void consolidate(node_pointer& currentNode) {
            if (_degreeTree.at(currentNode->degree) == nullptr) {
                _degreeTree.at(currentNode->degree) = currentNode;
                return;
            }

            auto otherNode = _degreeTree.at(currentNode->degree);
            _degreeTree.at(currentNode->degree) = nullptr;

            if (currentNode->data > otherNode->data) std::swap(currentNode, otherNode);

            remove_from_list(_first, _last, otherNode);
            append_to_list(currentNode->firstChild, currentNode->lastChild, otherNode);

            otherNode->parent = currentNode;
            currentNode->degree++;
            consolidate(currentNode);
        }

        node_pointer allocate(const_reference value) {
            node_pointer node(_alloc.allocate(1));
            node->data = value;
            ++_size;
            return node;
        }

        void deallocate(node_pointer& node) {
            if (node == nullptr) return;
            _alloc.deallocate(node, 1);
            --_size;
        }

        allocator_type _alloc = allocator_type();
        key_compare _comp = key_compare();
        size_type _size = 0;
        node_pointer _minNode = nullptr;
        node_pointer _first = nullptr;
        node_pointer _last = nullptr;
        std::vector<node_pointer> _degreeTree = std::vector<node_pointer>(239, nullptr);
    };
}

#endif //FIBONACCIIHEAP_LIBRARY_H
