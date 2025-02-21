#ifndef AVLTREE_H
#define AVLTREE_H

#include <stack>
#include <string>
#include "bst.h"

using namespace std;

class AVLTree : public BST
{
    static int get_height(Node * node);
    static int get_balance(Node * node);
    static void set_height(Node * node);
    static Node * right_rotate(Node * y);
    static Node * left_rotate(Node * x);
    static Node * rebalance(Node * t);
    static Node * insert_node(Node * t, string key);
    static Node * find_node(Node * t, string key);
    static Node * delete_node(Node * t, string key);
    static Node * isAbalance(Node* t, int is_balance);
    static Node * deleteFound(Node* t);
public:
    AVLTree();
    void insert(const string & key);
    bool find(const string & key) const;
    void remove(const string & key);
    bool is_empty() const;
    int get_height() const;
    void print(ostream & out) const;
    class iterator {
    private:
        std::stack<Node*> n_stack;
        void pushToleft(Node* node);
    public:
        iterator(Node* root);
        iterator();
        std::string& operator*();
        iterator& operator++();
        iterator operator++(int);
        std::string * operator->() { return &n_stack.top()->key; }
        bool operator==(const iterator& other_it) const;
        bool operator!=(const iterator& other_it) const;
    };
    iterator begin() const { return iterator(root); }
    iterator end() const { return iterator(); }
};

#endif
