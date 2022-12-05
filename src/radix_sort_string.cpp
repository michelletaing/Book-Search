/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

void countingSortString(std::vector<std::string>& inputVector, int letterPlace){

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

int findMinStringLength(std::vector<std::string> inputVector){
    int minSize = INT_MAX;

    for (int i = 0; i < inputVector.size(); i++){
        if (inputVector[i].size() < minSize){
            minSize = inputVector[i].size();
        }
    }
    return minSize;
}

void radixSortString(std::vector<std::string>& inputVector){
    
    int minSize = findMinStringLength(inputVector);

    for (int i = minSize - 1; i >= 0; i--){
        countingSortString(inputVector, i);
    }
}

int main(){

    std::vector<std::string> inputVector = {"123", "123456", "6532", "24646777", "2466426", "1", "0"};

    radixSortString(inputVector);



    return 0;
}
*/