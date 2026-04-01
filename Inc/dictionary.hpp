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

        int partitionWordsAroundPivotForQuicksort(
            int first_index,
            int last_index);
        // Partitions words for quicksort using the last item as pivot

        void quicksortWordsInRange(int first_index, int last_index);
        // Recursively applies quicksort to words in [first_index, last_index]

    public:
        void store(const std::string& filename);
        // Reads all words from filename into the dictionary
        // assumptions - filename points to a readable text file

        void sort(void);
        // Sorts the dictionary words using selection sort

        void sortWordsUsingQuicksortAlgorithm(void);
        // Sorts dictionary words using the quicksort algorithm

        void sortWordsUsingHeapsortAlgorithm(void);
        // Sorts dictionary words using the heapsort algorithm

        int find(const std::string& target) const;
        // Searches for target using binary search and returns its index
        // returns - index if found, -1 otherwise
        // assumptions - dictionary is already sorted

        friend std::ostream& operator<<(
            std::ostream& os, const dictionary& dict);
        // Overloaded << to print all stored words
};