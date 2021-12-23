#include "matrix.h"
#include "matrixFactory.h"

using namespace std;
typedef float num;
void workMatrix(matrix<num>&);
int main(){

    int const d0 = 6, d1=0;
    int n = 10 * (d1 + 1) + d0;

    matrixFactory mf = matrixFactory();
#ifdef TRIANG
    matrix<num> tri = mf.Triangular(n);
    cout << "with matrix tri:" << endl;
    workMatrix(tri);
#endif
#ifdef A
    matrix<num> a = mf.SpecificA();
    cout << "with matrix A:" << endl;
    workMatrix(a);
#endif
#ifdef B
    matrix<num> b = mf.SpecificB();
    cout << "with matrix B:" << endl;
    workMatrix(b);
#endif
#ifdef PASCAL
    matrix<num> pascal = mf.Pascal(10);
    cout << "with matrix pascal:" << endl;
    workMatrix(pascal);
#endif

//    number* s2 = new number[4]{1,1,1,1};
//    a.addSolutions(s2);
//    delete [] s2;
    return 1;
}

void workMatrix(matrix<num> &a){
    a.print();

    /* Esercizio 1 */
    cout << "Norma infinito A: " << a.infinityNorm() << endl;

    /* Esercizio 2 */
    matrix<num> x(a.getRows(), 1);
    x.init(1);
    matrix<num> b = a * x;
    cout << "Vettore b generato:" << endl;
    b.print();
    a.addSolutions(b);
    a.print();
    a.gauss();
#ifndef SHOW_CANCELLATION
    a.print();
#endif


}
