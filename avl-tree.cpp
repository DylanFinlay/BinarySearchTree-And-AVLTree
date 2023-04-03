#include "avl-tree.h";
#include <cstdlib>
#include <algorithm>
#include <iostream>


bool AVLTree::insert(DataType val) {
    BinarySearchTree::insert(val);
    Balance(val);
    return true;

}

bool AVLTree::remove(DataType val) {
    BinarySearchTree::remove(val);
    Balance(val);
    return true;
    
}

int AVLTree::depth(Node* n) const {
    if(n == nullptr)
        return 0;
    else if (n->left == nullptr && n->right == nullptr)
        return 1;
    else{
        return 1 + std::max(depth(n->left), depth(n->right));
    }
}


bool AVLTree::leftrotation(Node *unbalanced, Node *unblparent) {
    Node* unblchild = nullptr;

    //Setting unbalanced child
    if (depth(unbalanced->left) > depth(unbalanced->right))
        unblchild = unbalanced->left;

    else
        unblchild = unbalanced->right;

    if(unblparent == nullptr){
        Node** rootTemp = getRootNodeAddress();

        unbalanced->right = unblchild->left;
        unblchild->left = unbalanced;
        *rootTemp = unblchild;

        return true;
    }

    //Making rotation
    unbalanced->right = unblchild->left;
    unblchild->left = unbalanced;

    if (unblparent->left == unbalanced)
        unblparent->left = unblchild;
    else
        unblparent->right = unblchild;

    return true;
}


bool AVLTree::rightrotation(Node *unbalanced, Node *unblparent) {
    Node* unblchild = nullptr;

    //Setting unbalanced child
    if (depth(unbalanced->left) > depth(unbalanced->right))
        unblchild = unbalanced->left;

    else
        unblchild = unbalanced->right;


    if (unblparent == nullptr){
        Node** rootTemp = getRootNodeAddress();

        unbalanced->left = unblchild->right;
        unblchild->right = unbalanced;
        *rootTemp = unblchild;

        return true;
    }


    //Making rotation
    unbalanced->left = unblchild->right;
    unblchild->right = unbalanced;

    if (unblparent->left == unbalanced)
        unblparent->left = unblchild;
    else
        unblparent->right = unblchild;

    return true;
}

bool AVLTree::Balance(DataType val) {

    Node* current = BinarySearchTree::getRootNode();
    Node* prev = nullptr;

    Node* unbalanced = nullptr;
    Node* parent = nullptr;
    Node* child = nullptr;
    Node* grandChild = nullptr;

    //going from root to new value
    while (current!=nullptr){

        //Current will cycle through all the way to the new insert. Unbalanced will be set to the closest unbalanced node to the new node

        if (abs(depth(current->left) - depth(current->right))==2) {
            unbalanced = current;
            parent = prev;
        }

        //Setting prev and current so that they cycle all the way through to new node
        prev = current;

        if (val>current->val){
            current = current->right;
        }
        else {
            current = current->left;
        }
    }

    //if there is no unbalanced node then we are done
    if (unbalanced == nullptr)
        return true;


    //setting child needed for left-right or right-left rotations
    if (depth(unbalanced->left) > depth(unbalanced->right))
        child = unbalanced->left;

    else
        child = unbalanced->right;


    //setting grandchild needed for comparisons since we don't have proper value when removing
    if (depth(child->left) > depth(child->right))
        grandChild = child->left;

    else
        grandChild = child->right;


    //right rotation
    if (grandChild->val < unbalanced->val && grandChild->val < child->val){
        rightrotation(unbalanced, parent);
    }

    //left rotation
    else if (grandChild->val > unbalanced->val && grandChild->val > child->val){
        leftrotation(unbalanced, parent);
    }

    //left right rotation
    else if (grandChild->val < unbalanced->val && grandChild->val > child->val){
        leftrotation(child, unbalanced);
        rightrotation(unbalanced, parent);
    }

    //right left rotation
    else {
        rightrotation(child, unbalanced);
        leftrotation(unbalanced, parent);
    }

    return true;

}