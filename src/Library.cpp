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
    helperRadixSortString(strings);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	double seconds = ((double)duration.count()) / ((double) 1000000);

	std::cout << "Radix Sort (Integers) was completed in: " << duration.count() << " microseconds" << " or " << seconds << " seconds." << std::endl;
}

void Library::helperRadixSortString(std::vector<std::string>& inputVector) {
	int minSize = findMinStringLength(inputVector);

    for (int i = minSize - 1; i >= 0; i--){
        countingSortString(inputVector, i);
    }

	printData(inputVector, 300);
}

void Library::countingSortString(std::vector<std::string>& inputVector, int letterPlace) {
	std::string* resultArray = new std::string[inputVector.size() + 1];
    int letterCount[256] = {0};

    for (int i = 0; i < inputVector.size(); i++){
        
        //GET EACH CHARACTER'S ASCII
        char digit = inputVector[i][letterPlace];
        int num = int(digit);

        letterCount[num]++;
    }

    //GO THROUGH THE LETTERCOUNT ARRAY AND CALCULATE THE CUMULATIVE FREQUENCY
    for (int i = 0; i < 256; i++){
        //FOR EACH INDEX, ADD THE VALUE OF THE ELEMENT BEFORE TO THE CURRENT ELEMENT
        letterCount[i] += letterCount[i - 1];
    }

    for (int i = inputVector.size() - 1; i >= 0; i--){
        //STARTING FROM THE BACK OF THE INPUTVECTOR, MOVE EACH ELEMENT TO THEIR RESPECTIVE LOCATION BASED ON THE LETTERCOUNT ARRAY
        char letterASCII = inputVector[i][letterPlace];
        int num = int(letterASCII);

        resultArray[letterCount[num] - 1] = inputVector[i];

        //DECREMENT THE COUNT BY ONE
        letterCount[letterASCII]--;
    }
    
    //TRANSFER THE RESULT INTO THE INPUT ARRAY
    for (int i = 0; i < inputVector.size(); i++){
        inputVector[i] = resultArray[i];
    }

    //DELETE THE DYNAMICALLY ALLOCATED ARRAY
    delete[] resultArray;
}

int Library::findMinStringLength(std::vector<std::string> inputVector) {
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

	std::cout << "Radix Sort (Integers) was completed in: " << duration.count() << " microseconds" << " or " << seconds << " seconds." << std::endl;
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
	
	printData(inputVector, 300);

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
    if (type == "author" || type == "title" || type == "publisher" || type == "ISBN") {
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
        
        helperTimSort(strings);
    }
        
    else {
        std::vector<int> ints;

        for (int i = 0; i < library.size(); i++)
            ints.push_back(library[i].year);

        helperTimSort(ints);

    }
    
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

	/*
    int count2 = 1;
	for (Book b : library) {
		std::cout << count2 << " ";
		b.printData();
		count2++;
	}
    */
}