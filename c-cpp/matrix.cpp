#include "matrix.hpp"
#include <stdlib.h>
#include "common.hpp"

float reserved =0;


SS_Matrix::SS_Matrix() {
    this->GPUMatrixData=NULL;
    this->rows=0;
    this->cols=0;

    matrix = (float**)malloc(sizeof(void*)*rows);
    for (int i=0; i<rows; i++) {
        matrix[i] = (float*)malloc(sizeof(float)*cols);
        for (int j=0; j<cols; j++) matrix[i][j] = 0;
    }
}

SS_Matrix::SS_Matrix(const SS_Matrix& o) {
    this->GPUMatrixData=NULL;
    rows=o.rows;
    cols=o.cols;
    matrix = (float**)malloc(sizeof(void*)*rows);
    for (int i=0; i<rows; i++) {
        matrix[i] = (float*)malloc(sizeof(float)*cols);
        for (int j=0; j<cols; j++) matrix[i][j] = o.matrix[i][j];
    }
}

SS_Matrix::SS_Matrix(int rows, int cols) {
    this->GPUMatrixData=NULL;
    this->rows=rows;
    this->cols=cols;

    matrix = (float**)malloc(sizeof(void*)*rows);
    for (int i=0; i<rows; i++) {
        matrix[i] = (float*)malloc(sizeof(float)*cols);
        for (int j=0; j<cols; j++) matrix[i][j] = 0;
    }
}

SS_Matrix::SS_Matrix(std::vector<std::vector<float>> mat) {
    this->GPUMatrixData=NULL;
    this->rows=mat.size();
    this->cols=mat[0].size();

    matrix = (float**)malloc(sizeof(void*)*rows);
    for (int i=0; i<rows; i++) {
        matrix[i] = (float*)malloc(sizeof(float)*cols);
        memcpy(matrix[i], mat[i].data(), sizeof(float)*cols);
    }
}

SS_Matrix::~SS_Matrix() {
    if (matrix != NULL) {
        for (int i=0; i<rows; i++) free(matrix[i]);
        free(matrix);
        matrix=NULL;
    }

    if (GPUMatrixData != NULL) free(GPUMatrixData);
    GPUMatrixData = NULL;
}

SS_Matrix SS_Matrix::Identity(int size) {
    SS_Matrix res(size, size);
    for (int i=0; i<size;i++) res(i,i) = 1;
    return res;
}

int SS_Matrix::GetRows() const {
    return rows;
}

int SS_Matrix::GetCols() const {
    return cols;
}

float& SS_Matrix::operator()(int row, int col) {
    return row < rows && row >= 0 && col < cols && col >= 0? matrix[row][col] : reserved;
}

bool SS_Matrix::operator==(SS_Matrix& o) {
    return (rows == o.rows && cols == o.cols)? memcmp(matrix, o.matrix, sizeof(float)*rows*cols) == 0 : false;
}


void SS_Matrix::operator=(SS_Matrix o) {
    if (rows != o.rows || cols != o.cols) {
        for (int i=0; i<rows; i++) free(matrix[i]);
        free(matrix);
        this->rows=o.rows;
        this->cols=o.cols;

        matrix = (float**)malloc(sizeof(void*)*rows);
        for (int i=0; i<rows; i++) {
            matrix[i] = (float*)malloc(sizeof(float)*cols);
            for (int j=0; j<cols; j++) matrix[i][j] = o.matrix[i][j];
        }
    } else for (int i=0; i<rows; i++) for (int j=0; j<cols; j++) matrix[i][j] = o.matrix[i][j];
}

SS_Matrix SS_Matrix::operator+(SS_Matrix& o) {
    if (rows!=o.rows||cols!=o.cols) return SS_Matrix();
    SS_Matrix res(rows, cols);
    for (int i=0; i<rows;i++) for (int j=0; j<cols; j++)
        res(i, j) = this->operator()(i, j)+o(i, j);
    return res;
}

void SS_Matrix::operator+=(SS_Matrix& o) {
    if (rows!=o.rows||cols!=o.cols) return;
    for (int i=0; i<rows;i++) for (int j=0; j<cols; j++)
        this->operator()(i, j)+=o(i, j);
}

