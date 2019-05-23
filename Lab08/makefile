# Linking
Lab08: Lab08.o
	g++ -o Lab08 Lab08.o

# Compilation
Lab08.o: Lab08.cpp BinarySearchTree.h dsexceptions.h
	g++ -c Lab08.cpp BinarySearchTree.h dsexceptions.h


.PHONY: archive
archive:
	tar -cvzf valdecanaslab8.tar.gz Lab08.cpp dsexceptions.h in.txt BinarySearchTree.h makefile README.txt
