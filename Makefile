main: main.cc
	g++ -std=c++14 -g -Wall -o p02-language main.cc alphabet.cc word.cc file_managment.cc language.cc

alphabet: alphabet.cc
	g++ -std=c++14 -g -Wall -o alphabet alphabet.cc

word: word.cc
	g++ -std=c++14 -g -Wall -o word word.cc

file_managment: file_managment.cc
	g++ -std=c++14 -g -Wall -o file_managment file_managment.cc

language: language.cc
	g++ -std=c++14 -g -Wall -o language language.cc

