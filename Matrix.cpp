#include "Structures.h"
#include <assert.h>
#include "Rectangle.h"

// 3x3行列と3x3行列の積
void Multiply(const Matrix3x3* matrix1, const Matrix3x3* matrix2, Matrix3x3* result)
 {
	if (matrix1 && matrix2 && result) // ポインタが有効であることを確認
	{ 
		result->m[0][0] = matrix1->m[0][0] * matrix2->m[0][0] + matrix1->m[0][1] * matrix2->m[1][0] + matrix1->m[0][2] * matrix2->m[2][0];
		result->m[0][1] = matrix1->m[0][0] * matrix2->m[0][1] + matrix1->m[0][1] * matrix2->m[1][1] + matrix1->m[0][2] * matrix2->m[2][1];
		result->m[0][2] = matrix1->m[0][0] * matrix2->m[0][2] + matrix1->m[0][1] * matrix2->m[1][2] + matrix1->m[0][2] * matrix2->m[2][2];

		result->m[1][0] = matrix1->m[1][0] * matrix2->m[0][0] + matrix1->m[1][1] * matrix2->m[1][0] + matrix1->m[1][2] * matrix2->m[2][0];
		result->m[1][1] = matrix1->m[1][0] * matrix2->m[0][1] + matrix1->m[1][1] * matrix2->m[1][1] + matrix1->m[1][2] * matrix2->m[2][1];
		result->m[1][2] = matrix1->m[1][0] * matrix2->m[0][2] + matrix1->m[1][1] * matrix2->m[1][2] + matrix1->m[1][2] * matrix2->m[2][2];

		result->m[2][0] = matrix1->m[2][0] * matrix2->m[0][0] + matrix1->m[2][1] * matrix2->m[1][0] + matrix1->m[2][2] * matrix2->m[2][0];
		result->m[2][1] = matrix1->m[2][0] * matrix2->m[0][1] + matrix1->m[2][1] * matrix2->m[1][1] + matrix1->m[2][2] * matrix2->m[2][1];
		result->m[2][2] = matrix1->m[2][0] * matrix2->m[0][2] + matrix1->m[2][1] * matrix2->m[1][2] + matrix1->m[2][2] * matrix2->m[2][2];
	}
}

// 3x3行列と3次元ベクトルの積
Vector3 Multiply(const Matrix3x3& matrix, const Vector3& vec)
{
	Vector3 result;

	result.x = matrix.m[0][0] * vec.x + matrix.m[0][1] * vec.y + matrix.m[0][2] * vec.z;
	result.y = matrix.m[1][0] * vec.x + matrix.m[1][1] * vec.y + matrix.m[1][2] * vec.z;
	result.z = matrix.m[2][0] * vec.x + matrix.m[2][1] * vec.y + matrix.m[2][2] * vec.z;

	return result;
}

//スケーリング行列の関数
void MakeScaleMatrix(Matrix3x3* scaleMatrix, const Vector2* scale)
{
	if (scaleMatrix && scale) // ポインタが有効であることを確認
	{
		scaleMatrix->m[0][0] = scale->x;
		scaleMatrix->m[0][1] = 0;
		scaleMatrix->m[0][2] = 0;
		scaleMatrix->m[1][0] = 0;
		scaleMatrix->m[1][1] = scale->y;
		scaleMatrix->m[1][2] = 0;
		scaleMatrix->m[2][0] = 0;
		scaleMatrix->m[2][1] = 0;
		scaleMatrix->m[2][2] = 1;
	}
}

//回転行列の関数
void MakeRotateMatrix(Matrix3x3* rotateMatrix, float theta)
{
	if (rotateMatrix) // ポインタが有効であることを確認
	{
		rotateMatrix->m[0][0] = cosf(theta);
		rotateMatrix->m[0][1] = sinf(theta);
		rotateMatrix->m[0][2] = 0;
		rotateMatrix->m[1][0] = -sinf(theta);
		rotateMatrix->m[1][1] = cosf(theta);
		rotateMatrix->m[1][2] = 0;
		rotateMatrix->m[2][0] = 0;
		rotateMatrix->m[2][1] = 0;
		rotateMatrix->m[2][2] = 1;
	}
}

