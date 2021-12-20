#include "matrix.h"
#include "matrixFactory.h"

using namespace std;
int main(){
    typedef float num;
    int const d0 = 6, d1=0;
    int n = 10 * (d1 + 1) + d0;

    matrixFactory mf = matrixFactory();
#ifdef TRIANG
    matrix<num> tri = mf.Triangular(n);
    tri.print();
#endif
#ifdef A
    matrix<num> a = mf.SpecificA();
    a.print();
#endif
#ifdef B
    matrix<num> b = mf.SpecificB();
    b.print();
#endif
#ifdef PASCAL
    matrix<num> pascal = mf.Pascal(10);
    pascal.print();
#endif
    number* mat = new number[20]{0, 0, 1, 0, 3, 1, 3, 2, 1, 0, 4, 1, 0, 0, 6, 2, 0, 5, 4, 9};
    matrix<num> ma (4,5, mat);
//    ma.print();
#ifdef GAUSS
//    ma.gauss();

#ifndef SHOW_CANCELLATION
//    ma.print();
#endif
#endif
//    number* s2 = new number[4]{1,1,1,1};
//    a.addSolutions(s2);
//    delete [] s2;
    cout << a.infinityNorm() << endl;
    cout << b.infinityNorm() << endl;
    matrix<num>prod = a * b;
    prod.print();
    cout << prod.infinityNorm() << endl;
    return 1;
}
