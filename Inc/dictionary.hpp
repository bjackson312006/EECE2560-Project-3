#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "d_except.h"

class dictionary {
    private:
        std::vector<std::string> _words;

    public:
        void store(const std::string& filename); // Reads in a file of strings, and
        void sort(void); // Sorts the dictionary using selectionSort
        int find(const std::string& target) const; // Searches for a specific target in the dictionary. Can only be used if the dicitonary is already sorted. Returns the index of the target in the dictionary, or -1 if not found.

        friend std::ostream& operator<<(std::ostream& os, const dictionary& dict); // Friend overload for << to print out the dictionary's contents (i.e., whatever's in the array).
};