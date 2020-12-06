
#include "Matrix.h"
Matrix Matrix::operator*( Matrix matrix2) const {
    float * an=new float [getRow() *matrix2.getColumn()];
    memset(an,0,sizeof(float)*getRow() *matrix2.getColumn());
    Matrix *ans=new Matrix(  matrix2.getColumn(),getRow(),an);
    matrixmatrix(this, matrix2, ans);

    return *ans;
}
Matrix Matrix::operator*(float temp) const {
    float * an=new float [getRow() *getColumn()];
    Matrix *ans=new Matrix(  getColumn(),getRow(),an);
    for(int i=0;i<getRow() *getColumn();i++){
        an[i]=temp*data[i];
    }
        return *ans;
}
Matrix operator*(float tempt,Matrix matrix){
    float * an=new float [matrix.getRow() *matrix.getColumn()];
    Matrix *ans=new Matrix(  matrix.getColumn(),matrix.getRow(),an);
    for(int i=0;i<matrix.getRow() *matrix.getColumn();i++){
        an[i]=tempt*matrix.data[i];
    }
    return *ans;
}

void Matrix::operator=(const Matrix &temp) {
    this->data=temp.data;
    column=temp.column;
    row=temp.row;
}
ostream & operator<<(ostream &out,  Matrix obj){

    for (int i = 0; i < obj.getRow(); i++) {
        for (int j = 0; j < obj.getColumn(); j++) {
            out << obj.getData()[j + i * obj.getColumn()] << " ";
        }
        out << endl;
    }return out;}
void matrixmatrix(const Matrix *matrix1, Matrix matrix2, Matrix* ans) {
#if defined(_ENABLE_NEON)
    for (int i = 0; i < matrix1->getRow(); i++) {
        for (int j = 0; j < matrix2.getColumn(); j++) {
            for (int k = 0; k < matrix1->getColumn(); k++) {

                ans->getData()[j + i * matrix2.getColumn()] +=
                        matrix1->getData()[k + i * matrix1->getColumn()] * matrix2.getData()[k + j * matrix1->getColumn()];

            }
        }
    }
#elif defined(_ENABLE_AVX2)
    int m, n, p, si, sj, sk;
#pragma omp parallel for schedule(dynamic)
    for (sj = 0; sj < matrix2.getColumn(); sj += BLOCKSIZE) {
        for (si = 0; si < matrix1->getRow(); si += BLOCKSIZE) {
            for (sk = 0; sk < matrix1->getColumn(); sk += BLOCKSIZE) {
                m = matrix1->getRow() < si + BLOCKSIZE ? matrix1->getRow() : si + BLOCKSIZE;
                n = matrix2.getColumn() < sj + BLOCKSIZE ? matrix2.getColumn() : sj + BLOCKSIZE;
                p = sk + BLOCKSIZE < matrix1->getColumn() ? sk + BLOCKSIZE : matrix1->getColumn();
                doblock(matrix1,matrix2,si, sj, sk, m, n, p,*ans);

            }

        }

    }
#endif
}

void doblock(const Matrix * matrix1,Matrix matrix2,int si, int sj, int sk, int m, int n, int p,Matrix ans) {
#if defined(_ENABLE_AVX2)
    for (int i = si; i < m; i++) {
        for (int j = sj; j < n; j++) {
            __m256 acc = _mm256_setzero_ps();
            float temp[8];
            float inner_prod;
            int k;
            for (k = sk; k + 8 < p; k += 8) {

                acc = _mm256_add_ps(acc,
                                    _mm256_mul_ps(_mm256_loadu_ps(matrix1->getData() + k + i * matrix1->getColumn()),
                                                  _mm256_loadu_ps(matrix2.getData() + k + j * matrix1->getColumn())));
            }
            _mm256_storeu_ps(&temp[0], acc);
            inner_prod = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] +
                         temp[6] + temp[7] + temp[8];
            for (; k < p; k++) {
                inner_prod += matrix1->getData()[k + i * matrix1->getColumn()] * matrix2.getData()[k + j * matrix1->getColumn()];
            }
            ans.getData()[j + i * matrix2.getColumn()] += inner_prod;
        }

    }
#endif
}
Matrix::Matrix(const Matrix &matrix) {
    data=matrix.data;
    column=matrix.column;
    row=matrix.row;
    cnt++;
   
}


unsigned int Matrix::getColumn() const {
    return column;
}

unsigned int Matrix::getRow() const {
    return row;
}

float *Matrix::getData() const {
    return data;
}

void Matrix::setColumn(unsigned int column) {
    Matrix::column = column;
}

void Matrix::setRow(unsigned int row) {row = row;
}

void Matrix::setData(float *data) {
    Matrix::data = data;
}

Matrix::Matrix() {}


Matrix::Matrix(unsigned int column, unsigned int row) : column(column), row(row) {}

Matrix::Matrix(unsigned int column, unsigned int row, float *data) : column(column), row(row), data(data) {}

Matrix::~Matrix() {
    if(cnt==1){
  delete [] Matrix::data;}
}


