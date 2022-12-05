#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Library.h"

int main() {
    Library library;
    library.readFile();

    std::cout << "Welcome to GatorBooks!" << std::endl;
    // Menu starts here
    bool exit = false;
    while(!exit) {
        std::cout << "What would you like to search for? Choose an option from 1-5." << std::endl;
        std::cout << "1. ISBN" << std::endl << "2. Title" << std::endl << "3. Author" << std::endl << "4. Publisher" << std::endl << "5. Year" << std::endl;
        int searchOption;
        std::cin >> searchOption;

        if (searchOption > 5) {
            std::cout << "Please select a valid option." << std::endl;
            continue;
        }

        std::cout << "What sort would you like to use? Choose an option from 1-2." << std::endl;
        std::cout << "1. Timsort" << std::endl << "2. Radix sort" << std::endl;
        int sortOption;
        std::cin >> sortOption;

        if (sortOption > 2) {
            std::cout << "Please select a valid option." << std::endl;
            continue;
        }

        
        if (searchOption == 1 && sortOption == 1) {
            library.timSort("ISBN");
            // search + print ISBN
        }

        else if (searchOption == 1 && sortOption == 2) {
            library.radixSortString("ISBN");
        }

        else if (searchOption == 2 && sortOption == 1) {
            library.timSort("title");
            // search title(s)
        }
        
        else if (searchOption == 2 && sortOption == 2) {
            library.radixSortString("title");
            
        }
        


        std::cout << "Continue searching? (Y/N)" << std::endl;
        char cont;
        std::cin >> cont;
        if (cont == 'Y')
            continue;
        else {
            std::cout << "Thank you for using GatorHours!" << std::endl;
            exit = true;
        }    

    }

    return 0;
}

