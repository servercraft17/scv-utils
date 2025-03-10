#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include "stdlib.h"
#include "string.h"
#include "vector.hpp"

class SS_Matrix {
    int rows, cols;
    float** matrix;
    void* GPUMatrixData;

public:
    SS_Matrix();
    SS_Matrix(const SS_Matrix& o);
    SS_Matrix(int rows, int cols);
    SS_Matrix(std::vector<std::vector<float>> mat);
    ~SS_Matrix();

    static SS_Matrix Identity(int size);

    int GetRows() const;
    int GetCols() const;

    float& operator()(int row, int col);
    
    bool operator==(SS_Matrix& o);
    //void operator=(SS_Matrix& o);
    void operator=(SS_Matrix o);

    SS_Matrix operator+(SS_Matrix& o);
    void operator+=(SS_Matrix& o);
    SS_Matrix operator-(SS_Matrix& o);
    void operator-=(SS_Matrix& o);
    SS_Matrix operator*(SS_Matrix& o);
    void operator*=(SS_Matrix& o);
    
    // returns a version rotated version of the matrix.
    SS_Matrix transposed();
    // rotates the matrix.
    void transpose();    

    // Creates a perspective

    static SS_Matrix CreateTranslationMatrix(SS_Vector3<float> translation);
    static SS_Matrix translate(SS_Vector3<float> translation);
    static SS_Matrix translate(SS_Matrix mat, SS_Vector3<float> t);


//10/19/24: Maybe someday I'll figure out how to get it so I don't have to include vector.hpp in here, but today is not the day.
    #ifdef VECTOR_HPP
        SS_Matrix(SS_Vector<float> v);
        SS_Matrix(SS_Vector3<float> v);
        SS_Matrix(SS_Vector4<float> v);

        SS_Matrix operator+(SS_Vector<float> v);
        void operator+=(SS_Vector<float> v);
        SS_Matrix operator-(SS_Vector<float> v);
        void operator-=(SS_Vector<float> v);
        SS_Matrix operator*(SS_Vector<float> v);
        void operator*=(SS_Vector<float> v);

        SS_Matrix operator+(SS_Vector3<float> v);
        void operator+=(SS_Vector3<float> v);
        SS_Matrix operator-(SS_Vector3<float> v);
        void operator-=(SS_Vector3<float> v);
        SS_Matrix operator*(SS_Vector3<float> v);
        void operator*=(SS_Vector3<float> v);

        SS_Matrix operator+(SS_Vector4<float> v);
        void operator+=(SS_Vector4<float> v);
        SS_Matrix operator-(SS_Vector4<float> v);
        void operator-=(SS_Vector4<float> v);
        SS_Matrix operator*(SS_Vector4<float> v);
        void operator*=(SS_Vector4<float> v);
    #endif

    struct Matrix4x4Conv {
        float m11, m12, m13, m14;
        float m21, m22, m23, m24;
        float m31, m32, m33, m34;
        float m41, m42, m43, m44;
    };
    struct Matrix3x3Conv {
        float m11, m12, m13;
        float m21, m22, m23;
        float m31, m32, m33;
    };
    struct Matrix2x2Conv {
        float m11, m12;
        float m21, m22;
    };
    Matrix4x4Conv* GPUMatrix4x4();
    Matrix3x3Conv* GPUMatrix3x3();
    Matrix2x2Conv* GPUMatrix2x2();
};
#endif /* MATRIX_HPP */