#ifndef LAB_SISTEMI_MATRIX_H
#define LAB_SISTEMI_MATRIX_H

#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;


template <class T>

class matrix {
private:
    unsigned rows = 0, columns = 0;
    T* m;

    void init(T value) {
        for (int i=0; i<rows; ++i)
            for (int j=0; j<columns; ++j)
                m[i+j] = value;
    }

    size_t index(int i, int j) const {return j + columns * i;}

    /**
     * @returns index of first non zero number on the same column, starting from m[row][col], or -1
     * if not found
     */

    int firstNonZeroRow(int row, int col){
        int k = row * columns + col;
        if (k >= rows * columns)
            return -1;
        if (m[k] !=0)
            return k;
        return firstNonZeroRow(row, col + columns);
    }

    void swapRows(int row1, int row2){
        T tmp;
        for (int j=0; j<columns; ++j){
            tmp = m[j + columns * row1];
            m[j + columns * row1] = m[j + columns * row2];
            m[j + columns * row2] = tmp;
        }
    }

public:

    matrix(unsigned int rows, unsigned int columns) : rows(rows), columns(columns){
        m = new T[rows * columns];
        init(0);
    }

    matrix(unsigned int rows, unsigned int columns, T* m) : rows(rows), columns(columns), m(m){}


    inline unsigned int getRows() const { return this->rows; }
    inline unsigned int getCols() const { return this->columns; }

    void print(){
        if (m == nullptr)
            return;
        int a;
        for (int i=0; i<rows; ++i) {
            for (int j=0; j < columns; ++j) {
                cout << " " << m[index(i,j)];
            }
            cout << endl;
        }
        cout << endl;
    }
};


#endif