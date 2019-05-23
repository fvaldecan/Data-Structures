usage:
@echo "Usage:"
@echo " 1) dependencies: Download the EasyBMP library sources."
@echo " 2) easyexec: Compile and link the ’easyexec’ executable."
@echo " 3) clean: Removes dependencies and compiled files."

# Linking
queue: queue.o EasyBMP.o
	g++ -o queue queue.o EasyBMP.o

# Compilation
queue.o: queue.cpp 
	g++ -c queue.cpp 
EasyBMP.o: EasyBMP.cpp
	g++ -c EasyBMP.cpp
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
	tar -cvzf valdecanaslab6.tar.gz queue.cpp makefile
