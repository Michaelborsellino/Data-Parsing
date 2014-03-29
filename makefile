all: dataparsing.x

dataparsing.x: dataparsing.o
	g++47 -odataparsing.x dataparsing.o

dataparsing.o: dataparsing.cpp
	g++47 -g -c -std=c++11 -Wall -Wextra  dataparsing.cpp

