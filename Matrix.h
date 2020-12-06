//
// Created by Stone on 2020/11/30.
//

#ifndef D_MATRIX_H
#define D_MATRIX_H

#define _ENABLE_AVX2 //Please enable it if X64 CPU
//#define _ENABLE_NEON //Please enable it if ARM CPU
#if  defined(_ENABLE_AVX2)
#include <immintrin.h>
#endif
#include <chrono>
#include "iostream"
#include <memory.h>

#define BLOCKSIZE 1024
using namespace std;
class Matrix {
private:
    unsigned int column, row,cnt=1;
    float *data;
public:
    unsigned int getColumn() const;

    unsigned int getRow() const;

    float *getData() const;

    void setColumn(unsigned int column);

    void setRow(unsigned int row);

    void setData(float *data);

    Matrix(unsigned int column, unsigned int row);

    Matrix(unsigned int column, unsigned int row, float *data);
Matrix(Matrix const &matrix);

    Matrix();
    void operator=(Matrix const & temp);
    Matrix operator*(Matrix temp) const;
    Matrix operator*(int temp) const;
    friend  Matrix operator*(int tempt,Matrix matrix);
    friend ostream & operator<<(ostream &out,  Matrix obj);

    ~Matrix();
};
void matrixmatrix(const Matrix *matrix1, Matrix matrix2, Matrix* ans);


void doblock(const Matrix *matrix1,Matrix matrix2,int si, int sj, int sk, int m, int n, int p,Matrix ans);

#endif //D_MATRIX_H
