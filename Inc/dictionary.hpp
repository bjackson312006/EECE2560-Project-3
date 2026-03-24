//
// Brian Mack, Juan Ipina, Blake Jackson, James Su
// Project #3 Word Search
// Header for the dictionary class
// (stores words and supports sort/find operations)
//
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "d_except.h"

class dictionary
{
    private:
        std::vector<std::string> _words; // Stored dictionary words

    public:
        void store(const std::string& filename);
        // Reads all words from filename into the dictionary
        // assumptions - filename points to a readable text file

        void sort(void);
        // Sorts the dictionary words using selection sort

        int find(const std::string& target) const;
        // Searches for target using binary search and returns its index
        // returns - index if found, -1 otherwise
        // assumptions - dictionary is already sorted

        friend std::ostream& operator<<(
            std::ostream& os, const dictionary& dict);
        // Overloaded << to print all stored words
};