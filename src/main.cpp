#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Library.h"

int main() {
    Library library;
    library.readFile();

    std::cout << "Welcome to GatorBooks!" << std::endl;
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

        std::string data;
        std::cout << "Search for... (enter a string): ";
        std::cin.ignore();
        std::getline(std::cin, data);
        
        std::cout << std::endl;

        std::cout << "What sort would you like to use? Choose an option from 1-2." << std::endl;
        std::cout << "1. Timsort" << std::endl << "2. Radix sort" << std::endl;
        int sortOption;
        std::cin >> sortOption;

        if (sortOption > 2) {
            std::cout << "Please select a valid option." << std::endl;
            continue;
        }

        if (searchOption == 1 && sortOption == 1)
            library.timSort("ISBN", data);

        else if (searchOption == 1 && sortOption == 2)
            library.radixSortString("ISBN", data);

        else if (searchOption == 2 && sortOption == 1)
            library.timSort("title", data);
        
        else if (searchOption == 2 && sortOption == 2)
            library.radixSortString("title", data);

        else if (searchOption == 3 && sortOption == 1)
            library.timSort("author", data);

        else if (searchOption == 3 && sortOption == 2)
            library.radixSortString("author", data);

        else if (searchOption == 4 && sortOption == 1)
            library.timSort("publisher", data);

        else if (searchOption == 4 && sortOption == 2)
            library.radixSortString("publisher", data);

        else if (searchOption == 5 && sortOption == 1)
            library.timSort("year", data);

        else if (searchOption == 5 && sortOption == 2)
            library.radixSortInt("year", data);

        std::cout << "Continue searching? (Y/N)" << std::endl;
        char cont;
        std::cin >> cont;
        if (cont == 'Y' || cont == 'y')
            continue;
        else if (cont == 'N' || cont == 'n') {
            std::cout << "Thank you for using GatorBooks!" << std::endl;
            exit = true;
        }    

    }

    return 0;
}

