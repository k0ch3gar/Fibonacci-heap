#ifndef FIBONACCIIHEAP_LIBRARY_H
#define FIBONACCIIHEAP_LIBRARY_H
#include <cstdint>
#include <optional>
#include <unordered_set>
#include <expected>
#include <vector>
#include <memory>
#include "Node.h"

namespace kstmc {
    template <
        typename Tp,
        typename Comp = std::less<Tp>
    >
    class FibonacciHeap {
    public:
        typedef FibonacciHeap<Tp, Comp> heap_type;
        typedef std::shared_ptr<heap_type> heap_pointer;
        typedef Tp value_type;
        typedef Comp key_compare;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef unsigned long size_type;
        typedef Node<Tp> node_type;
        typedef node_type* node_pointer;
        typedef std::allocator<Node<Tp>> allocator_type;

        FibonacciHeap() { };

        void insert(value_type value) {
            node_pointer newNode = allocate(value);

            if (size == 1) {
                first = newNode;
                last = newNode;
                minNode = first;
                return;
            }

            appendToList(first, last, newNode);
            if (minNode->data > value) minNode = newNode;
        }

        void removeMin() {
            if (size == 0) return;

            while (minNode->firstChild != nullptr) {
                auto child = minNode->firstChild;
                cut(child);
            }

            if (size == 1) {
                deallocate(minNode);
                first = last = minNode = nullptr;
                return;
            }

            removeFromList(first, last, minNode);
            deallocate(minNode);
            minNode = first;

            auto currentNode = first;
            while (currentNode != nullptr) {
                auto next = currentNode->right;
                consolidate(currentNode);

                minNode = (comparator(minNode->data, currentNode->data) ? currentNode : minNode);
                currentNode = next;
            }

            for (auto &x: degreeTree) x = nullptr;
        }

        std::optional<value_type> getMin() {
            if (size == 0) {
                return std::nullopt;
            }
            return minNode->data;
        }

        void decreaseKey(value_type prevValue, value_type newValue) {
            auto foundNode = find(first, prevValue);
            if (foundNode == nullptr) return;
            foundNode->data = newValue;
            if (foundNode->parent == nullptr) {
                minNode = comparator(minNode->data, newValue) ? minNode : foundNode;
                return;
            }
            if (foundNode->parent->data < newValue) return;

            auto parent = foundNode->parent;

            cut(foundNode);
            cascadeCut(parent);

            minNode = comparator(minNode->data, newValue) ? minNode : foundNode;
        }

        // костя сделай
        void merge(heap_type& other);

        void copyTo(heap_type &insFibHeap) {
            heap_pointer ptr = std::make_shared<heap_type>(insFibHeap);
            dfsCopy(first, ptr);
        }

    private:
        void dfsCopy(node_pointer& current, heap_pointer & newHeap) {
            if (current == nullptr) return;
            newHeap->insert(current->data);
            dfsCopy(current->firstChild, newHeap);
            dfsCopy(current->right, newHeap);
        }
        void appendToList(node_pointer& firstNode, node_pointer& lastNode, node_pointer& newNode) {
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
        void removeFromList(node_pointer& firstNode, node_pointer& lastNode, node_pointer& listNode) {
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
        void cascadeCut(node_pointer& current) {
            if (current == nullptr) return;
            if (current->marked) {

                auto parent = current->parent;
                cut(current);
                cascadeCut(parent);

                return;
            }
            current->marked = true;
        }
        void cut(node_pointer& childToCut) {
            if (childToCut == nullptr || childToCut->parent == nullptr) return;

            auto parent = childToCut->parent;

            removeFromList(parent->firstChild, parent->lastChild, childToCut);
            appendToList(first, last, childToCut);

            childToCut->parent = nullptr;
            childToCut->marked = false;
            --parent->degree;
        }
        void consolidate(node_pointer &currentNode) {
            if (degreeTree.at(currentNode->degree) == nullptr) {
                degreeTree.at(currentNode->degree) = currentNode;
                return;
            }

            auto otherNode = degreeTree.at(currentNode->degree);
            degreeTree.at(currentNode->degree) = nullptr;

            if (currentNode->data > otherNode->data) std::swap(currentNode, otherNode);

            removeFromList(first, last, otherNode);
            appendToList(currentNode->firstChild, currentNode->lastChild, otherNode);

            otherNode->parent = currentNode;
            currentNode->degree++;
            consolidate(currentNode);
        }
        node_pointer allocate(value_type value) {
            node_pointer node = allocator.allocate(1);
            node->data = value;
            ++size;
            return node;
        }
        void deallocate(node_pointer node) {
            if (node == nullptr) return;
            allocator.deallocate(node, 1);
            --size;
        }

        allocator_type allocator = allocator_type();
        key_compare comparator = key_compare();
        int64_t size = 0;
        node_pointer minNode = nullptr;
        node_pointer first = nullptr;
        node_pointer last = nullptr;
        std::vector<node_pointer> degreeTree = std::vector<node_pointer>(239, nullptr);
    };
}
#endif //FIBONACCIIHEAP_LIBRARY_H
