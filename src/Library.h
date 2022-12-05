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
        void helperTimSort(std::vector<T>& vals);
        template <typename T> 
        void insertionSort(std::vector<T>& vals, int left, int right);
        template <typename T>
        void merge(std::vector<T>& vals, int left, int mid, int right);

        // Radix - int
        void helperRadixSortInt(std::vector<int>& inputVector);
        void countingSortInt(std::vector<int>& inputVector, int digitPlace);

        // Radix - string
        void helperRadixSortString(std::vector<std::string>& inputVector);
        void countingSortString(std::vector<std::string>& inputVector, int letterPlace);
        int findMinStringLength(std::vector<std::string> inputVector);

        // Print
        template <typename T>
        void printData(std::vector<T>& library, int n);
        
    public: 
         
        // ==== SORTING ALGORITHMS ==== //
        void timSort(std::string type);
        void radixSortString(std::string type);
        void radixSortInt(std::string type);

        // ==== READ AND PRINT ==== //
        void readFile();
        
};

template <typename T>
void Library::insertionSort(std::vector<T>& vals, int left, int right) {
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
void Library::merge(std::vector<T>& vals, int left, int mid, int right) {
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
void Library::helperTimSort(std::vector<T>& vals) {
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
void Library::printData(std::vector<T>& library, int n) {
    for (int i = 0; i < n; i++)
        std::cout << library[i] << std::endl;
}

#endif