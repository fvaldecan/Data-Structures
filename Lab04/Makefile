usage:
	@echo "Usage:"
	@echo " 1) dependencies: Download the EasyBMP library sources."
	@echo " 2) easyexec: Compile and link the ’easyexec’ executable."
	@echo " 3) clean: Removes dependencies and compiled files."

# Linking
colorToGray: colorToGray.o
	g++ -o colorToGray main.o include/EasyBMP.o
problem1: problem1.o
	g++ -o problem1 problem1.o includes/EasyBMP.o

ex2: main.o
	g++ -o ex2 ex2.cpp EasyBMP.cpp
	.ex2.out
easyexec: main.o
	g++ -o easyexec main.o includes/EasyBMP.o

# Compilation
problem1.o: problem1.cpp includes/EasyBMP.o
	g++ -c problem1.cpp -Iincludes
main.o: main.cpp includes/EasyBMP.o
	g++ -c main.cpp -Iincludes

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
	tar -cvzf $(USER)_lab3.tar.gz main.cpp Makefile
