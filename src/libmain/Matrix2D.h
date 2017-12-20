#ifndef GAMEOFLIFE_MATRIX2D_H
#define GAMEOFLIFE_MATRIX2D_H

#include <vector>
#include <stdexcept>

template<typename T>
class Matrix2D {
private:
    std::vector<T> data;
    const unsigned int rows;
    const unsigned int columns;

public:
    Matrix2D(const unsigned int rows, const unsigned int columns)
            : rows(rows), columns(columns) {
        data.resize(rows * columns);
    }

    T &operator()(const int row, const int column) {
        if ((row < 0) || (row >= rows) || (column < 0) || (column >= columns)) {
            throw std::out_of_range("row/column out of bounds");
        }

        return data[(row * columns) + column];
    }
};

#endif //GAMEOFLIFE_MATRIX2D_H
