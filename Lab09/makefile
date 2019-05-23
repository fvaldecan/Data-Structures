# Linking
Lab09: Lab09.o
	g++ -o Lab09 Lab09.o

# Compilation
Lab09.o: Lab09.cpp AvlTree.h dsexceptions.h
	g++ -c Lab09.cpp AvlTree.h dsexceptions.h

.PHONY: archive
archive:
	tar -cvzf valdecanaslab9.tar.gz Lab09.cpp dsexceptions.h in.txt AvlTree.h makefile README.txt
