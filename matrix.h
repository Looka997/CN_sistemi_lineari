#ifndef LAB_SISTEMI_MATRIX_H
#define LAB_SISTEMI_MATRIX_H

#include <vector>
#include <iostream>
#include <stack>
#include <math.h>
#include "flags.h"

using std::vector;
using std::cout;
using std::endl;
using std::stack;


template <class T>

class matrix {
private:
    unsigned rows = 0, columns = 0;
    T* m;

    struct i_row{
        int i;
        int row;
    };

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

    void rowScalar(int row_i, T lambda){
        for (int j=0; j<columns; ++j){
            T a = m[index(row_i,j)];
            m[index(row_i, j)]*= lambda;
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

    void completeReduction(stack<i_row> &pivots){
        T lambda;
        while(!pivots.empty()){
            i_row p = pivots.top();
            pivots.pop();
            if (p.row == 0)
                break;
            for (int k=p.i-columns; k > 0; k-=columns){
                if (m[k] != 0){
                    lambda = - m[k]/m[p.i];
                    rowSum(p.row,k/columns, lambda);
#ifdef SHOW_CANCELLATION
                    print();
#endif
                }
            }
        }
    };

public:

    /**
    * @creates uninitialized matrix. The user is supposed to call init(T value) right after
    */
    matrix(unsigned int rows, unsigned int columns) : rows(rows), columns(columns){
        m = new T[rows * columns];
    }

    matrix(unsigned int rows, unsigned int columns, T* m) : rows(rows), columns(columns), m(m){}

    ~matrix(){
        delete [] m;
    }

    void init(T value) {
        for (int i=0; i<rows; ++i)
            for (int j=0; j<columns; ++j)
                m[i+j] = value;
    }
    inline unsigned int getRows() const { return this->rows; }
    inline unsigned int getCols() const { return this->columns; }
    inline T get(const int i, const int j){ return m[index(i,j)]; }
    inline void set(const int i, const int j, T value){ m[index(i,j)] = value; }

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
        stack<i_row> pivots;
        i_row pivot;
        while(col < columns && row < rows && (i=findPivot(row, col)) != -1){
            pivot.row = row;
            pivot.i = i;
            if (i != (rows * columns)-1){
                pivots.push(pivot);
                if (m[i]!=1){
                    rowScalar(i/columns, 1/m[i]);
#ifdef SHOW_CANCELLATION
                    print();
#endif
                }
                applyE(i);
            }
            col++;row++;
        };
        completeReduction(pivots);
    }

    void addSolutions(T* s){
        T* new_m = new T [rows * columns + rows];
        int i,j;
        for(i=0; i<rows; ++i){
            int off = (1+columns) * i;
            for (j=0; j<columns; ++j) {
                new_m[j+off] = m[index(i,j)];
            }
            new_m[j+off] = s[i];
        }
        delete [] m;
        m = new_m;
        columns++;
#ifdef SHOW_CANCELLATION
        print();
#endif
    }

    matrix operator*(matrix &b) {
        if (columns != b.getCols())
            throw std::invalid_argument("a matrix columns have to be the same as b's");
        matrix res(rows, b.getCols());
        T tmp = 0 ;
        for (int i=0; i<rows; ++i)
            for (int j=0; j<b.getCols(); ++j)
            {
                tmp = 0;
                for (int k=0; k<columns; ++k)
                    tmp +=  m[index(i,k)] * b.get(k,j);
                res.set(i, j, tmp);
            }
        return res;
    }

    T infinityNorm() {
        T sum, norm = 0;
        for (int i=0; i<rows; ++i) {
            sum=0;
            for (int j=0; j<columns; ++j)
                sum += fabs(m[index(i,j)]);
            if (sum>norm)
                norm = sum ;
        }
        return norm;
    }
};


#endif