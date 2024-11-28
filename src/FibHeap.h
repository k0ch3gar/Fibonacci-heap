#ifndef FIBONACCIIHEAP_LIBRARY_H
#define FIBONACCIIHEAP_LIBRARY_H
#include <cstdint>
#include <optional>
#include <unordered_set>
#include <expected>
#include <vector>
#include <memory>

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
            std::shared_ptr<Node> left = nullptr;
            std::shared_ptr<Node> right = nullptr;
            std::shared_ptr<Node> firstChild = nullptr;
            std::shared_ptr<Node> lastChild = nullptr;
            std::shared_ptr<Node> parent = nullptr;
            int degree = 0;
            bool marked = false;

            explicit Node(const int data) : data(data) {}
            ~Node() = default;

        };

    private:
        void dfsCopy(std::shared_ptr<Node>& current, std::shared_ptr<FibonacciHeap>& newHeap);

        void appendToList(std::shared_ptr<Node> &firstNode, std::shared_ptr<Node>& lastNode, std::shared_ptr<Node>& newNode);
        void removeFromList(std::shared_ptr<Node> &firstNode, std::shared_ptr<Node>& lastNode, std::shared_ptr<Node>& listNode);

        std::shared_ptr<Node> find(std::shared_ptr<Node>& currentNode, int val);
        void cascadeCut(std::shared_ptr<Node>& current);
        void cut(std::shared_ptr<Node>& childToCut);

        void consolidate(std::shared_ptr<Node> &currentNode);

        int64_t size = 0;
        std::shared_ptr<Node> minNode = nullptr;
        std::shared_ptr<Node> first = nullptr;
        std::shared_ptr<Node> last = nullptr;
        std::vector<std::shared_ptr<Node>> degreeTree = std::vector<std::shared_ptr<Node>>(239, nullptr);
    };
}
#endif //FIBONACCIIHEAP_LIBRARY_H
