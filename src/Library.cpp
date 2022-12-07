#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>
#include "Library.h"

// ===== RADIX SORT (STRING) ===== //
void Library::radixSortString(std::string type, std::string find) {
	auto start = std::chrono::high_resolution_clock::now();
	if (type == "author" || type == "title" || type == "year" || type == "publisher")    
		helperRadixSortString(library, "title");
	else
		helperRadixSortString(library, type);	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	double seconds = ((double)duration.count()) / ((double) 1000000);

	findData(find, type);
	std::cout << "Radix Sort was completed in: " << duration.count() << " microseconds" << " or " << seconds << " seconds." << std::endl << std::endl;
	
}

void Library::helperRadixSortString(std::vector<Book>& library, std::string type) {
	int minSize = findMinStringLength(library, type);

    for (int i = minSize - 1; i >= 0; i--)
        countingSortString(library, i, type);
}

void Library::countingSortString(std::vector<Book>& library, int letterPlace, std::string type) {
	Book* resultArray = new Book[library.size()];

    int letterCount[257] = {0};

	if (type == "author") {
		for (int i = 0; i < library.size(); i++)
			letterCount[getASCII(library[i].author, letterPlace)]++;
	}

	if (type == "title"){
		for (int i = 0; i < library.size(); i++)
			letterCount[getASCII(library[i].title, letterPlace)]++;
	}

	if (type == "ISBN"){
		for (int i = 0; i < library.size(); i++)
			letterCount[getASCII(library[i].ISBN, letterPlace)]++;
	}

	if (type == "publisher"){
		for (int i = 0; i < library.size(); i++)
			letterCount[getASCII(library[i].publisher, letterPlace)]++;
	}

    //GO THROUGH THE LETTERCOUNT ARRAY AND CALCULATE THE CUMULATIVE FREQUENCY
    for (int i = 1; i < 257; i++) {
        //FOR EACH INDEX, ADD THE VALUE OF THE ELEMENT BEFORE TO THE CURRENT ELEMENT
        letterCount[i] += letterCount[i - 1];
    }

    for (int i = library.size() - 1; i >= 0; i--) {
		if (type == "author")
			resultArray[--letterCount[getASCII(library[i].author, letterPlace)]] = library[i];

		if (type == "title")
			resultArray[--letterCount[getASCII(library[i].title, letterPlace)]] = library[i];

		if (type == "ISBN")
			resultArray[--letterCount[getASCII(library[i].ISBN, letterPlace)]] = library[i];

		if (type == "publisher")
			resultArray[--letterCount[getASCII(library[i].publisher, letterPlace)]] = library[i];
    }
    
	for (int i = 0; i < library.size(); i++)
		library[i] = resultArray[i];
    
	delete[] resultArray;
}

int Library::getASCII(std::string input, int letterIndex){
	if (input.size() < letterIndex)
		return -1;
	else
		return input.at(letterIndex);
}

int Library::findMinStringLength(std::vector<Book>& library, std::string type) {
	int minSize = INT_MAX;

    for (int i = 0; i < library.size(); i++) {
		if (type == "author") {
			if (library[i].author.size() < minSize)
            	minSize = library[i].author.size();
		}

		if (type == "title"){
			if (library[i].title.size() < minSize)
            	minSize = library[i].title.size();
		}

		if (type == "ISBN"){
			if (library[i].ISBN.size() < minSize)
            	minSize = library[i].ISBN.size();
		}

		if (type == "publisher"){
			if (library[i].publisher.size() < minSize)
            	minSize = library[i].publisher.size();
		}		
    }

    return minSize;
}

// ===== RADIX SORT (INT) ===== //
void Library::radixSortInt(std::string type, std::string find) {
	auto start = std::chrono::high_resolution_clock::now(); 
    helperRadixSortInt(library);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	double seconds = ((double)duration.count()) / ((double) 1000000);

	findData(find, type);
	std::cout << "Radix Sort was completed in: " << duration.count() << " microseconds" << " or " << seconds << " seconds." << std::endl << std::endl;
}

void Library::helperRadixSortInt(std::vector<Book>& library) {
	//FIRST DETERMINE THE MAXIMUM VALUE IN THE VECTOR AS THIS WILL BE THE AMOUNT OF TIMES THE SORT WILL EXECUTE
	int maxVal = 0;

	for (int i = 0; i < library.size(); i++) {
		if (library[i].year > maxVal)
			maxVal = library[i].year;
	}

    //EXECUTE THE COUNTING SORT PORTION EQUAL TO THE NUMBER OF PLACES IN THE LARGEST ELEMENT
    //GOES UNTIL THE VALUE OF DIGITSPLACE IS LARGER THAN THE MAXVAL (RESULTING IN 0 AND BREAKING THE LOOP)
    for (int digitPlace = 1; maxVal / digitPlace > 0; digitPlace *= 10) 
        countingSortInt(library, digitPlace);
}