//平行移動行列の関数
void MakeTranslateMatrix(Matrix3x3* translateMatrix, const Vector2* translate)
{
	if (translateMatrix && translate) // ポインタが有効であることを確認
	{
		translateMatrix->m[0][0] = 1;
		translateMatrix->m[0][1] = 0;
		translateMatrix->m[0][2] = 0;
		translateMatrix->m[1][0] = 0;
		translateMatrix->m[1][1] = 1;
		translateMatrix->m[1][2] = 0;
		translateMatrix->m[2][0] = translate->x;
		translateMatrix->m[2][1] = translate->y;
		translateMatrix->m[2][2] = 1;
	}
}

void Transform(const Matrix3x3* matrix, const Vector2* vector, Vector2* result)
{
	if (matrix && vector && result) // ポインタが有効であることを確認
	{
		result->x = vector->x * matrix->m[0][0] + vector->y * matrix->m[1][0] + 1.0f * matrix->m[2][0];
		result->y = vector->x * matrix->m[0][1] + vector->y * matrix->m[1][1] + 1.0f * matrix->m[2][1];
		float w = vector->x * matrix->m[0][2] + vector->y * matrix->m[1][2] + 1.0f * matrix->m[2][2];

		assert(w != 0);
		result->x /= w;
		result->y /= w;
	}
	
}

//アフィン行列の関数
void MakeAffineMatrix(const Vector2* scale, float theta, const Vector2* translate, Matrix3x3* affineMatrix)
{
	if (scale && translate && affineMatrix) // ポインタが有効であることを確認
	{ 
		// 拡縮の行列
		Matrix3x3 scaleMatrix; 
		MakeScaleMatrix(&scaleMatrix, scale);

		// 回転の行列
		Matrix3x3 rotateMatrix;
		MakeRotateMatrix(&rotateMatrix, theta);

		// 平行移動の行列
		Matrix3x3 translateMatrix;
		MakeTranslateMatrix(&translateMatrix, translate);

		// 行列の掛け算
		Matrix3x3 scaleRotateMatrix;
		Multiply(&scaleMatrix, &rotateMatrix, &scaleRotateMatrix);
		Multiply(&scaleRotateMatrix, &translateMatrix, affineMatrix);
	}
}

void ApplyScalingToRectangle(RectangleObject* rectangle)
{
	if (rectangle == nullptr) return; // nullptr チェック

	// スケーリング行列を作成
	Matrix3x3 scaleMatrix;
	MakeScaleMatrix(&scaleMatrix, &rectangle->scale);

	// 左上
	Vector3 leftTop = { rectangle->vertex.leftTop.x, rectangle->vertex.leftTop.y, 1.0f };
	Vector3 scaledLeftTop = Multiply(scaleMatrix, leftTop);
	rectangle->vertex.leftTop.x = scaledLeftTop.x;
	rectangle->vertex.leftTop.y = scaledLeftTop.y;

	// 右上
	Vector3 rightTop = { rectangle->vertex.rightTop.x, rectangle->vertex.rightTop.y, 1.0f };
	Vector3 scaledRightTop = Multiply(scaleMatrix, rightTop);
	rectangle->vertex.rightTop.x = scaledRightTop.x;
	rectangle->vertex.rightTop.y = scaledRightTop.y;

	// 左下
	Vector3 leftBottom = { rectangle->vertex.leftBottom.x, rectangle->vertex.leftBottom.y, 1.0f };
	Vector3 scaledLeftBottom = Multiply(scaleMatrix, leftBottom);
	rectangle->vertex.leftBottom.x = scaledLeftBottom.x;
	rectangle->vertex.leftBottom.y = scaledLeftBottom.y;

	// 右下
	Vector3 rightBottom = { rectangle->vertex.rightBottom.x, rectangle->vertex.rightBottom.y, 1.0f };
	Vector3 scaledRightBottom = Multiply(scaleMatrix, rightBottom);
	rectangle->vertex.rightBottom.x = scaledRightBottom.x;
	rectangle->vertex.rightBottom.y = scaledRightBottom.y;
}