SS_Matrix SS_Matrix::operator-(SS_Matrix& o) {
    if (rows!=o.rows||cols!=o.cols) return SS_Matrix();
    SS_Matrix res(rows, cols);
    for (int i=0; i<rows;i++) for (int j=0; j<cols; j++)
        res(i, j) = this->operator()(i, j)-o(i, j);
    return res;
}

void SS_Matrix::operator-=(SS_Matrix& o) {
    if (rows!=o.rows||cols!=o.cols) return;
    for (int i=0; i<rows;i++) for (int j=0; j<cols; j++)
        this->operator()(i, j)-=o(i, j);
}

SS_Matrix SS_Matrix::operator*(SS_Matrix& o) {
    if (cols != o.rows) return SS_Matrix();
    SS_Matrix res(rows, o.cols);
    for (int i=0; i<rows;i++) for (int j=0; j<o.cols;j++) for (int k=0; k<o.rows;k++) 
        res(i, j) += this->operator()(i, k) * o(k, j);
    return res;
}

void SS_Matrix::operator*=(SS_Matrix& o) {
    if (cols != o.rows) return;
    SS_Matrix res(rows, o.cols);
    for (int i=0; i<rows;i++) for (int j=0; j<o.cols;j++) for (int k=0; k<o.rows;k++) 
        res(i, j) += this->operator()(i, k) * o(k, j);
    *this = res;
}

SS_Matrix SS_Matrix::transposed() {
    SS_Matrix retv(cols, rows);
    for (int i=0; i<rows;i++) for (int j=0; j<cols;j++)
        retv(j, i) = this->operator()(i,j);
    return retv;
}

void SS_Matrix::transpose() {
    SS_Matrix retv(cols, rows);
    for (int i=0; i<rows;i++) for (int j=0; j<cols;j++)
        retv(j, i) = this->operator()(i,j);
    *this = retv;
}

SS_Matrix SS_Matrix::CreateTranslationMatrix(SS_Vector3<float> translation) {
    return SS_Matrix({
        {1, 0, 0, translation.x},
        {0, 1, 0, translation.y},
        {0, 0, 1, translation.z},
        {0, 0, 0, 1}
    });}

SS_Matrix SS_Matrix::translate(SS_Vector3<float> translation) {
    return SS_Matrix({
        {1, 0, 0, translation.x},
        {0, 1, 0, translation.y},
        {0, 0, 1, translation.z},
        {0, 0, 0, 1}
    });
}

SS_Matrix SS_Matrix::translate(SS_Matrix mat, SS_Vector3<float> t) {
    return SS_Matrix({{1, 0, 0, t.x}, {0, 1, 0, t.y}, {0, 0, 1, t.z}, {0, 0, 0, 1}})
        * mat;
}

SS_Matrix::Matrix4x4Conv* SS_Matrix::GPUMatrix4x4() {
    if (rows<4 || cols<4) return NULL;
    if (GPUMatrixData != NULL) {
        free(GPUMatrixData);
        GPUMatrixData = NULL;
    }
    GPUMatrixData = malloc(sizeof(Matrix4x4Conv));
    Matrix4x4Conv* md = (Matrix4x4Conv*)GPUMatrixData;
    md->m11 = (*this)(00,0);
    md->m12 = (*this)(00,1);
    md->m13 = (*this)(00,2);
    md->m14 = (*this)(00,3);
    md->m21 = (*this)(01,0);
    md->m22 = (*this)(01,1);
    md->m23 = (*this)(01,2);
    md->m24 = (*this)(01,3);
    md->m31 = (*this)(02,0);
    md->m32 = (*this)(02,1);
    md->m33 = (*this)(02,2);
    md->m34 = (*this)(02,3);
    md->m41 = (*this)(03,0);
    md->m42 = (*this)(03,1);
    md->m43 = (*this)(03,2);
    md->m44 = (*this)(03,3);
    return md;
}
SS_Matrix::Matrix3x3Conv* SS_Matrix::GPUMatrix3x3() {
    if (rows<3 || cols<3) return NULL;
    if (GPUMatrixData != NULL) {
        free(GPUMatrixData);
        GPUMatrixData = NULL;
    }
    GPUMatrixData = malloc(sizeof(Matrix3x3Conv));
    Matrix3x3Conv* md = (Matrix3x3Conv*)GPUMatrixData;
    md->m11 = (*this)(00,0);
    md->m12 = (*this)(00,1);
    md->m13 = (*this)(00,2);
    md->m21 = (*this)(01,0);
    md->m22 = (*this)(01,1);
    md->m23 = (*this)(01,2);
    md->m31 = (*this)(02,0);
    md->m32 = (*this)(02,1);
    md->m33 = (*this)(02,2);
    return md;
}
SS_Matrix::Matrix2x2Conv* SS_Matrix::GPUMatrix2x2() {
    if (rows<2 || cols<2) return NULL;
    if (GPUMatrixData != NULL) {
        free(GPUMatrixData);
        GPUMatrixData = NULL;
    }
    GPUMatrixData = malloc(sizeof(Matrix2x2Conv));
    Matrix2x2Conv* md = (Matrix2x2Conv*)GPUMatrixData;
    md->m11 = (*this)(00,0);
    md->m12 = (*this)(00,1);
    md->m21 = (*this)(01,0);
    md->m22 = (*this)(01,1);
    return md;
}

