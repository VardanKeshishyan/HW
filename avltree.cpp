#include "avltree.h"
#include <algorithm>
#include <string>
using namespace std;

AVLTree::AVLTree() : BST("AVLTree") {}

int AVLTree::get_height(Node* node) {
    if(node == nullptr) return 0;
    return node->height;
}

int AVLTree::get_balance(Node* node) {
    if(node == nullptr) return 0;
    return get_height(node->left) - get_height(node->right);
}

void AVLTree::set_height(Node* node) {
    if(node){ node->height = 1 + std::max(get_height(node->left), get_height(node->right));}
}

Node* AVLTree::right_rotate(Node* y) {
    Node* r = y->left; Node* tmp = r->right;
    r->right = y; y->left = tmp;
    set_height(y);
    set_height(r);
    return r;
}

Node* AVLTree::left_rotate(Node* r) {
    Node* y = r->right; Node* tmp = y->left;
    y->left = r; r->right = tmp;
    set_height(r);
    set_height(y);
    return y;
}

Node* AVLTree::rebalance(Node* t) {
    if (t == nullptr) return t;
    set_height(t);
    int is_balance = get_balance(t);
    return isAbalance(t, is_balance);
}

Node* AVLTree::isAbalance(Node* t, int is_balance) {
    if (is_balance > 1) { if (get_balance(t->left) < 0) t->left = left_rotate(t->left);
        return right_rotate(t);}
    if (is_balance < -1) { if (get_balance(t->right) > 0) t->right = right_rotate(t->right);
        return left_rotate(t);}
    return t;
}

Node* AVLTree::insert_node(Node* t, string key) {
    if(t == nullptr) return new Node(key);
    if(key < t->key) t->left = insert_node(t->left, key);
    else if(key > t->key) t->right = insert_node(t->right, key);
    else return t;
    return rebalance(t);
}

Node* AVLTree::find_node(Node* t, string key) {
    if(t == nullptr) return nullptr;
    if(key == t->key) return t;
    else if(key < t->key) return find_node(t->left, key);
    else return find_node(t->right, key);
}

Node* AVLTree::delete_node(Node* t, string key) {
    if(t == nullptr)return t;
    if(key < t->key)t->left = delete_node(t->left, key);
    else if(key > t->key)t->right = delete_node(t->right, key);
    else t = deleteFound(t);
    return t==nullptr?t:rebalance(t);
}

Node* AVLTree::deleteFound(Node* t) {
    if(t->left==nullptr || t->right==nullptr){ Node* temp = (t->left ? t->left : t->right);
    if(temp==nullptr){ temp=t; t=nullptr; } else *t=*temp; delete temp; } else{ Node* temp = t->right;
    while(temp->left!=nullptr)temp = temp->left;
    t->key=temp->key; t->right = delete_node(t->right, temp->key); }
    return t;}

void AVLTree::insert(const string & key) {
    if(find(key))
        return;
    root = insert_node(root, key);
    count++;
}

bool AVLTree::find(const string & key) const {
    return (find_node(root, key) != nullptr);
}

void AVLTree::remove(const string & key) {
    if(find(key)) {
        root = delete_node(root, key);
        count--;
    }
}

int AVLTree::get_height() const {
    return AVLTree::get_height(root);
}

bool AVLTree::is_empty() const {
    return root == nullptr;
}

void AVLTree::iterator::pushToleft(Node* node) {
    while(node) {
        n_stack.push(node);
        node = node->left;
    }
}

AVLTree::iterator::iterator(Node* root) {
    pushToleft(root);
}

AVLTree::iterator::iterator() {}

std::string& AVLTree::iterator::operator*() {
    return n_stack.top()->key;
}

AVLTree::iterator& AVLTree::iterator::operator++() {
    Node* node = n_stack.top();
    n_stack.pop();
    if(node->right) pushToleft(node->right);
    return *this;
}

bool AVLTree::iterator::operator==(const iterator& other_it) const {
    if(n_stack.empty() && other_it.n_stack.empty()) return true;
    if(n_stack.empty() || other_it.n_stack.empty()) return false;
    return n_stack.top() == other_it.n_stack.top();
}

bool AVLTree::iterator::operator!=(const iterator& other_it) const {
    return !(*this == other_it);
}

AVLTree::iterator AVLTree::iterator::operator++(int) {
    iterator temp = *this;
    ++(*this);
    return temp;
}

void AVLTree::print(ostream & out) const {
    for (auto it = begin(); it != end(); ++it) {
        out << *it << " ";
    }
}
