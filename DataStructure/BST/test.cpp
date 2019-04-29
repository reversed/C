#include "BSTree.h"

BinaryTree<double> createBST() {
    BinaryTree<double> bt;
    bt.insertNode(0);
    bt.insertNode(2);
    bt.insertNode(3);
    bt.insertNode(7);
    bt.insertNode(1);
    bt.insertNode(-2);
    bt.insertNode(4);
    bt.insertNode(-3);
    bt.insertNode(2.5);
    return bt;
}

int main() {
    BinaryTree<double> bt = createBST();    
    bt.printNode();

    std::cout << "delete 0: " << std::endl;
    bt = createBST();
    bt.deleteNode(0);
    bt.printNode();

    std::cout << "delete 1: " << std::endl;
    bt = createBST();
    bt.deleteNode(1);
    bt.printNode();

    std::cout << "delete 2: " << std::endl;
    bt = createBST();
    bt.deleteNode(2);
    bt.printNode();

    std::cout << "delete 3: " << std::endl;
    bt = createBST();
    bt.deleteNode(3);
    bt.printNode();

    std::cout << "delete -2: " << std::endl;
    bt = createBST();
    bt.deleteNode(-2);
    bt.printNode();

    std::cout << "delete 7, add 1.1, delete 3, add 4.5, delete 0, add 0 " << std::endl;
    bt = createBST();
    bt.deleteNode(7);
    bt.insertNode(1.1);
    bt.deleteNode(3);
    bt.insertNode(4.5);
    bt.deleteNode(0);
    bt.insertNode(0);
    bt.printNode();
    return 0;
}

