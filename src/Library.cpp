#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Library.h"
using namespace std;

void Library::timSort(std::string type) {
    if (type == "author" || type == "title" || type == "publisher" || type == "ISBN") {
        std::vector<std::string> strings;

        for (int i = 0; i < library.size(); i++) {
            if (type == "author")
                strings.push_back(library[i].Book::author);
        }
        
        helperTimSort(strings);
    }
        
    else {
        std::vector<int> ints;

        for (int i = 0; i < library.size(); i++)
            ints.push_back(library[i].Book::year);

        helperTimSort(ints);

    }
    
}

void Library::readFile() {
    std::ifstream myfStream;
	myfStream.open("books.csv");
	if (!myfStream.is_open())
		std::cout << "File failed to load" << std::endl;
	std::string ISBN, title, author, year, publisher, junk;

	std::string line;
	bool isValid = true;
	// std::vector <Book> library;
	int count = 1;
	getline(myfStream, line);
	while (getline(myfStream, line)) {
		if (std::count(line.begin(), line.end(), ';') == 7) {

			std::stringstream myStrStream(line);

			getline(myStrStream, ISBN, ';');
			ISBN = ISBN.substr(1, ISBN.length() - 2);

			getline(myStrStream, title, ';');

			title = title.substr(1, title.length() - 2);

			getline(myStrStream, author, ';');
			author = author.substr(1, author.length() - 2);

			getline(myStrStream, year, ';');
			year = year.substr(1, year.length() - 2);

			getline(myStrStream, publisher, ';');
			publisher = publisher.substr(1, publisher.length() - 2);

			getline(myStrStream, junk, '\n');

			for (int i = 0; i < ISBN.length(); i++) {
				if (!isdigit(ISBN[i]) && ISBN[i] != 88)
					isValid = false;
			}
			for (int i = 0; i < year.length(); i++) {
				if (!isdigit(year[i]))
					isValid = false;
			}
			
			for (int i = 0; i < title.length(); i++) {
				if (title[i] > 126 || title[i] < 32)
					isValid = false;
			}
			for (int i = 0; i < author.length(); i++) {
				if (author[i] > 126 || author[i] < 32)
					isValid = false;
			}
			for (int i = 0; i < publisher.length(); i++) {
				if (publisher[i] > 126 || publisher[i] < 32)
					isValid = false;
			}
			

			if (isValid)
			    library.emplace_back(ISBN, title, author, stoi(year), publisher);
		}
		isValid = true;
		count++;
	}

	myfStream.close();

	/*
    int count2 = 1;
	for (Book b : library) {
		std::cout << count2 << " ";
		b.printData();
		count2++;
	}
    */
}