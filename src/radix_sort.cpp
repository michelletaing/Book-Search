/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

//STARTS AT THE ONES PLACE, THEN TENS, ETC.
//THIS IS AN LSD RADIX SORT
void countingSortInt(std::vector<int>& inputVector, int digitPlace){

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

void radixSortInt(std::vector<int>& inputVector){
    
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

int main(){

    std::vector<int> inputVector = {6531, 8623, 5944, 95, 8159, 915, 1519, 9859, 2077, 5942};

    auto start = std::chrono::high_resolution_clock::now();
    radixSortInt(inputVector);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    for (auto& element: inputVector){
        std::cout << element << std::endl;
    }

    double seconds = ((double)duration.count()) / ((double) 1000000);

    std::cout << "Radix Sort (Integers) was completed in: " << duration.count() << " microseconds" << " or " << seconds << " seconds." << std::endl;

    return 0;
}
*/
