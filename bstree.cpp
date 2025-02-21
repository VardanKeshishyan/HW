#include "bstree.h"
#include <algorithm>
#include <stack>
#include <string>
using namespace std;

BSTree::BSTree() : BST("BSTree") {}

bool BSTree::find(const string & key) const {
    return (find_node(root, key) != nullptr);
}

void BSTree::insert(const string & key) {
    if(find(key))
        return;
    root = insert_node(root, key);
    count++;
}

void BSTree::remove(const string & key) {
    if(find(key)) {
        root = delete_node(root, key);
        count--;
    }
}

bool BSTree::is_empty() const {
    return root == nullptr;
}

int BSTree::get_height() const {
    return compute_height(root);
}

Node* BSTree::insert_node(Node* t, string key) {
    if (!t) return new Node(key);
    Node* parent = find_parent_for_insert(t, key);
    if (key < parent->key) parent->left = new Node(key);
    else if (key > parent->key) parent->right = new Node(key);
    return t;}

Node* BSTree::find_parent_for_insert(Node* t, string key) {
    Node* current = t; Node* parent = nullptr;
    while (current) {
        parent = current;
        if (key < current->key) current = current->left; else if (key > current->key) current = current->right;
        else return parent;} return parent;}


Node* BSTree::find_node(Node* t, string key) {
    Node* current = t;
    while (current) {
        if (key == current->key) return current;
        else if (key < current->key) current = current->left;
        else current = current->right;} return nullptr;}


Node * BSTree::left_most(Node * t) {
    if(t == nullptr) return nullptr;
    while(t->left != nullptr)
        t = t->left;
    return t;
}

Node* BSTree::delete_node(Node* t, std::string key) {
    Node* parent = nullptr, *current = find_node_and_parent(t, key, parent); if (!current) return t;
    if (current->left && current->right) return caseDeletion(current), t;
    Node* child = current->left ? current->left : current->right;
    if (!parent) t = child; else (parent->left == current ? parent->left : parent->right) = child;
    delete current; return t;}

Node* BSTree::caseDeletion(Node* node) {
    Node* sp = node, *s = node->right;
    while (s->left) sp = s, s = s->left;
    node->key = s->key;
    (sp->left == s ? sp->left : sp->right) = s->right;
    delete s; return node;}

Node* BSTree::find_node_and_parent(Node* t, string key, Node*& parent) {
    Node* current = t;
    while (current && current->key != key) {
        parent = current;
        current = (key < current->key) ? current->left : current->right;}
    return current;}

int BSTree::compute_height(Node* t) {
    if (!t) return 0;
    std::queue<Node*> q;
    q.push(t);
    return process_level(q, 0);
}

int BSTree::process_level(std::queue<Node*>& q, int height) {
    while (!q.empty()) {
        int LS = q.size();
        for (int i = 0; i < LS; i++) {
            Node* node = q.front();q.pop(); if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);} height++;} return height;}

void BSTree::iterator::pushToleft(Node* node) {
    while(node) {
        n_stack.push(node);
        node = node->left;
    }
}

BSTree::iterator::iterator(Node* root) {
    pushToleft(root);
}

BSTree::iterator::iterator() {}

std::string& BSTree::iterator::operator*() {
    return n_stack.top()->key;
}

BSTree::iterator& BSTree::iterator::operator++() {
    Node* node = n_stack.top();
    n_stack.pop();
    if(node->right) pushToleft(node->right);
    return *this;
}

bool BSTree::iterator::operator==(const iterator& other_it) const {
    if(n_stack.empty() && other_it.n_stack.empty()) return true;
    if(n_stack.empty() || other_it.n_stack.empty()) return false;
    return n_stack.top() == other_it.n_stack.top();
}

bool BSTree::iterator::operator!=(const iterator& other_it) const {
    return !(*this == other_it);
}

BSTree::iterator BSTree::iterator::operator++(int) {
    iterator temp = *this;
    ++(*this);
    return temp;
}

void BSTree::print(ostream & out) const {
    for (auto it = begin(); it != end(); ++it) {
        out << *it << " ";
    }
}