//THIS IS USED FOR SORTING THE YEARS
void Library::countingSortInt(std::vector<Book>& library, int digitPlace) {
	Book* resultArray = new Book[library.size() + 1];
    int digitCount[10] = {0};

    for (int i = 0; i < library.size(); i++) {
        //KEEP A COUNT OF EACH DIGIT (FOR A SPECIFIC PLACE) IN THE INPUTVECTOR
        int digit = (library[i].year / digitPlace) % 10;
        digitCount[digit]++;
    }

    //GO THROUGH THE DIGITCOUNT ARRAY AND CALCULATE THE CUMULATIVE FREQUENCY
    for (int i = 0; i < 10; i++) {
        //FOR EACH INDEX, ADD THE VALUE OF THE ELEMENT BEFORE TO THE CURRENT ELEMENT
        digitCount[i] += digitCount[i - 1];
    }

    for (int i = library.size() - 1; i >= 0; i--) {
        //STARTING FROM THE BACK OF THE INPUTVECTOR, MOVE EACH ELEMENT TO THEIR RESPECTIVE LOCATION BASED ON THE DIGITCOUNT ARRAY
        int digit = (library[i].year / digitPlace) % 10;
        resultArray[digitCount[digit] - 1] = library[i];

        //DECREMENT THE COUNT BY ONE
        digitCount[digit]--;
    }
    
    //TRANSFER THE RESULT INTO THE INPUT ARRAY
    for (int i = 0; i < library.size(); i++)
        library[i] = resultArray[i];

    //DELETE THE DYNAMICALLY ALLOCATED ARRAY
    delete[] resultArray;
}


// ===== TIM SORT ===== //
void Library::timSort(std::string type, std::string find) {
	auto start = std::chrono::high_resolution_clock::now();
	helperTimSort(library, "title");	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	double seconds = ((double)duration.count()) / ((double) 1000000);

	findData(find, type);
	std::cout << "Timsort was completed in: " << duration.count() << " microseconds" << " or " << seconds << " seconds." << std::endl << std::endl;
}

// ===== READ CSV ===== //
void Library::readFile() {
    std::ifstream myfStream;
	myfStream.open("books.csv");
	if (!myfStream.is_open())
		std::cout << "File failed to load" << std::endl;
	std::string ISBN, title, author, year, publisher, junk;

	std::string line;
	bool isValid = true;
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
			if(title[0] == 32){
				title = title.substr(1, title.length());
			}

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
}

std::string Library::makeLowerCase(std::string input){
	std::string returnString = "";

	for (int i = 0; i < input.size(); i++)
		returnString += tolower(input[i]);

	return returnString;
}

void Library::findData(std::string find, std::string type) {
	std::cout << "======== Search Results ========" << std::endl;

	std::string lowerCaseFind = makeLowerCase(find);

	std::vector<Book> found;
	for (int i = 0; i < library.size(); i++) {
		if (type == "title") {
			std::string lowerCaseBook = makeLowerCase(library[i].title);
			if (lowerCaseBook.find(lowerCaseFind) != std::string::npos)
				found.push_back(library[i]);
		}
			
		else if (type == "author") {
			std::string lowerCaseBook = makeLowerCase(library[i].author);
			if (lowerCaseBook.find(lowerCaseFind) != std::string::npos)
				found.push_back(library[i]);
		}
			
		else if (type == "ISBN") {
			std::string lowerCaseBook = makeLowerCase(library[i].ISBN);
			if (lowerCaseBook.find(lowerCaseFind) != std::string::npos)
				found.push_back(library[i]);	
		}
			
		else if (type == "publisher") {
			std::string lowerCaseBook = makeLowerCase(library[i].publisher);
			if (lowerCaseBook.find(lowerCaseFind) != std::string::npos)
				found.push_back(library[i]);
		}
			
		else if (type == "year") {
			if (library[i].year == stoi(find))
				found.push_back(library[i]);
		}
	}

	if (found.size() >= 10) {
		std::cout << "Viewing top 10 results..." << std::endl << std::endl;
		printData(found, type, 10);
	}
		
	else
		printData(found, type, found.size());
	
}

// ===== PRINT ===== //
void Library::printData(std::vector<Book>& lib, std::string type, int n) {
	if (lib.size() == 0) {
			std::cout << "No results found." << std::endl;
			return;
	}

    for (int i = 0; i < n; i++) {

		std::cout << "Title: " << lib[i].title << std::endl;
		std::cout << "Author: " << lib[i].author << std::endl;
		std::cout << "Year: " << lib[i].year << std::endl;
		std::cout << "ISBN: " << lib[i].ISBN << std::endl;	
		std::cout << "Publisher: " << lib[i].publisher << std::endl << std::endl;
		
	}
}

// ===== TEST ===== //
void Library::testSort() {
	helperTestSort(library);
}

void Library::helperTestSort(std::vector<Book>& library) {
	std::vector<std::string> data;
	for (int i = 0; i < library.size(); i++) {
		data.push_back(library[i].title);
	}

	std::sort(data.begin(), data.end());

	for (int i = 0; i < 300; i++) {
		std::cout << data[i] << std::endl;
	}
}