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