#ifndef _SIMPLEX_H_
#define _SIMPLEX_H_

#include <iostream>
#include <vector>
#include <map>

class Simplex
{
private:
	int rows, cols;
	//stores coefficients of all the variables
	std::vector <std::vector<double>> A;
	//stores constants of constraints
	std::vector<double> B;
	//stores the coefficients of the objective function
	std::vector<double> C;

	double maximum;
	bool isUnbounded;

public:
	Simplex(
		std::vector <std::vector<double> > matrix,
		std::vector<double> b, std::vector<double> c);
	bool simplexAlgorithmCalculataion();
	bool checkOptimality();
	void doPivotting(int pivotRow, int pivotColumn);
	int findPivotColumn();
	int findPivotRow(int pivotColumn);
	void print();
	void CalculateSimplex();
};

#endif