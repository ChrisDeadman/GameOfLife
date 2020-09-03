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

    Matrix2D(const Matrix2D &that) = delete; // Forbid copying

    unsigned int getRows() const {
        return rows;
    }

    unsigned int getColumns() const {
        return columns;
    }

    bool contains(const unsigned int row, const unsigned int column) const {
        return (row < rows) && (column < columns);
    }

    T &getValue(const unsigned int row, const unsigned int column) {
        if (!contains(row, column)) {
            throw std::out_of_range("row/column out of bounds");
        }

        return data[(row * columns) + column];
    }

    void setValue(const unsigned int row, const unsigned int column, const T &value) {
        if (!contains(row, column)) {
            throw std::out_of_range("row/column out of bounds");
        }

        data[(row * columns) + column] = value;
    }
};

#endif //GAMEOFLIFE_MATRIX2D_H
