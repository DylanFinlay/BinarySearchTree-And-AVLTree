#include "binary-search-tree.h"
#include <algorithm>
#include <queue>
#include <iostream>
#include <stack>

using namespace std;


BinarySearchTree::Node::Node(DataType newval) {
    val = newval;
    left = nullptr;
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if(n == nullptr)
        return -1;
    else if (n->left == nullptr && n->right == nullptr)
        return 0;
    else{
        return 1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right));
    }
}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;

}

BinarySearchTree::~BinarySearchTree() {
    if(root_ == nullptr) {
        std::cout << "Tree is empty." << '\n';
        return;
    }
    std::queue <Node*> Q;
    Q.push(root_);
    while (!Q.empty()) {
        Node *P = Q.front();
        if (P->left != nullptr) Q.push(P->left);
        if (P->right != nullptr) Q.push(P->right);
        Q.pop();
        delete P;
    }
    std::cout << '\n' ;

}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    Node* current = root_;
    while(current-> right != nullptr){
        current = current->right;
    }
    return current->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node* current = root_;
    while(current-> left != nullptr){
        current = current->left;
    }
    return current->val;
}

unsigned int BinarySearchTree::depth() const {
    unsigned int depth = getNodeDepth(root_);
    return depth;
}

void BinarySearchTree::print() const {
    if(root_ == nullptr) {
        std::cout << "Tree is empty." << '\n';
        return;
    }
    std::queue <Node*> Q;
    Q.push(root_);
    while (!Q.empty()) {
        Node *P = Q.front();
        Q.pop();
        std::cout<< P->val<<", ";
        if (P->left != nullptr) Q.push(P->left);
        if (P->right != nullptr) Q.push(P->right);
    }
    std::cout << '\n';


 //print using inorder
//    Node* temp = root_;
//    stack<Node*> st;
//    while ( temp!= nullptr || !st.empty() ){
//        if (temp != nullptr) {
//            st.push(temp);
//            temp = temp->left;
//        }
//        else {
//            temp = st.top();
//            st.pop();
//            std::cout<<temp->val << " ";
//            temp = temp->right;
//        }
//    }
}

bool BinarySearchTree::exists(DataType val) const {
    Node* current = root_;
    while(current!=nullptr){
        if (current->val == val)
            return true;
        else if (val>current->val)
            current = current->right;
        else
            current = current->left;
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    Node** address = &root_;
    return address;
}

bool BinarySearchTree::insert(DataType val) {
    if (exists(val)) {
        return false;
    }

    Node* NewNode = new Node(val);

    if (root_ == nullptr) {
        root_ = NewNode;
        size_ = 1;
        return true;
    }

    Node* current = root_;
    Node* prev = nullptr;

    while(current!=nullptr){
        prev = current;
        if (val>current->val)
            current = current->right;
        else
            current = current->left;
    }

    if (val > prev->val){
        prev->right = NewNode;
    }
    else if (val < prev->val){
        prev->left = NewNode;
    }

    size_ ++;
    return true;

}

bool BinarySearchTree::remove(DataType val) {
    if (exists(val) == false)
        return false;

    Node* current = root_;
    Node* prev = nullptr;

    while(current!=nullptr && current->val != val){
        prev = current;
        if (val>current->val)
            current = current->right;
        else
            current = current->left;
    }

    if (current->left == nullptr && current->right == nullptr){
        if(current == root_){
            delete root_;
            root_ = nullptr;
        }

        else if (prev->left == current){
            delete current;
            prev->left = nullptr;
        }
        else{
            delete current;
            prev->right = nullptr;
        }

    }

    else if (current->left != nullptr && current->right == nullptr){
        if (current == root_)
            root_ = current->left;
        else if (prev->left == current)
            prev->left = current->left;
        else
            prev->right = current->left;

        delete current;
    }

    else if (current->right != nullptr && current->left == nullptr){
        if (current == root_)
            root_ = current->right;
        else if (prev->left == current)
            prev->left = current->right;
        else
            prev->right = current->right;

        delete current;
    }


    else if (current->left != nullptr && current->right != nullptr){
        Node* predecessor = current->left;
        Node* PreParent = current;

        while (predecessor->right != nullptr){
            PreParent = predecessor;
            predecessor = predecessor->right;
        }

        current->val = predecessor->val;

        if (predecessor->left == nullptr){
            if (predecessor == current->left)
                current->left = nullptr;
            else
                PreParent->right = nullptr;
        }

        else{
            if (predecessor == current->left)
                PreParent->left = predecessor->left;
            else
                PreParent->right = predecessor->left;
        }

        delete predecessor;
        predecessor = nullptr;
        PreParent = nullptr;

    }

    current = nullptr;
    prev = nullptr;
    size_ --;
    return true;

}
