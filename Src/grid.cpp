#include "grid.hpp"

void grid::read_grid(const std::string& filename) {
    std::ifstream in(filename);

    /* Make sure the file can be opened. */
    if(!in) {
        throw fileOpenError(filename);
    }
    in >> _rows >> _cols;

    /* Make sure the grid schema is valid. */
    if(!in || _rows <= 0 || _cols <= 0) {
        throw fileError("Invalid grid dimensions");
    }

    /* Clear the matrix and resize it to the current rows/cols. */
    _matrix.clear();
    _matrix.resize(_rows, std::vector<char>(_cols));

    /* Populate the matrix with the file contents. */
    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _cols; j++) {
            if(!(in >> _matrix[i][j])) {
                throw fileError("Not enough grid characters in file");
            }
        }
    }
}

char grid::get(int r, int c) const {
    /* Make sure the input is vailid. */
    if(r < 0 || r >= _rows || c < 0 || c >= _cols) {
        throw indexRangeError("Grid index out of range", r, _rows);
    }

    /* Return the element at that r/c pair. */
    return _matrix[r][c];
}

std::ostream& operator<<(std::ostream& os, const grid& g) {
    for(int i = 0; i < g._rows; i++) {
        for(int j = 0; j < g._cols; j++) {
            os << g._matrix[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}