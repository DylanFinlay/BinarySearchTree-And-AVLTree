#ifndef LAB3_AVL_TREE_H
#define LAB3_AVL_TREE_H

#include "binary-search-tree.h"

class AVLTree : public BinarySearchTree {
public:
    // Overriden insert and remove functions
    // Do not modify these definitions


    // The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);


    int depth(Node* n) const;

    bool leftrotation(Node* unbalanced, Node* unblparent);
    bool rightrotation(Node* unbalanced, Node* unblparent);
    bool Balance(DataType val);

    // Define additional functions and attributes below if you need
};

#endif  // LAB3_AVL_TREE_H
