#ifndef SRC_BOOK_H
#define SRC_BOOK_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std; 

class Book {
	int year;
	string ISBN, title, author, publisher;

public:
	Book(string ISBN, string title, string author, int year, string publisher);
	void printData();
    void readFile(string fileName);

};

#endif