#ifdef VECTOR_HPP

SS_Matrix::SS_Matrix(SS_Vector<float> v) {
    rows=2; cols=1;
    matrix = (float**)malloc(sizeof(void*)*rows);
    for (int i=0; i<rows; i++) {
        matrix[i] = (float*)malloc(sizeof(float)*cols);
    }
    matrix[0][0]=v.x;
    matrix[1][0]=v.y;
}

SS_Matrix::SS_Matrix(SS_Vector3<float> v) {
    rows=3; cols=1;
    matrix = (float**)malloc(sizeof(void*)*rows);
    for (int i=0; i<rows; i++) {
        matrix[i] = (float*)malloc(sizeof(float)*cols);
    }
    matrix[0][0]=v.x;
    matrix[1][0]=v.y;
    matrix[2][0]=v.z;
}

SS_Matrix::SS_Matrix(SS_Vector4<float> v) {
    rows=4; cols=1;
    matrix = (float**)malloc(sizeof(void*)*rows);
    for (int i=0; i<rows; i++) {
        matrix[i] = (float*)malloc(sizeof(float)*cols);
    }
    matrix[0][0]=v.x;
    matrix[1][0]=v.y;
    matrix[2][0]=v.z;
    matrix[3][0]=v.w;
}

SS_Matrix SS_Matrix::operator+(SS_Vector<float> v) {
    if (rows != 2 || cols != 1) return SS_Matrix();
    SS_Matrix res(2, 1);
    res(0,0) = this->operator()(0,0)+v.x;
    res(1,0) = this->operator()(1,0)+v.y;
    return res;
}

void SS_Matrix::operator+=(SS_Vector<float> v) {
    if (rows != 2 || cols != 1) return;
    this->operator()(0,0)+=v.x;
    this->operator()(1,0)+=v.y;
}

SS_Matrix SS_Matrix::operator-(SS_Vector<float> v) {
    if (rows != 2 || cols != 1) return SS_Matrix();
    SS_Matrix res(2, 1);
    res(0,0) = this->operator()(0,0)-v.x;
    res(1,0) = this->operator()(1,0)-v.y;
    return res;
}

void SS_Matrix::operator-=(SS_Vector<float> v) {
    if (rows != 2 || cols != 1) return;
    this->operator()(0,0)-=v.x;
    this->operator()(1,0)-=v.y;
}

SS_Matrix SS_Matrix::operator*(SS_Vector<float> v) {
    if (cols != 2) return SS_Matrix();
    SS_Matrix res(rows, 1);
    float vm[2] = {v.x, v.y};
    for (int i=0; i<rows;i++) for (int k=0; k<2;k++) 
        res(i, 0) += this->operator()(i, k) * vm[k];
    return res;
}

void SS_Matrix::operator*=(SS_Vector<float> v) {
    if (cols != 2) return;
    SS_Matrix res(rows, 1);
    float vm[2] = {v.x, v.y};
    for (int i=0; i<rows;i++) for (int k=0; k<2;k++) 
        res(i, 0) += this->operator()(i, k) * vm[k];
    *this = res;
}


