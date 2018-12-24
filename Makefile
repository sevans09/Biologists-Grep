# 
# Makefile for Trees Biology Project
#
# Project 1 (fall 2018)
#

CXX      = clang++
CXXFLAGS = -g -Wall -Wextra -std=c++11
LDFLAGS  = -g

SeqMatch: Trie.o main.o
	${CXX} ${LDFLAGS} -o SeqMatch Trie.o main.o

Trie.o: Trie.h main.cpp
main.o: Trie.cpp Trie.h

clean:
	rm -f SeqMatch *.o *.dYSM

provide:
	provide comp15 proj1 SeqMatch main.cpp Trie.cpp Trie.h \
	README Makefile

