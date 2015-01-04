#include "MatrixUtil.h"

void MatrixUtil::PrependMatrix(Matrix& base, Matrix& prep)
{
	base.SetTo(
		base.m_A * prep.m_A + base.m_C * prep.m_B,
		base.m_B * prep.m_A + base.m_D * prep.m_B,
		base.m_A * prep.m_C + base.m_C * prep.m_D,
		base.m_B * prep.m_C + base.m_D * prep.m_D,
		base.m_Tx + base.m_A * prep.m_Tx + base.m_C * prep.m_Ty,
		base.m_Ty + base.m_B * prep.m_Tx + base.m_D * prep.m_Ty
		);
}