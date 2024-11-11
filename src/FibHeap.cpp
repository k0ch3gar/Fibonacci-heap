#include "FibHeap.h"
#include <optional>
#include <utility>
#include <iostream>

void kstmc::FibonacciHeap::insert(int64_t value) {
    if (minNode == nullptr) {
        minNode = new Node(value);
        minNode->left = minNode;
        minNode->right = minNode;
        return;
    }

    Node* newNode = new Node(value);
    insertIntoList(minNode, newNode);
    minNode = (minNode->data < newNode->data ? minNode : newNode);
}

void kstmc::FibonacciHeap::insertIntoList(Node* listNode, Node* node) {
    if (listNode == nullptr) {
        listNode = node;

        listNode->left = listNode;

        listNode->right = listNode;
        return;
    }
    Node* prevNode = listNode->left;

    prevNode->right = node;

    node->left = prevNode;
    listNode->left = node;
    node->right = listNode;
    node->parent = listNode->parent;

}


void kstmc::FibonacciHeap::insertChild(Node *parent, Node *child) {
    if (parent->child == nullptr) {
        parent->child = child;

        child->parent = parent;
        child->left = child;
        child->right = child;
        return;
    }
    insertIntoList(parent->child, child);

}


void kstmc::FibonacciHeap::removeFromList(Node* listNode) {
    Node* l = listNode->left;

    Node* r = listNode->right;
    l->right = r;
    r->left = l;
}

void kstmc::FibonacciHeap::cascadeCut(Node *current) {
    if (current == nullptr) return;
    if (current->marked) {
        Node* parent = current->parent;
        current->marked = false;
        cut(current);
        cascadeCut(parent);

        return;
    }
    current->marked = true;
}

kstmc::FibonacciHeap::Node* kstmc::FibonacciHeap::find(Node *currentNode, int64_t val) {
    if (currentNode == nullptr) return nullptr;
    if (currentNode->data == val) return currentNode;
    Node* f = find(currentNode->child, val);
    if (f != nullptr) return f;
    Node* endNode = currentNode;
    Node* current = currentNode->right;
    while (current != endNode) {
        if (current->data == val) return current;
        Node* foundNode = find(current->child, val);
        if (foundNode != nullptr) return foundNode;
        current = current->right;
    }

    return nullptr;
}

void kstmc::FibonacciHeap::cut(Node* currentNode) {

    if (currentNode == nullptr) return;
    --currentNode->parent->degree;
    if (currentNode->right == currentNode) {
        currentNode->parent->child = nullptr;
        removeFromList(currentNode);
        insertIntoList(minNode, currentNode);
        return;
    }
    Node* next = currentNode->right;
    removeFromList(currentNode);
    insertIntoList(minNode, currentNode);
    cut(next);
}

std::optional<int64_t> kstmc::FibonacciHeap::getMin() {
    if (minNode == nullptr) {
        return std::nullopt;

    }
    return minNode->data;
}

void kstmc::FibonacciHeap::decreaseKey(int64_t prevValue, int64_t newValue) {
    Node* foundNode = find(minNode, prevValue);
    if (foundNode == nullptr) return;
    if (foundNode->parent == nullptr) {

        foundNode->data = newValue;
        minNode = minNode->data < newValue ? minNode : foundNode;
        return;

    }

    if (foundNode->parent->data < newValue) {
        foundNode->data = newValue;
        return;
    }


    foundNode->data = newValue;

    Node* parent = foundNode->parent;
    cut(foundNode);
    cascadeCut(parent);
    updateMin();

}


void kstmc::FibonacciHeap::merge(FibonacciHeap &other) {
    if (other.minNode == nullptr) return;
    Node* lMain = minNode;
    Node* rMain = minNode->right;


    Node* lOther = other.minNode;
    Node* rOther = other.minNode->right;

    lMain->right = rOther;
    rOther->left = lMain;


    rMain->left = lOther;
    lOther->right = rMain;

    updateMin();

}


void kstmc::FibonacciHeap::removeMin() {
    if (minNode == nullptr) return;

    cut(minNode->child);

    if (minNode->right == minNode) {
        delete minNode;

        minNode = nullptr;
        return;

    }
    removeFromList(minNode);


    Node* nodeToDelete = minNode;
    minNode = minNode->right;
    delete nodeToDelete;

    Node* currentNode = minNode->right;
    while (currentNode != minNode) {

        Node* next = currentNode->right;
        consolidate(currentNode);
        //std::cout << "b" << '\n';
        currentNode = next;
    }

    updateMin();
    for (auto& x : degreeTree) x = nullptr;

}


void kstmc::FibonacciHeap::consolidate(Node* currentNode) {
    if (degreeTree.at(currentNode->degree) == nullptr) {
        degreeTree.at(currentNode->degree) = currentNode;
        return;
    }
    Node* otherNode = degreeTree.at(currentNode->degree);
    degreeTree.at(currentNode->degree) = nullptr;
    if (currentNode->data > otherNode->data) std::swap(currentNode, otherNode);
    removeFromList(otherNode);
    insertChild(currentNode, otherNode);
    currentNode->degree++;
    consolidate(currentNode);

}


void kstmc::FibonacciHeap::updateMin() {
    Node* currentNode = minNode->right;
    Node* prevMinNode = minNode;
    while (currentNode != prevMinNode) {
        minNode = currentNode->data < minNode->data ? currentNode : minNode;
        currentNode = currentNode->right;
    }
}

