#ifndef SRC_LIBRARY_H
#define SRC_LIBRARY_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
// #include "Book.h" 

template <typename T>
class Library {
    private: 
        struct Book {
            int year;
	        std::string ISBN, title, author, publisher;

            Book(std::string myISBN, std::string myTitle, std::string myAuthor, int myYear, std::string myPublisher) {
                ISBN = myISBN;
	            title = myTitle;
	            author = myAuthor;
	            year = myYear;
	            publisher = myPublisher;
            }
        };

        std::vector<Book> library;
        // ==== PRIVATE HELPER FUNCTIONS ==== //
        void helperTimSort(std::vector<T> vals); 
        void insertionSort(std::vector<T>& vals, int left, int right);
        void merge(std::vector<T>& vals, int left, int mid, int right);
        
    public: 
         
        // ==== SORTING ALGORITHMS ==== //
        void timSort(std::string type);

        // ==== READ AND PRINT ==== //
        void readFile();
        void printData();
        
};

template <typename T>
void Library<T>::insertionSort(std::vector<T>& vals, int left, int right) {
    for (int i = left + 1; i <= right; i++) { // first element is always placed in sorted
		T key = vals[i];
		int j = i - 1; 

		// Compare key with each element in sorted till smaller val is found
		while (key < vals[j] && j >= left) {
			vals[j + 1] = vals[j]; 
			j--;
		}
		vals[j + 1] = key;
	}
}

template <typename T>
void Library<T>::merge(std::vector<T>& vals, int left, int mid, int right) {
    // Split vals in half: X is first half, Y is second half
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> X;
    std::vector<T> Y;

    for (int i = 0; i < n1; i++)
        X.push_back(vals[left + i]);
    for (int j = 0; j < n2; j++) 
        Y.push_back(vals[mid + 1 + j]); 

    // Merge the vectors X and Y into vals
    int i, j, k;
    i = 0;
    j = 0; 
    k = left;

    while (i < n1 && j < n2) {
        if(X[i] <= Y[j]) {
            vals[k] = X[i];
            i++;
        }

        else {
            vals[k] = Y[j];
            j++;
        }

        k++;
    }   

    // When we run out of elements in either X or Y, append the remaining elements
    while (i < n1) {
        vals[k] = X[i];
        i++;
        k++;
    }   
    while (j < n2) {
        vals[k] = Y[j];
        j++;
        k++;
    } 
}

template <typename T>
void Library<T>::helperTimSort(std::vector<T> vals) {
    int run = 32;

    // 1. Insertion sort on subarrays of size = run
    for (int i = 0; i < vals.size(); i += run)
        insertionSort(vals, i, std::min((i + run - 1), ((int)vals.size() - 1)));

    // 2. Start merging from size = run 
    for (int size = run; size < vals.size(); size = 2 * size) {
        for (int left = 0; left < vals.size(); left += 2 * size)
        {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), ((int)vals.size() - 1));

            if(mid < right)
                merge(vals, left, mid, right);
        }
    }
}

template <typename T>
void Library<T>::timSort(std::string type) {
    /*
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
    */
    
    helperTimSort(library);
    
}

template <typename T>
void Library<T>::readFile() {
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

template <typename T>
void Library<T>::printData()
{
	std::cout << "ISBN: " << Book::ISBN << "\t" << "Title: " << Book::title << "\t" << "Author: " << Book::author << "\t" << "Year: " << Book::year << "\t" << "Publisher: " << Book::publisher << std::endl;
}

#endif