#ifndef _BINARY_SEARCH_TREE_HPP_
#define _BINARY_SEARCH_TREE_HPP_
#include <iostream>

template <class T>
class Node {
public:
    Node(T val) : parent(nullptr), left(nullptr), right(nullptr), data(val) {}

    class Node *parent;
    class Node *left;
    class Node *right;
    T data;
};

template <class T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {}

    void insertNode(T data);
    bool deleteNode(T data);
    void printNode();
    Node<T>* findNode(T data);

private:
    void _printNode(Node<T>* root);
    Node<T> *root;
};

template<class T>
void BinaryTree<T>::insertNode(T val) {
    Node<T> *x = nullptr, *current, *parent;

    // find x's parent
    current = root;
    parent = nullptr;
    while (current) {
        if (val == current->data) return;
        parent = current;
        current = (val < current->data) ? current->left : current->right;
    }
    
    x = new Node<T>(val);
    x->parent = parent;
    
    if (parent) {
        if (x->data < parent->data) parent->left = x;
        else parent->right = x;
    }
    else {
        root = x;
    }
}

template<class T>
bool BinaryTree<T>::deleteNode(T data) {
    Node<T>* pNode = findNode(data);
    if (pNode == nullptr) {
        std::cout << "deleteNode(): Cannot find Node in BST." << std::endl;
        return false;
    }
    
    Node<T>* p = pNode->parent;

    // Case 1: delete node is leaf
    if (pNode->left == nullptr && pNode->right == nullptr) {
        if (p == nullptr) root = nullptr;
        else if (p->left == pNode) p->left = nullptr;
        else if (p->right == pNode) p->right = nullptr;
        delete(pNode);
    } 
    // Case 2: delete node has only one child
    else if (pNode->left == nullptr || pNode->right == nullptr) {
        Node<T>* succ;
        if (pNode->left == nullptr) succ = pNode->right;
        if (pNode->right == nullptr) succ = pNode->left;

        if (p == nullptr) {
            root = succ;
            succ->parent = nullptr;
        }
        else if (p->left == pNode) {
            p->left = succ;
            succ->parent = p;
        }
        else if (p->right == pNode) {
            p->right = succ;
            succ->parent = p;
        }
        delete(pNode);
    }
    // Case 3: delete node has both childs
    else {
        Node<T>* succ;
        succ = pNode->right;
        if (succ->left == nullptr) {
            pNode->data = succ->data;
            succ->parent->right = succ->right;
        }
        else {
            while (succ->left != nullptr) succ = succ->left;
            pNode->data = succ->data;
            succ->parent->left = succ->right;
        }
        if (succ->right) succ->right->parent = succ->parent;
        delete(succ);
    }
    return true;
}

template<class T>
Node<T>* BinaryTree<T>::findNode(T val) {
    Node<T> *current = root;
    while (current != nullptr) {
        if (val == current->data) return current;
        else current = (val < current->data) ? current->left : current->right;
    }
    return nullptr;
}

template<class T>
void BinaryTree<T>::printNode() {
    _printNode(root);
    std::cout << std::endl;
}

template<class T>
void BinaryTree<T>::_printNode(Node<T> *root) {
    if (root == nullptr) return;
    _printNode(root->left);
    std::cout << root->data << " ";
    _printNode(root->right);
}

#endif

