CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

OptionPricing: Main.o MCModel.o PathDepOption.o Matrix.o
	$(CC) $(CFLAGS) -o OptionPricing Main.o MCModel.o PathDepOption.o Matrix.o

Main.o: Main.cpp PathDepOption.h
	$(CC) $(CFLAGS) -c Main.cpp

PathDepOption.o: MCModel.h PathDepOption.h PathDepOption.cpp
	$(CC) $(CFLAGS) -c PathDepOption.cpp
	
MCModel.o: Matrix.h MCModel.h MCModel.cpp
	$(CC) $(CFLAGS) -c MCModel.cpp
	
Matrix.o: Matrix.h Matrix.cpp
	$(CC) $(CFLAGS) -c Matrix.cpp
	
clean:
	rm -rf  OptionPricing *.o
