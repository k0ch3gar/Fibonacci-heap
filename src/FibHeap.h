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

        FibonacciHeap() { };

        void insert(int value);

        void removeMin();

        std::optional<int> getMin();

        void decreaseKey(int prevValue, int newValue);

        void merge(FibonacciHeap& other);

        void copyTo(FibonacciHeap &insFibHeap);


        struct Node {
            int data;
            Node* left = nullptr;
            Node* right = nullptr;
            Node* firstChild = nullptr;
            Node* lastChild = nullptr;
            Node* parent = nullptr;
            int degree = 0;
            bool marked = false;

            explicit Node(const int data) : data(data) {}
            ~Node() = default;

        };

    private:
        static void dfsCopy(Node* current, FibonacciHeap* newHeap);


        static void appendToList(Node *&firstNode, Node *&lastNode, Node* newNode);

        void cascadeCut(Node* current);

        static Node* find(Node *currentNode, int val);
        void cut(Node* childToCut);

        static void removeFromList(Node *&firstNode, Node *&lastNode, Node *listNode);
        void consolidate(Node *&currentNode);

        int64_t size = 0;
        Node* minNode = nullptr;
        Node* first = nullptr;

        Node* last = nullptr;
        std::vector<Node*> degreeTree = std::vector<Node*>(239, nullptr);
    };
}
#endif //FIBONACCIIHEAP_LIBRARY_H
