usage:
	@echo "Usage:"
	@echo " 1) dependencies: Download the EasyBMP library sources."
	@echo " 2) easyexec: Compile and link the ’easyexec’ executable."
	@echo " 3) clean: Removes dependencies and compiled files."

# Linking
colorToGray: colorToGray.o
	g++ -o colorToGray EasyBMP.o
ex1: ex1.o EasyBMP.o
	g++ -o ex1 ex1.o EasyBMP.o
ex1.o: ex1.cpp
	g++ -c ex1.cpp EasyBMP.cpp
ex2: ex2.o EasyBMP.o
	g++ -o ex2 ex2.o EasyBMP.o
ex2.o: ex2.cpp 
	g++ -c ex2.cpp EasyBMP.cpp
ex3: ex3.o EasyBMP.o
	g++ -o ex3 ex3.o EasyBMP.o
ex3.o: ex3.cpp
	g++ -c ex3.cpp EasyBMP.cpp
EasyBMP.o: EasyBMP.cpp
	g++ -c EasyBMP.cpp
easyexec: main.o
	g++ -o easyexec main.o includes/EasyBMP.o

# Compilation
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
