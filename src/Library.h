#ifndef SRC_LIBRARY_H
#define SRC_LIBRARY_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

// Remove all templates
// template <typename T>
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
        // Timsort
        template <typename T>
        void helperTimSort(std::vector<T>& vals, std::string type);
        template <typename T> 
        void insertionSort(std::vector<T>& vals, int left, int right, std::string type);
        template <typename T>
        void merge(std::vector<T>& vals, int left, int mid, int right, std::string type);

        // Radix - int
        void helperRadixSortInt(std::vector<int>& inputVector);
        void countingSortInt(std::vector<int>& inputVector, int digitPlace);

        // Radix - string
        void helperRadixSortString(std::vector<std::string>& inputVector);
        void countingSortString(std::vector<std::string>& inputVector, int letterPlace);
        int findMaxStringLength(std::vector<std::string> inputVector);
        int getASCII(std::string input, int letterIndex);

        // Print
        void printData(std::vector<Book>& library, std::string type);

        // Test
        template <typename T>
        void testPrint(std::vector<T>& vals, int n);
        void helperTestSort(std::vector<Book>& library);

        
    public: 
         
        // ==== SORTING ALGORITHMS ==== //
        void timSort(std::string type);
        void radixSortString(std::string type);
        void radixSortInt(std::string type);

        // ==== READ AND PRINT ==== //
        void readFile();

        // ==== TEST ===== //
        void testSort();
        
};

template <typename T>
void Library::insertionSort(std::vector<T>& vals, int left, int right, std::string type) {
    for (int i = left + 1; i <= right; i++) { // first element is always placed in sorted
		T key = vals[i];
		int j = i - 1; 

		// Compare key with each element in sorted till smaller val is found
        if (type == "ISBN") {
            while (key.ISBN < vals[j].ISBN && j >= left) {
			    vals[j + 1] = vals[j]; 
			    j--;
		    }
        }
        else if (type == "author") {
            while (key.author < vals[j].author && j >= left) {
			    vals[j + 1] = vals[j]; 
			    j--;
		    }
        }
        else if (type == "title") {
            while (key.title < vals[j].title && j >= left) {
			    vals[j + 1] = vals[j]; 
			    j--;
		    }
        }
        else if (type == "publisher") {
            while (key.publisher < vals[j].publisher && j >= left) {
			    vals[j + 1] = vals[j]; 
			    j--;
		    }
        }
        else if (type == "year") {
            while (key.year < vals[j].year && j >= left) {
			    vals[j + 1] = vals[j]; 
			    j--;
		    }
        }

		vals[j + 1] = key;
	}
}

template <typename T>
void Library::merge(std::vector<T>& vals, int left, int mid, int right, std::string type) {
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
        if (type == "ISBN") {
            if(X[i].ISBN <= Y[j].ISBN) {
                vals[k] = X[i];
                i++;
            }
            else {
                vals[k] = Y[j];
                j++;
            }
        }
        else if (type == "author") {
            if(X[i].author <= Y[j].author) {
                vals[k] = X[i];
                i++;
            }
            else {
                vals[k] = Y[j];
                j++;
            }
        }
        else if (type == "title") {
            if(X[i].title <= Y[j].title) {
                vals[k] = X[i];
                i++;
            }
            else {
                vals[k] = Y[j];
                j++;
            }
        }
        else if (type == "publisher") {
            if(X[i].publisher <= Y[j].publisher) {
                vals[k] = X[i];
                i++;
            }
            else {
                vals[k] = Y[j];
                j++;
            }
        }
        else if (type == "year") {
            if(X[i].year <= Y[j].year) {
                vals[k] = X[i];
                i++;
            }
            else {
                vals[k] = Y[j];
                j++;
            }
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
void Library::helperTimSort(std::vector<T>& vals, std::string type) {
    int run = 32;

    // 1. Insertion sort on subarrays of size = run
    for (int i = 0; i < vals.size(); i += run)
        insertionSort(vals, i, std::min((i + run - 1), ((int)vals.size() - 1)), type);

    // 2. Start merging from size = run 
    for (int size = run; size < vals.size(); size = 2 * size) {
        for (int left = 0; left < vals.size(); left += 2 * size)
        {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), ((int)vals.size() - 1));

            if(mid < right)
                merge(vals, left, mid, right, type);
        }
    }
}

// ===== TEST ===== //
template <typename T> 
void Library::testPrint(std::vector<T>& vals, int n) {
    for (int i = 0; i < n; i++)
        std::cout << vals[i] << std::endl;
}


#endif