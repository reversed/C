#include "BSTree.h"

int main() {
    BinaryTree<int> bt;    
    bt.insertNode(0);
    bt.insertNode(2);
    bt.insertNode(3);
    bt.insertNode(7);
    bt.insertNode(1);
    bt.insertNode(-2);
    bt.printNode();

    if (bt.findNode(-2) != nullptr) std::cout << "found -2" << std::endl;
    else std::cout << "not found -2" << std::endl;
    if (bt.findNode(-3) == nullptr) std::cout << "not found -3" << std::endl;
    else std::cout << "found -3" << std::endl;

    return 0;
}

