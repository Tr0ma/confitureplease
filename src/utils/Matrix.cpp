#include "Matrix.h"

void Matrix::Identity()
{
	m_A = 1;
	m_B = 0;
	m_C = 0;
	m_D = 1;
	m_Tx = 0;
	m_Ty = 0;
}

void Matrix::SetTo(float a, float b, float c, float d, float tx, float ty)
{
	m_A = a;
	m_B = b;
	m_C = c;
	m_D = d;
	m_Tx = tx;
	m_Ty = ty;
}

void Matrix::CopyFrom(Matrix& matrix)
{
	m_A = matrix.m_A;
	m_B = matrix.m_B;
	m_C = matrix.m_C;
	m_D = matrix.m_D;
	m_Tx = matrix.m_Tx;
	m_Ty = matrix.m_Ty;
}