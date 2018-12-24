/* 
 * Trie.h
 *
 *  header file for trie
 */
#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string.h>
using namespace std;



    struct Node {
        char  data;
        bool  node_end = false;
        Node *a = NULL;
        Node *t = NULL;
        Node *c = NULL;
        Node *g = NULL;
    };  

class Trie {
public:

        // constructor
       Trie();

        // destructor
        ~Trie();

        // copy constructor
        Trie(const Trie &source);   

        // assignment overload
        Trie &operator= (const Trie &source);

        // contains() returns true if the queried string is in the trie,
        // false if it is not in the trie
        int contains(string str) const;

        // insert() inserts the value into the trie.
        void insert(string str);

        // remove() will remove the queried sequence in the event that
        // the string has a full match with the given sequence.
        bool remove(string str);

        int open_out(string output);

        void query(string str);

private:
        Node *root = new Node;

        bool is_leaf(Node *node, string str);

        Node* traverse_to_end(Node *node, string str);

        // returns true if the entire sequence is contained
        // in the trie, false if not.
        bool contains_bool(Node *node, string str);

        void insert_wild(Node *node, int i, string str);


        void delete_trie(Node *node);
        // these are private helper functins for the public
        // functions. the root and other information is passed
        // to these from the public functions.
        void  query(string str, Node* node);
        void  new_node(Node *node, int i, string str);
        int   int_longest(Node *node, string str, int i) const;
        int   contains(Node *node, int i, string str) const;
        void  insert(Node *node, string str, int i);
        void  remove_wild(Node *node, string str, int i);
        bool  remove(Node *node, int i, string str);
};


#endif  /*TRIE_H*/