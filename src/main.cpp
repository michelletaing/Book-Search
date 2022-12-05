#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Library.h"

int main() {
    Library library;
    library.readFile();
    library.timSort("author");

    return 0;
}

