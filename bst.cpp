#include <iostream>
#include <fstream>
#include "bst.h"
#include "bstree.h"
#include "avltree.h"
#include "timer.h"
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

void delete_tree(Node * t) {
    if(t) {
        delete_tree(t->left);
        delete_tree(t->right);
        delete t; }
}

BST::~BST() {
    delete_tree(root);
}

void BST::pre_order_print(ostream & out, Node * t) {
    if(t) {
        out << t->key << " ";
        pre_order_print(out, t->left);
        pre_order_print(out, t->right);
    }
}

void BST::in_order_print(ostream & out, Node * t) {
    if(t) {
        in_order_print(out, t->left);
        out << t->key << " ";
        in_order_print(out, t->right);}
}

void BST::post_order_print(ostream & out, Node * t) {
    if(t) {
        post_order_print(out, t->left);
        post_order_print(out, t->right);
        out << t->key << " ";}
}

ostream & operator << (ostream & out, BST & L) {
    L.print(out);
    return out;
}

void error(string word, string msg) {
    cerr << "Error -> " << word << " : " << msg << endl;
    return;
}


void process_partition(BST &L, const std::vector<std::string>& words, int begin, int end, char op) {
    for (int i = begin; i < end; i++) {
        if (op == 'I')
            L.insert(words[i]);
        else if (op == 'F')
            L.find(words[i]);
        else
            L.remove(words[i]);
    }
}


std::vector<std::string> read_words(const std::string &file_name) {
    std::ifstream in(file_name);
    if (!in) {
        std::cerr << "Error opening file " << file_name << std::endl;
        return {};
    }
    std::vector<std::string> words;
    for (std::string w; in >> w; ) {
        words.push_back(w);
    }
    std::cout << "Read " << words.size() << " words\n";
    return words;
}


void process_all_words(int k, const std::string &file_name, BST &L, char op) {
    std::vector<std::string> words = read_words(file_name);
    int total = static_cast<int>(words.size());
    if (total == 0) return;
    
    int p_s = total / k;   
    int remainder = total % k;
    
    for (int i = 0, start_idx = 0; i < k; i++) {
        Timer timer;
        timer.start();
        
        int extra = (i < remainder ? 1 : 0);
        int end_idx = start_idx + p_s + extra;
        
        process_partition(L, words, start_idx, end_idx, op);
        start_idx = end_idx;
        
        double eTime;
        timer.elapsedUserTime(eTime);
        std::cout << "Partition " << (i+1) << ": " << eTime << " s\n";
    }
}



void insert_all_words(int k, const std::string &file_name, BST &L) {
    process_all_words(k, file_name, L, 'I');
}

void find_all_words(int k, const std::string &file_name, BST &L) {
    process_all_words(k, file_name, L, 'F');
}

void remove_all_words(int k, const std::string &file_name, BST &L) {
    process_all_words(k, file_name, L, 'R');
}


void measure_BST(string file_name, BST & L) {
    cout << "Let's Measure " << L.name << " File-> " << file_name << endl;
    int p = 10; insert_all_words(p, file_name, L);
    cout << "Height: " << L.get_height() << endl;
    find_all_words(p, file_name, L); remove_all_words(p, file_name, L);
    cout << "Done: " << L.name << "\n" << endl;}

void measure_BSTs(string input_file) {
    cout << "\nLet's Measure BSTree" << endl;
    BSTree bst; AVLTree avl;
    measure_BST(input_file, bst);
    cout << "\nLet's Measure AVLTree" << endl;
    measure_BST(input_file, avl);}



