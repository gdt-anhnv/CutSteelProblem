#include "solution.h"
#include "simplex.h"
#include "big_m_solution.h"

/*sample:
require:
		5 steel 5000mm
		6 steel 4000mm
		9 steel 3000mm
		3 steel 1500mm

demand: minimum number of 6000mm steel*/

struct SteelData
{
	int length;
	int number;

	SteelData(int l, int n) :
		length(l),
		number(n)
	{}
};

int main()
{
	std::vector<SteelData> steel_data = std::vector<SteelData>();
	steel_data.push_back(SteelData(5000, 5));
	steel_data.push_back(SteelData(4000, 6));
	steel_data.push_back(SteelData(3000, 9));
	steel_data.push_back(SteelData(1500, 3));

	Solution* solution = new Solution(6000);
	for (std::vector<SteelData>::iterator iter = steel_data.begin();
		iter != steel_data.end(); iter++)
		solution->AddLength(iter->length);

	Solutions ret = solution->GetAllSolution();
	delete solution;

	int num_sol = ret.size();
	int num_art_var = steel_data.size();

	VECTOR c = VECTOR(num_sol + num_art_var, 0.0);
	for (int i = 0; i < num_sol; i++)
		c[i] = 1.0;
	for (int i = num_sol; i < num_sol + num_art_var; i++)
		c[i] = BigMSolution::BIG_M;

	std::vector<VECTOR> d = std::vector<VECTOR>(steel_data.size(), {});
	for (int i = 0; i < steel_data.size(); i++)
	{
		d[i] = VECTOR(num_sol + num_art_var, 0.0);
		for (int j = 0; j < num_sol; j++)
		{
			std::vector<int> sol = ret[j];
			for (int k = 0; k < sol.size(); k++)
			{
				if(steel_data[i].length == sol[k])
				d[i][j] += 1;
			}
		}

		d[i][i + num_sol] = 1.0;
	}

	VECTOR b = VECTOR(steel_data.size(), 0.0);
	for (int i = 0; i < steel_data.size(); i++)
		b[i] = steel_data[i].number;

	BigMSolution* big_m_solution = new BigMSolution(c, d, b);
	big_m_solution->DoSimplex();

	delete big_m_solution;

	return 0;
}