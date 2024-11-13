#include "FibHeap.h"

void kstmc::FibonacciHeap::insert(int value) {
    Node* newNode = new Node(value);

    if (size == 0) {
        ++size;
        first = newNode;
        last = newNode;
        minNode = first;
        return;
    }

    ++size;
    appendToList(first, last, newNode);
    if (minNode->data > value) minNode = newNode;
}

void kstmc::FibonacciHeap::removeFromList(Node *&firstNode, Node *&lastNode, Node *listNode) {

    Node* l = listNode->left;
    Node* r = listNode->right;
    if (l != nullptr) l->right = r;
    else {
        firstNode = firstNode->right;
        if (firstNode) firstNode->left = nullptr;
    }
    if (r != nullptr) r->left = l;
    else {
        lastNode = lastNode->left;
        if(lastNode) lastNode->right = nullptr;
    }
    listNode->right = nullptr;

    listNode->left = nullptr;
}

void kstmc::FibonacciHeap::cascadeCut(Node *current) {
    if (current == nullptr) return;
    if (current->marked) {

        Node* parent = current->parent;
        cut(current);
        cascadeCut(parent);

        return;
    }
    current->marked = true;
}

kstmc::FibonacciHeap::Node* kstmc::FibonacciHeap::find(Node *currentNode, int val) {
    if (currentNode == nullptr) return nullptr;
    if (currentNode->data == val) return currentNode;
    Node* foundNode = find(currentNode->firstChild, val);
    if (foundNode != nullptr) return foundNode;
    return find(currentNode->right, val);
}

void kstmc::FibonacciHeap::cut(Node* childToCut) {
    if (childToCut == nullptr || childToCut->parent == nullptr) return;

    Node* parent = childToCut->parent;


    removeFromList(parent->firstChild, parent->lastChild, childToCut);
    appendToList(first, last, childToCut);

    childToCut->parent = nullptr;
    childToCut->marked = false;


    --parent->degree;
}

std::optional<int> kstmc::FibonacciHeap::getMin() {

    if (size == 0) {
        return std::nullopt;
    }
    return minNode->data;
}

void kstmc::FibonacciHeap::decreaseKey(int prevValue, int newValue) {
    Node* foundNode = find(first, prevValue);
    if (foundNode == nullptr) return;
    foundNode->data = newValue;
    if (foundNode->parent == nullptr) {
        minNode = minNode->data < newValue ? minNode : foundNode;

        return;
    }
    if (foundNode->parent->data < newValue) return;


    Node* parent = foundNode->parent;

    cut(foundNode);
    cascadeCut(parent);

    minNode = minNode->data < newValue ? minNode : foundNode;
}

void kstmc::FibonacciHeap::dfsCopy(kstmc::FibonacciHeap::Node* current, kstmc::FibonacciHeap* newHeap) {
    while (current == nullptr) return;
    newHeap->insert(current->data);
    dfsCopy(current->firstChild, newHeap);
    dfsCopy(current->right, newHeap);
}

void kstmc::FibonacciHeap::appendToList(Node *&firstNode, Node *&lastNode, Node *newNode) {
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

void kstmc::FibonacciHeap::copyTo(FibonacciHeap &insFibHeap) {
    dfsCopy(first, &insFibHeap);
}

void kstmc::FibonacciHeap::removeMin() {
    if (size == 0) return;

    while (minNode->firstChild != nullptr) {
        auto child = minNode->firstChild;
        cut(child);
    }

    if (size == 1) {
        --size;
        delete minNode;
        first = last = minNode = nullptr;
        return;
    }

    --size;

    removeFromList(first, last, minNode);
    delete minNode;
    minNode = first;

    auto currentNode = first;
    while (currentNode != nullptr) {
        Node* next = currentNode->right;
        consolidate(currentNode);

        minNode = (currentNode->data <= minNode->data ? currentNode : minNode);
        currentNode = next;
    }

    for (auto& x : degreeTree) x = nullptr;
}

void kstmc::FibonacciHeap::consolidate(Node *&currentNode) {

    if (degreeTree.at(currentNode->degree) == nullptr) {
        degreeTree.at(currentNode->degree) = currentNode;
        return;
    }


    Node* otherNode = degreeTree.at(currentNode->degree);
    degreeTree.at(currentNode->degree) = nullptr;

    if (currentNode->data > otherNode->data) std::swap(currentNode, otherNode);

    removeFromList(first, last, otherNode);
    appendToList(currentNode->firstChild, currentNode->lastChild, otherNode);

    otherNode->parent = currentNode;
    currentNode->degree++;
    consolidate(currentNode);
}

