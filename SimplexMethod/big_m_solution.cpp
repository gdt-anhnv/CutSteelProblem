#include "big_m_solution.h"

const double BigMSolution::BIG_M = 10000000.0f;

BigMSolution::BigMSolution(
	const VECTOR & _c,
	const std::vector<VECTOR>& _d,
	const VECTOR & _b) :
	c(_c),
	d(_d),
	b(_b),
	b_m(VECTOR(_d.size(), BIG_M))
{
}

BigMSolution::~BigMSolution()
{
}

void BigMSolution::DoSimplex()
{
	while (!IsTerminal())
	{
		int col = 0;
		int row = 0;
		FindPivot(col, row);
		DoPivot(col, row);
	}
}

static VECTOR GetCol(const std::vector<VECTOR>& mat, int index)
{
	VECTOR ret = VECTOR(mat.size(), 0.0f);
	for (int i = 0; i < ret.size(); i++)
	{
		ret[i] = mat[i][index];
	}

	return ret;
}

static double GetSumCol(
	const std::vector<VECTOR>& mat,
	const VECTOR& bm,
	int col)
{
	double sum = 0.00000f;
	VECTOR col_val = GetCol(mat, col);
	for (int i = 0; i < col_val.size(); i++)
	{
		double tmp1 = col_val[i];
		double tmp2 = bm[i];
		double mul = (tmp1 * tmp2);
		sum = sum + mul;
	}

	return sum;
}

static int MaxIndex(const VECTOR& v)
{
	int index = 0;
	double tmp = v[0];
	for (int i = 0; i < v.size(); i++)
	{
		if (tmp < v[i])
		{
			tmp = v[i];
			index = i;
		}
	}

	return index;
}

static int MinRadioIndex(const VECTOR& v1, const VECTOR& v2)
{
	int index = 0;
	double min_radio = BigMSolution::BIG_M;
	for (int i = 0; i < v2.size(); i++)
	{
		if (std::abs(v2[i]) < 0.001)
			continue;

		double tmp = v1[i] / v2[i];
		if (tmp < min_radio)
		{
			index = i;
			min_radio = tmp;
		}
	}

	return index;
}

void BigMSolution::FindPivot(int & col, int & row)
{
	VECTOR z_c = VECTOR(c.size(), 0.0f);
	for (int i = 0; i < d.front().size(); i++)
		z_c[i] = GetSumCol(d, b_m, i) - c[i];

	int max_index = MaxIndex(z_c);
	int min_radio_index = MinRadioIndex(b, GetCol(d, max_index));

	col = max_index;
	row = min_radio_index;
}

void BigMSolution::DoPivot(int col, int row)
{
	b_m[row] = c[row];
	double div = d[row][col];
	b[row] /= div;
	for (int i = 0; i < d.front().size(); i++)
	{
		d[row][i] /= div;
	}

	for (int i = 0; i < d.size(); i++)
	{
		if (i == row)
			continue;

		if (std::abs(d[i][col]) < 0.001)
			continue;

		b[i] -= b[row];

		for (int j = 0; j < d.front().size(); j++)
			d[i][j] -= d[row][j];
	}
}

bool BigMSolution::IsTerminal() const
{
	for (int i = 0; i < d.front().size(); i++)
	{
		double tmp = GetSumCol(d, b_m, i) - c[i];
		if (tmp > 0.0001)
			return false;
	}

	return true;
}
