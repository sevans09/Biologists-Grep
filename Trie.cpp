/* 
 * Trie.cpp
 *
 *  Created on: Oct 13, 2014
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cmath>
#include "Trie.h"
using namespace std;

//Function: search tree constructor
//Parameters: none
//Output: none
//Does: constructs a binary search tree
Trie::Trie()
{
    root->data = 'R';
    root->node_end = false;
    root->a = NULL;
    root->c = NULL;
    root->t = NULL;
    root->g = NULL;

}

//Function: binary search tree destructor
//Parameters: none 
//Output: none
//Does: calls post order delete to do a post order traversal and
// delete the tree
Trie::~Trie()
{
        // call delete function to delete all root's children
        delete_trie(root);
        root = NULL;  
}

//Function: delete
//Parameters: pointer to a node
//Output: none
//Does: 
void Trie::delete_trie(Node *node)
{
	if (node == NULL)
        return;
    if (!node->a && !node->c && !node->g && !node->t)
    	delete node;
    else{
		if (node->a){
	        delete_trie(node->a);
		}
	    if (node->t){
	        delete_trie(node->t);
	    }
	    if (node->c){
	        delete_trie(node->c);
	    }
	    if (node->g){
	        delete_trie(node->g);
	    }
		delete node;
    }  
    return;
}

// Function is_leaf
bool Trie::is_leaf(Node *node, string str)
{
	int str_length = str.length();
	str_length--;
	string str_new = str.substr(0, str_length);
	Node *node_chk = traverse_to_end(node, str_new);
	if (node_chk->a)
		return false;
	else if (node_chk->c)
		return false;
	else if (node_chk->g)
		return false;
	else if (node_chk->t)
		return false;
	else
		return true;
}

int Trie::open_out(string output)
{
	ofstream outfile;
	outfile.open(output.c_str());
	if (outfile.is_open() != true){
		cerr << "Failed to open output file" << endl;
		return false;
	}
	else return 1;
}

// function: contains_bool
// parameters: node and string sequence
// returns; boolean whther the whole string is contained in trie
// does: traverses down and checks flags to see if whole sequence is
// already contained in the trie
bool Trie::contains_bool(Node *node, string str)
{
	int str_length = str.length();
	int num_matched = contains(str);
	if (str_length-1 == num_matched){
		for (int i = 0; i < str_length; i++){
			if (str[i] == 'A')
				node = node->a;
			else if (str[i] == 'C')
				node = node->c;
			else if (str[i] == 'T'){
				node = node->t;
			}
			else if (str[i] == 'G')
				node = node->g;
			else if (str[i] == '?'){
				if (node->a != NULL){
			    	node = node->a;
		    	}
		    	else if (node->c != NULL){
		    		node = node->c;
		    	}
		    	else if (node->t != NULL){
		    		node = node->t;
		    	}
		    	else if (node->g != NULL){
		    		node = node->g;
		    	}
		    }
		}
		if (node->node_end == true)
			return true;
		else
			return false;
	}
	else
		return false;
}



//Function: contains
//Parameters: string str
//Output: int of number matched
//Does: wrapper function for contains
int Trie::contains(string str) const
{
    if (root == NULL)
        return 0;
    else return contains(root, 0, str);
}
// Function: traverse_to_end
// Parameters: node, string
// Returns: a node that is the end of the sequence in the trie
// Does: Traverses the trie to find the end of the sequence and returns
// that node.
Node* Trie::traverse_to_end(Node *node, string str)
{
	int str_length = str.length();
	for (int i = 0; i < str_length; i++){
		if (str[i] == 'A'){
			if (node->a == NULL)
				return node;
			else
				node = node->a;
		}
		else if (str[i] == 'C'){
			if (node->c == NULL)
				return node;
			else
				node = node->c;
		}
		else if (str[i] == 'T'){
			if (node->t == NULL)
				return node;
			else
				node = node->t;
		}
		else if (str[i] == 'G')
			if (node->g == NULL)
				return node;
			else
				node = node->g;
		else if (str[i] == '?'){
			if (node->a != NULL){
		    	node = node->a;
	    	}
	    	if (node->c != NULL){
	    		node = node->c;
	    	}
	    	if (node->g != NULL){
	    		node = node->g;
	    	}
	    	if (node->t != NULL){
	    		node = node->t;
	    	}
	    }
	}
	return node;
}

//Function: contains
//Parameters: node, int i for index, string
//Output: int for number of matches found in the trie
//Does: traverses down the tree and stops if the next node is not
// is not found in the trie or when string length - 1 = index,
// or all of the sequence has been found.
int Trie::contains(Node *node, int i, string str) const
{
	int str_length = str.length();
	if (str_length - 1 == i)
		return str_length;
    if (str[i] == 'A'){
    	if (node->a == NULL)
    		return i;
    	else{
	    	i++;
	    	return contains(node->a, i, str);
    	}
    }
    if (str[i] == 'C'){
		if (node->c == NULL)
    		return i;
    	else{
	    	i++;
	    	return contains(node->c, i, str);
    	}
    }
    if (str[i] == 'T'){
		if (node->t == NULL)
    		return i;
    	else{
	    	i++;
	    	return contains(node->t, i, str);
    	}
    }
    if (str[i] == 'G'){
		if (node->g == NULL)
    		return i;
    	else{
	    	i++;
	    	return contains(node->g, i, str);
    	}
	}
	if (str[i] == '?'){
		int max = 0;
		if (node->a == NULL && node->c == NULL
			&& node->t == NULL && node->g == NULL)
    		return i;
       	if (node->a != NULL){
	    	int m = contains(node->a, i+1, str);	  
	    	if (m > max)
    			max = m;  	
    	}
    	if (node->c != NULL){
    		int m = contains(node->c, i+1, str);
    		if (m > max)
    			max = m;
    	}
    	if (node->t != NULL){
    		int m = contains(node->t, i+1, str);
    		if (m > max)
    			max = m;
    	}
    	if (node->g != NULL){
    		int m = contains(node->g, i+1, str);
    		if (m > max)
    			max = m;
    	}
    	i = max++;
		return i;
    }
}
// Function: new_node
// Parameters: node, int i for index, string
// Returns: void
// Does: creates nodes for the trie and traverses down to insert a
// sequence called.
void Trie::new_node(Node *node, int i, string str)
{
	int str_length = str.length();
    for (i; i < str_length; i++){
        if (str[i] == '?'){
    		insert_wild(node, i, str);
    	}
		else if (str[i] == 'A'){
			if (node->a){
				node = node->a;
			}
			else if (node->a == NULL){
				node->a = new Node;
				node->data = 'A';
				node = node->a;
			}
		}
		else if (str[i] == 'C'){
			if (node->c){
				node = node->c;
			}
			else if (node->c == NULL){
				node->c = new Node;
				node->data = 'C';
				node = node->c;				
			}
		}
		else if (str[i] == 'T'){
			if (node->t){
				node = node->t;				
			}
			else if (node->t == NULL){
				node->t = new Node;
				node->data = 'T';
				node = node->t;
			}
		}
		else if (str[i] == 'G'){
			if (node->g){
				node = node->g;
			}
			else if (node->g == NULL){
				node->g = new Node;
				node->data = 'G';
				node = node->g;	
			}
	    }
	    else return;
    }
    node->node_end = true;
}

// Function: insert_wild
// Parameters: node, int i for index, string
// Returns: void
// Does: if a ? character is inserted, loops through and creates
// all possible sequences in the trie.
void Trie::insert_wild(Node *node, int i, string str){
	if (node->a == NULL){
		node->a = new Node;
		node->data = 'A';
		node = node->a;
		i++;
	}
	else if (node->a){
		node->data = 'A';
		node = node->a;
		i++;
	}
	new_node(node, i, str);
	if (node->c == NULL){
		node->c = new Node;
		node->data = 'C';
		node = node->c;
		i++;
	}
	else if (node->c){
		node->data = 'C';
		node = node->c;
		i++;
	}
	new_node(node, i, str);
	if (node->t == NULL){
		node->t = new Node;
		node->data = 'T';
		node = node->t;
		i++;
	}
	else if (node->t){
		node->data = 'T';
		node = node->t;
		i++;
	}
	new_node(node, i, str);
	if (node->g == NULL){
		node->g = new Node;
		node->data = 'G';
		node = node->g;
		i++;
	}
	else if (node->g){
		node->data = 'G';
		node = node->g;
		i++;
	}
	new_node(node, i, str);
}

// Function: insert
// Parameters: string
// Returns: void
// Does: Wrapper function for insert
void Trie::insert(string str)
{
    insert(root, str, 0);
}

// Function: insert
// Parameters: node, string, int i for index
// Returns: none
// Does: Wrapper function for insert
void Trie::insert(Node *node, string str, int i)
{
    // iterate through whole string length and check each char
	// for a node match. create a new node if nonexistent
    new_node(node, i, str);

}

// Function: query
// Parameters: string
// Returns: none
// Does: Wrapper function for query
void Trie::query(string str)
{
	query(str, root);
}

// recursive function that returns the longest sequence in tree that
// contains the sequences
int Trie::int_longest(Node *node, string str, int i) const
{
	int str_length = str.length();
	if (node == NULL)
		return i - 1;
	for (0; i < str_length; i++){
		if (str[i] == node->data){
			if (str[i] == 'A'){
				node = node->a;
			}
			else if (str[i] == 'C'){
				node = node->c;
			}
			else if (str[i] == 'T'){
				node = node->t;
			}
			else if (str[i] == 'G'){
				node = node->g;
			}
			else if (str[i] == '?'){
				if (node->a && node->c && node->g && node->t){
					if (str[i + 1] == 'A'){
						node = node->a;
					}
					else if (str[i + 1] == 'C'){
						node = node->c;
					}
					else if (str[i + 1] == 'G'){
						node = node->g;
					}
					else if (str[i + 1] == 'T'){
						node = node->t;
					}
		    	}
		    }
		}
		else return i;
	}
	if (node->a){
		i++;
		return int_longest(node->a,str,i);
	}
	if (node->c){
		i++;
		return int_longest(node->c,str,i);
	}
	if (node->g){
		i++;
		return int_longest(node->g,str,i);
	}
	if (node->t){
		i++;
		return int_longest(node->t,str,i);
	}
	else return i -1;
}

// Function: query
// Parameters: string and node
// Returns: void
// Does: checks if trie contains queried sequence. if it doesnt contain
// the first letter, no match is found. otherwise, if contais_bool
// returns true that the whole sequence is found in the trie, there is a 
// 100% match. otherwise, it sees if part of the queried sequence is 
// contained in the trie.
void Trie::query(string str, Node *node)
{
	int i = 0;	
	// number of letters in the trie that match the sequence
	int num_matched = contains(str);
	int str_length = str.length();
	Node *node_check = traverse_to_end(node, str);
	if (contains_bool(node, str)){
		cout << "Match found " << str << " 100%" << endl;
	}
	else if (num_matched == 0){
		cout << "No match found" << endl;
		return;
	}
	else{
		// otherwise, traverse down tree and search for matches
		int longest_seq = int_longest(node, str, 0);
		double temp_long = max(longest_seq, str_length);
		double percent_match = (num_matched * 100) / temp_long;
		percent_match = round(percent_match);
		cout << "Match found ";
		for (0; i < temp_long; i++){
				if (str[i] == 'A'){
					cout << str[i];
				//	node = node->a;
				}
				else if (str[i] == 'C'){
					cout << str[i];
				//	node = node->c;
				}
				else if (str[i] == 'T'){
					cout << str[i];
				//	node = node->t;
				}
				else if (str[i] == 'G'){
					cout << str[i];
				//	node = node->g;
				}
				else if (str[i] == '?'){
					cout << "?";
					if (node->a && node->c && node->g && node->t){
						if (str[i + 1] == 'A'){
							cout << "A";
							node = node->a;
						}
						else if (str[i + 1] == 'C'){
							cout << "C";
							node = node->c;
						}
						else if (str[i + 1] == 'G'){
							cout << "G";
							node = node->g;
						}
						else if (str[i + 1] == 'T'){
							cout << "T";
							node = node->t;
						}
					}			    	
			    }
		}
		cout << " " << percent_match << "%" << endl;
		return;
	}
}

// Function: remove
// Parameters: string
// Returns: a boolean if the string is removed or not
// Does: Wrapper function for remove
bool Trie::remove(string str)
{
	return remove(root, 0, str);
}

// Function: remove_wild
// Parameters: node, string
// Returns: bool
// Does: recursively removes a wildcard ? character
void Trie::remove_wild(Node *node, string str, int i)
{
	i++;
	if (node->a){
		cout << "A";
		node = node->a;
	}
	if (node->c){
		cout << "C";
		node = node->c;
	}
	if (node->g){
		cout << "G";
		node = node->g;
	}
	if (node->t){
		cout << "T";
		node = node->t;
	}
	remove(node->a, i, str);
	remove(node->c, i, str);
	remove(node->g, i, str);
	remove(node->t, i, str);
}

// Function: remove
// Parameters: string
// Returns: a boolean if the string is removed or not
// Does: Checks if the whole sequence is contained in the trie.
// If it is, change node marker to false and if it is a leaf node,
// delete the node.
bool Trie::remove(Node *node, int i, string str)
{
	int str_length = str.length();
    if (node == NULL)
        return false;
    Node *node_check = traverse_to_end(node, str);
    if (node_check->node_end == false){
    	cout << "No match found" << endl;
    	return false;
    }
    else {
    	for (int i = 0; i < str_length; i++){
			if (str[i] == 'A'){
				if (node->a){
					cout << "A";
					node = node->a;
				}
			}
			else if (str[i] == 'C'){
				if (node->c){
					cout << "C";
					node = node->c;
				}
			}
			else if (str[i] == 'T'){
				if (node->t){
					cout << "T";
					node = node->t;
				}
			}
			else if (str[i] == 'G'){
				if (node->g){
					cout << "G";
					node = node->g;
				}
			}
			else if (str[i] == '?'){
				remove_wild(node, str, i);
			}
		}
	}

	node->node_end = false;
	if (is_leaf(node,str)){
		node->data = 'X';
	}
	cout << " removed" << endl;
	return true;
}

