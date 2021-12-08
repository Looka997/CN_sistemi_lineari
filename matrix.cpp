#include "matrix.h"
#include "matrixFactory.h"

using namespace std;
int main(){
    typedef float num;
    int const d0 = 6, d1=0;
    int n = 10 * (d1 + 1) + d0;

    matrixFactory mf = matrixFactory();
    matrix<num> pascal = mf.Pascal(10);
#ifdef DEBUG
    pascal.print();
#endif

    matrix<num> tri = mf.Triangular(n);
#ifdef DEBUG
    tri.print();
#endif

    matrix<num> A = mf.SpecificA();
#ifdef DEBUG
    A.print();
#endif

    matrix<num> B = mf.SpecificB();
#ifdef DEBUG
    B.print();
#endif
#ifdef GAUSS
    number* mat = new number[20]{0, 0, 1, 0, 3, 1, 3, 2, 1, 0, 4, 1, 0, 0, 6, 2, 0, 5, 4, 9};
    matrix<num> ma (4,5, mat);
    ma.print();
    ma.gauss();
#ifndef SHOW_CANCELLATION
    ma.print();
#endif
#endif


    return 1;
}