SS_Matrix SS_Matrix::operator+(SS_Vector3<float> v) {
    if (rows != 3 || cols != 1) return SS_Matrix();
    SS_Matrix res(3, 1);
    res(0,0) = this->operator()(0,0)+v.x;
    res(1,0) = this->operator()(1,0)+v.y;
    res(2,0) = this->operator()(1,0)+v.z;
    return res;
}

void SS_Matrix::operator+=(SS_Vector3<float> v) {
    if (rows != 3 || cols != 1) return;
    this->operator()(0,0)+=v.x;
    this->operator()(1,0)+=v.y;
    this->operator()(2,0)+=v.z;
}

SS_Matrix SS_Matrix::operator-(SS_Vector3<float> v) {
    if (rows != 3 || cols != 1) return SS_Matrix();
    SS_Matrix res(3, 1);
    res(0,0) = this->operator()(0,0)-v.x;
    res(1,0) = this->operator()(1,0)-v.y;
    res(3,0) = this->operator()(1,0)-v.z;
    return res;
}

void SS_Matrix::operator-=(SS_Vector3<float> v) {
    if (rows != 3 || cols != 1) return;
    this->operator()(0,0)-=v.x;
    this->operator()(1,0)-=v.y;
    this->operator()(2,0)-=v.z;
}

SS_Matrix SS_Matrix::operator*(SS_Vector3<float> v) {
    if (cols != 3) return SS_Matrix();
    SS_Matrix res(rows, 1);
    float vm[3] = {v.x, v.y, v.z};
    for (int i=0; i<rows;i++) for (int k=0; k<3;k++) 
        res(i, 0) += this->operator()(i, k) * vm[k];
    return res;
}

void SS_Matrix::operator*=(SS_Vector3<float> v) {
    if (cols != 3) return;
    SS_Matrix res(rows, 1);
    float vm[3] = {v.x, v.y, v.z};
    for (int i=0; i<rows;i++) for (int k=0; k<3;k++) 
        res(i, 0) += this->operator()(i, k) * vm[k];
    *this = res;
}


SS_Matrix SS_Matrix::operator+(SS_Vector4<float> v) {
    if (rows != 4 || cols != 1) return SS_Matrix();
    SS_Matrix res(4, 1);
    res(0,0) = this->operator()(0,0)+v.x;
    res(1,0) = this->operator()(1,0)+v.y;
    res(2,0) = this->operator()(2,0)+v.z;
    res(3,0) = this->operator()(3,0)+v.w;
    return res;
}

void SS_Matrix::operator+=(SS_Vector4<float> v) {
    if (rows != 4 || cols != 1) return;
    this->operator()(0,0)+=v.x;
    this->operator()(1,0)+=v.y;
    this->operator()(2,0)+=v.z;
    this->operator()(3,0)+=v.w;
}

SS_Matrix SS_Matrix::operator-(SS_Vector4<float> v) {
    if (rows != 4 || cols != 1) return SS_Matrix();
    SS_Matrix res(4, 1);
    res(0,0) = this->operator()(0,0)-v.x;
    res(1,0) = this->operator()(1,0)-v.y;
    res(3,0) = this->operator()(2,0)-v.z;
    res(4,0) = this->operator()(3,0)-v.w;
    return res;
}

void SS_Matrix::operator-=(SS_Vector4<float> v) {
    if (rows != 4 || cols != 1) return;
    this->operator()(0,0)-=v.x;
    this->operator()(1,0)-=v.y;
    this->operator()(2,0)-=v.z;
    this->operator()(3,0)-=v.w;
}

SS_Matrix SS_Matrix::operator*(SS_Vector4<float> v) {
    if (cols != 4) return SS_Matrix();
    SS_Matrix res(rows, 1);
    float vm[4] = {v.x, v.y, v.z, v.w};
    for (int i=0; i<rows;i++) for (int k=0; k<4;k++) 
        res(i, 0) += this->operator()(i, k) * vm[k];
    return res;
}

void SS_Matrix::operator*=(SS_Vector4<float> v) {
    if (cols != 4) return;
    SS_Matrix res(rows, 1);
    float vm[4] = {v.x, v.y, v.z, v.w};
    for (int i=0; i<rows;i++) for (int k=0; k<4;k++) 
        res(i, 0) += this->operator()(i, k) * vm[k];
    *this = res;
}
#endif /* VECTOR_HPP */