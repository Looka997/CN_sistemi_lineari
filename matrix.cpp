#include "matrix.h"
#include "matrixFactory.h"
#define DEBUG

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


    return 1;
}
