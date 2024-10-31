#pragma once

#include "Structures.h"

// 3x3行列と3x3行列の積
void Multiply(const Matrix3x3* matrix1, const Matrix3x3* matrix2, Matrix3x3* result);

//スケーリング行列の関数
void MakeScaleMatrix(Matrix3x3* scaleMatrix, const Vector2* scale);

//回転行列の関数
void MakeRotateMatrix(Matrix3x3* rotateMatrix, float theta);

//平行移動行列の関数
void MakeTranslateMatrix(Matrix3x3* translateMatrix, const Vector2* translate);
void Transform(const Matrix3x3* matrix, const Vector2* vector, Vector2* result);

//アフィン行列の関数
void MakeAffineMatrix(const Vector2* scale, float theta, const Vector2* translate, Matrix3x3* affineMatrix);