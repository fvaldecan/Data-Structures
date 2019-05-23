usage:
@echo "Usage:"
@echo " 1) dependencies: Download the EasyBMP library sources."
@echo " 2) easyexec: Compile and link the ’easyexec’ executable."
@echo " 3) clean: Removes dependencies and compiled files."

# Linking
stack1: stack1.o
	g++ -o stack1 stack1.o

# Compilation
stack1.o: stack1.cpp 
	g++ -c stack1.cpp

# Easy BMP library compilation
includes/EasyBMP.o:
	g++ -c includes/EasyBMP.cpp -o includes/EasyBMP.o

# Download and unzip the EasyBMP library.
.PHONY: dependencies
dependencies: includes
	wget http://prdownloads.sourceforge.net/easybmp/EasyBMP_1.06.zip
	unzip EasyBMP_1.06.zip -d includes && rm EasyBMP_1.06.zip

# Creates the includes subdirectory if it does not exist
includes:
	mkdir -p includes

.PHONY: clean
clean:
	-rm -r easyexec *.o *.bmp *.zip *.tar.gz includes 2> /dev/null || true

.PHONY: archive
archive:
	tar -cvzf lab5.tar.gz stack1.cpp makefile
