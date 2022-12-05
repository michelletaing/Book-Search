#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Book.h"
using namespace std;

Book::Book(string myISBN, string myTitle, string myAuthor, int myYear, string myPublisher)
{
	ISBN = myISBN;
	title = myTitle;
	author = myAuthor;
	year = myYear;
	publisher = myPublisher;
}

void Book::readFile(string fileName) {
    ifstream myfStream;
	myfStream.open("books.csv");
	if (!myfStream.is_open())
		cout << "File failed to load" << endl;
	string ISBN, title, author, year, publisher, junk;

	string line;
	bool isValid = true;
	vector <Book> library;
	int count = 1;
	getline(myfStream, line);
	while (getline(myfStream, line)) {
		if (std::count(line.begin(), line.end(), ';') == 7) {

			stringstream myStrStream(line);

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

	
	int count2 = 1;
	for (Book b : library) {
		cout << count2 << " ";
		b.printData();
		count2++;
	}
}

void Book::printData()
{
	cout << "ISBN: " << ISBN << "\t" << "Title: " << title << "\t" << "Author: " << author << "\t" << "Year: " << year << "\t" << "Publisher: " << publisher << endl;
}