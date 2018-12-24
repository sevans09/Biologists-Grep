/*
 * main.cpp
 * 
 * Driver of trie program
 */
#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string.h>
#include "Trie.h"
using namespace std;

// declare commands as constants
const char IN = 'i';
const char Q = 'q';
const char R = 'r';

int main(int argc, char *argv[])
{       
    string INPUT;
    string OUTPUT;
    ifstream infile;
    ofstream outfile;

    if (argc < 3){
        cerr << "Command line has less than two files. Try again";
        cerr << endl;
        return 0;
    }

    else{
        INPUT = argv[1];
        OUTPUT = argv[2];
        infile.open(INPUT.c_str());
        if (infile.is_open() != true){
            cerr << "File could not be opened" << endl;
            return 0;
        }
        else{
            Trie trie;
            string inSeq;
            trie.open_out(OUTPUT);
            while (getline(infile, inSeq)){
                char command = inSeq[0];
                // create new shorter sequence of input seq that contains
                // only the beginning of the seq to end, not the command
                inSeq = inSeq.substr(2, inSeq.length());
                if (command == IN)
                    trie.insert(inSeq);
                else if (command == Q)
                    trie.query(inSeq);
                else if (command == R)
                    trie.remove(inSeq);
                else
                    cerr << "Please input a valid sequence" << endl;
            }
            infile.close();
            outfile.close();
        }
    } 
        return 0;
}
