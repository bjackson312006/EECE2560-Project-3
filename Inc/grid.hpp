#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "d_except.h"

class grid {
    private:
        std::vector<std::vector<char>> _matrix;
        int _rows;
        int _cols;
    public:
        grid() : _rows(0), _cols(0) {}

        void read_grid(const std::string& filename); // Reads in a grid and stores it in the matrix
        char get(int r, int c) const; // Reads a specific element in the matrix

        /* Helpers */
        int num_rows(void) const { return _rows; }; // Gets the number of rows in the matrix
        int num_cols(void) const { return _cols; }; // Gets the number of columns in the matrix

        /* Helper << overload to print out the matrix. */
        friend std::ostream& operator<<(std::ostream& os, const grid& g);
};