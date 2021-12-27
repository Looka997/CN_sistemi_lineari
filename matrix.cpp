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
    matrix<num> a_copy(a);
    /* Esercizio 1 */
    cout << "Norma infinito A: " << a.infinityNorm() << endl;

    /* Esercizio 2 */
    matrix<num> x(a.getRows(), 1);
    x.init(1);
    matrix<num> b = a * x;
    cout << "Vettore b generato:" << endl;
    b.print();
    cout << "Matrice con soluzioni b:" << endl;
    a.addSolutions(b);
    a.print();
    cout << "Matrice ridotta:" << endl;
    a.gauss();
#ifndef SHOW_CANCELLATION
    a.print();
#endif
    num b_norm = b.infinityNorm();
    num *distortion = new num[b.getRows()]{1, 1, 1, 1};
    for(int i=0, e=1; i<b.getRows(); ++i, ++e)
        distortion[i] = pow(-1,e) * 0.01;
    matrix<num> d(b.getRows(), 1, distortion);
    matrix<num> delta_d = d.scalar(b_norm);
    matrix<num> new_solutions = b + delta_d;
    cout << "Soluzioni b+deltaB" << endl;
    new_solutions.print();
    cout << "Matrice con soluzioni b+deltaB:" << endl;
    a_copy.addSolutions(new_solutions);
    a_copy.print();
    cout << "Matrice ridotta:" << endl;
    a_copy.gauss();
#ifndef SHOW_CANCELLATION
    a_copy.print();
#endif


}
