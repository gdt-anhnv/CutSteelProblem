#ifndef _BIG_M_SOLUTION_H_
#define _BIG_M_SOLUTION_H_

#include <iostream>
#include <vector>

#define VECTOR				std::vector<double>
class BigMSolution
{
public:
	const static double BIG_M;
private:
	VECTOR c;
	std::vector<VECTOR> d;
	VECTOR b;
	VECTOR b_m;

public:
	BigMSolution(const VECTOR& _c, const std::vector<VECTOR>& _d, const VECTOR& _b);
	~BigMSolution();

	void DoSimplex();

private:
	void FindPivot(int& col, int& row);
	void DoPivot(int col, int row);
	bool IsTerminal() const;
};

#endif