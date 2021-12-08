#ifndef LAB_SISTEMI_MATRIX_H
#define LAB_SISTEMI_MATRIX_H
//#define DEBUG
#define SHOW_CANCELLATION
#define GAUSS

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

    void rowSum( int row_p, int row_i, T lambda){
        for (int j=0; j<columns; ++j){
            T a = m[index(row_i,j)];
            m[index(row_i, j)] = m[index(row_i, j)] + lambda * m[index(row_p,j)];
        }
    }

    int findPivot(int row, int col){
        int i;
        while((i=firstNonZeroRow(row, col))== -1 && col < columns) col++;
        if (i!= -1){
            if (row!= i/columns){
                swapRows(row, i/columns);
#ifdef SHOW_CANCELLATION
                print();
#endif
            }
            i = row;
        }
        return index(i, col);
    }

    void applyE(int p){
        int i=p+columns;
        T lambda;
        while(i<rows * columns) {
            if (m[i] != 0) {
                lambda = - m[i]/m[p];
                rowSum(p/columns,i/columns, lambda);
#ifdef SHOW_CANCELLATION
                print();
#endif
            }
            i+= columns;
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

    void gauss(){
        int row = 0, col = 0, i;
        while(col < columns - 1 && row < rows - 1  && (i=findPivot(row, col)) != -1){
            applyE(i);
            col++;row++;
        };
    }
};


#endif