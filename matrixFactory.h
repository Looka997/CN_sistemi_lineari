#ifndef LAB_SISTEMI_MATRIXFACTORY_H
#define LAB_SISTEMI_MATRIXFACTORY_H

#include <matrix.h>

typedef float number;
class matrixFactory {
private:
    static number fact(number n){
        if (n<=1)
            return 1;
        return n * fact(n-1);
    }

    static number compute_pascal(int i, int j){
        return fact(i+j-2) / (fact(i-1) * fact(j-1));
    }

    static number compute_triangular(int i, int j){
        if (i == j)
            return 2;
        if (abs(i-j) == 1)
            return -1;
        return 0;
    }

    template<typename Function>
    matrix<number> populate(unsigned int n, Function f){
        number* mat = new number [n * n];
        for (int i=0, k=0; k<n*n; ++i)
            for (int j=0; j<n; ++j, ++k)
                mat[k] = f(i+1,j+1);
        return matrix<number>(n, n,mat);
    }
public:
    matrix<number> Pascal(unsigned int n){
        return populate(n, compute_pascal);
    }
    matrix<number> Triangular(unsigned int n){
        return populate(n, compute_triangular);
    }
    matrix<number> SpecificA(){
        number* mat = new number[16]{3, 1, -1, 0, 0, 7, -3, 0, 0, -3, 9, -2, 0, 0, 4, -10};
        return matrix<number>(4,4, mat);
    }
    matrix<number> SpecificB(){
        number* mat = new number[16]{2, 4, -2, 0, 1, 3, 0, 1, 3, -1, 1, 2, 0, -1, 2, 1};
        return matrix<number>(4,4, mat);
    }
};


#endif //LAB_SISTEMI_MATRIXFACTORY_H
