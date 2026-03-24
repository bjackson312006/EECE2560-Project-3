//
// Brian Mack, Juan Ipina, Blake Jackson, James Su
// Project #3 Word Search
// Header for the grid class (stores and provides access to puzzle letters)
//
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "d_except.h"

class grid
{
    private:
        std::vector<std::vector<char>> _matrix; // Grid letters
        int _rows;                              // Row count
        int _cols;                              // Column count
    public:
        grid() : _rows(0), _cols(0) {}
        // Default constructor that initializes an empty grid

        void read_grid(const std::string& filename);
        // Reads grid dimensions and letters from filename
        // assumptions - filename points to a valid grid input file

        char get(int r, int c) const;
        // Returns the character at row r and column c
        // assumptions - r and c are within the grid bounds

        /* Helpers */
        int num_rows(void) const { return _rows; };
        // Gets the number of rows in the matrix

        int num_cols(void) const { return _cols; };
        // Gets the number of columns in the matrix

        /* Helper << overload to print out the matrix. */
        friend std::ostream& operator<<(std::ostream& os, const grid& g);
        // Overloaded << to print the grid contents
};