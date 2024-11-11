#ifndef FIBONACCIIHEAP_LIBRARY_H
#define FIBONACCIIHEAP_LIBRARY_H
#include <cstdint>
#include <optional>
#include <unordered_set>
#include <expected>
#include <vector>


namespace kstmc {
    class FibonacciHeap {
    public:
        void insert(int64_t value);


        void removeMin();

        std::optional<int64_t> getMin();


        void decreaseKey(int64_t prevValue, int64_t newValue);


        void merge(FibonacciHeap& other);

        struct Node {
            int64_t data;
            Node* left = nullptr;
            Node* right = nullptr;
            Node* child = nullptr;
            Node* parent = nullptr;
			int64_t degree = 0;
            bool marked = false;

            Node(int64_t data) : data(data) {
            }
        };

    private:
        void cascadeCut(Node* current);
        Node* find(Node *currentNode, int64_t val);
        void cut(Node* currentNode);
        void insertIntoList(Node* listNode, Node* node);
        void insertChild(Node* parent, Node* child);
        void removeFromList(Node* listNode);
        void consolidate(Node* currentNode);
        void updateMin();


        Node *minNode = nullptr;
        std::vector<Node*> degreeTree = std::vector<Node*>(239, nullptr);
    };
}

#endif //FIBONACCIIHEAP_LIBRARY_H
