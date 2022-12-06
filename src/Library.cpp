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
void Library::radixSortString(std::string type) {
	std::vector<std::string> strings;

    for (int i = 0; i < library.size(); i++) {
        if (type == "author")
            strings.push_back(library[i].author);
        if (type == "title")
            strings.push_back(library[i].title);
		if (type == "ISBN")
			strings.push_back(library[i].ISBN);	
		if (type == "publisher")
			strings.push_back(library[i].publisher);			   
    }

	auto start = std::chrono::high_resolution_clock::now();    
    // helperRadixSortString(strings);
	helperRadixSortString(strings);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	double seconds = ((double)duration.count()) / ((double) 1000000);

	testPrint(strings, 300);

	std::cout << "Radix Sort was completed in: " << duration.count() << " microseconds" << " or " << seconds << " seconds." << std::endl;
}

void Library::helperRadixSortString(std::vector<std::string>& inputVector) {
	int maxSize = findMaxStringLength(inputVector);

    for (int i = maxSize - 1; i >= 0; i--){
        countingSortString(inputVector, i);
    }
}

void Library::countingSortString(std::vector<std::string>& inputVector, int letterPlace) {
	std::string* resultArray = new std::string[inputVector.size()];

    int letterCount[257] = {0};

    for (std::string value : inputVector){
		letterCount[getASCII(value, letterPlace)]++;
	}

    //GO THROUGH THE LETTERCOUNT ARRAY AND CALCULATE THE CUMULATIVE FREQUENCY
    for (int i = 1; i < 257; i++){
        //FOR EACH INDEX, ADD THE VALUE OF THE ELEMENT BEFORE TO THE CURRENT ELEMENT
        letterCount[i] += letterCount[i - 1];
    }

    for (int i = inputVector.size() - 1; i >= 0; i--){
        resultArray[--letterCount[getASCII(inputVector[i], letterPlace)]] = inputVector[i];
    }
    
	for (int i = 0; i < inputVector.size(); i++){
		inputVector[i] = resultArray[i];
	}
    
	delete[] resultArray;
}

int Library::findMaxStringLength(std::vector<std::string> inputVector) {
	int minSize = INT_MAX;

    for (int i = 0; i < inputVector.size(); i++){
        if (inputVector[i].size() < minSize){
            minSize = inputVector[i].size();
        }
    }
    return minSize;
}

// ===== RADIX SORT (INT) ===== //
void Library::radixSortInt(std::string type) {
	std::vector<int> ints;

    for (int i = 0; i < library.size(); i++)
        ints.push_back(library[i].year);

	auto start = std::chrono::high_resolution_clock::now(); 
    helperRadixSortInt(ints);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	double seconds = ((double)duration.count()) / ((double) 1000000);

	testPrint(ints, 300);

	std::cout << "Radix Sort was completed in: " << duration.count() << " microseconds" << " or " << seconds << " seconds." << std::endl;
}

void Library::helperRadixSortInt(std::vector<int>& inputVector) {
	//FIRST DETERMINE THE MAXIMUM VALUE IN THE VECTOR AS THIS WILL BE THE AMOUNT OF TIMES THE SORT WILL EXECUTE
    //MAX_ELEMENT WAS DERIVED FROM THE CPLUSPLUS WEBSITE
    auto it = std::max_element(inputVector.begin(), inputVector.end());
    int maxVal = *it;

    //EXECUTE THE COUNTING SORT PORTION EQUAL TO THE NUMBER OF PLACES IN THE LARGEST ELEMENT
    //GOES UNTIL THE VALUE OF DIGITSPLACE IS LARGER THAN THE MAXVAL (RESULTING IN 0 AND BREAKING THE LOOP)
    for (int digitPlace = 1; maxVal / digitPlace > 0; digitPlace *= 10){
        countingSortInt(inputVector, digitPlace);
    }
}

void Library::countingSortInt(std::vector<int>& inputVector, int digitPlace) {
	int* resultArray = new int[inputVector.size() + 1];
    int digitCount[10] = {0};

    for (int i = 0; i < inputVector.size(); i++){
        //KEEP A COUNT OF EACH DIGIT (FOR A SPECIFIC PLACE) IN THE INPUTVECTOR
        int digit = (inputVector[i] / digitPlace) % 10;
        digitCount[digit]++;
    }

    //GO THROUGH THE DIGITCOUNT ARRAY AND CALCULATE THE CUMULATIVE FREQUENCY
    for (int i = 0; i < 10; i++){
        //FOR EACH INDEX, ADD THE VALUE OF THE ELEMENT BEFORE TO THE CURRENT ELEMENT
        digitCount[i] += digitCount[i - 1];
    }

    for (int i = inputVector.size() - 1; i >= 0; i--){
        //STARTING FROM THE BACK OF THE INPUTVECTOR, MOVE EACH ELEMENT TO THEIR RESPECTIVE LOCATION BASED ON THE DIGITCOUNT ARRAY
        int digit = (inputVector[i] / digitPlace) % 10;
        resultArray[digitCount[digit] - 1] = inputVector[i];

        //DECREMENT THE COUNT BY ONE
        digitCount[digit]--;
    }
    
    //TRANSFER THE RESULT INTO THE INPUT ARRAY
    for (int i = 0; i < inputVector.size(); i++){
        inputVector[i] = resultArray[i];
    }

    //DELETE THE DYNAMICALLY ALLOCATED ARRAY
    delete[] resultArray;
}


// ===== TIM SORT ===== //
void Library::timSort(std::string type) {
	auto start = std::chrono::high_resolution_clock::now();
	helperTimSort(library, type);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	double seconds = ((double)duration.count()) / ((double) 1000000);

	printData(library, type);

	std::cout << "Timsort was completed in: " << duration.count() << " microseconds" << " or " << seconds << " seconds." << std::endl;
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

// ===== PRINT ===== //
void Library::printData(std::vector<Book>& library, std::string type) {
    for (int i = 20000; i < 20100; i++) {
		/*
		if (type == "title")
			std::cout << library[i].title << std::endl;
		else if (type == "author")
			std::cout << library[i].author << std::endl;
		else if (type == "ISBN")
			std::cout << library[i].ISBN << std::endl;
		else if (type == "publisher")
			std::cout << library[i].publisher << std::endl;
		else if (type == "year")
			std::cout << library[i].year << std::endl;
		*/

		if (type == "year" && library[i].year == 0)
			continue;

		std::cout << "Title: " << library[i].title << std::endl;
		std::cout << "Author: " << library[i].author << std::endl;
		std::cout << "Year: " << library[i].year << std::endl;
		std::cout << "ISBN: " << library[i].ISBN << std::endl;	
		std::cout << "Publisher: " << library[i].publisher << std::endl << std::endl;
			
	}
        

}

// ===== TEST ===== //
void Library::testSort() {
	helperTestSort(library);
}

void Library::helperTestSort(std::vector<Book>& library) {
	std::vector<std::string> data;
	for (int i = 0; i < library.size(); i++) {
		data.push_back(library[i].ISBN);
	}

	std::sort(data.begin(), data.end());

	for (int i = 0; i < 300; i++) {
		std::cout << data[i] << std::endl;
	}
}