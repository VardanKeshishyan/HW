#ifndef BSTREE_H
#define BSTREE_H
#include <queue>
#include "bst.h"
#include <stack>
#include <string>
using namespace std;

class BSTree : public BST
{
    static Node * insert_node(Node * t, string key);
    static Node * find_node(Node * t, string key);
    static Node * find_parent_for_insert(Node* t, string key);
    static Node * find_node_and_parent(Node* t, string key, Node*& parent);
    static int process_level(queue<Node*>& q, int height);
    static Node * left_most(Node * t);
    static Node * delete_node(Node * t, string key);
    static int compute_height(Node * t);
    static Node * caseDeletion(Node* t);
public:
    BSTree();
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
