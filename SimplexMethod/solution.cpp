#include "solution.h"
#include "solution_tree.h"

#include <queue>
#include <string>

Solution::Solution(int len) :
	length_values(std::list<int>()),
	max_length(len)
{
}

Solution::~Solution()
{
}

void Solution::AddLength(int len)
{
	length_values.push_back(len);
}

static Solutions RemoveDuplication(Solutions& solutions)
{
	Solutions ident_sol = Solutions();
	std::list<std::wstring> ident_comp = std::list<std::wstring>();
	for (Solutions::iterator iter = solutions.begin();
		iter != solutions.end(); iter++)
	{
		std::sort(iter->begin(), iter->end());

		std::wstring ident = std::wstring();
		for (std::vector<int>::const_iterator sub_iter = iter->begin();
			sub_iter != iter->end(); sub_iter++)
		{
			ident.append(std::to_wstring(*sub_iter));
		}

		bool is_duplicated = false;
		for (std::list<std::wstring>::iterator ident_iter = ident_comp.begin();
			ident_iter != ident_comp.end(); ident_iter++)
		{
			if (0 == ident.compare(*ident_iter))
			{
				is_duplicated = true;
			}
		}

		if (!is_duplicated)
		{
			ident_comp.push_back(ident);
			ident_sol.push_back(*iter);
		}
	}

	return ident_sol;
}

Solutions Solution::GetAllSolution() const
{
	SolutionTree* tree = new SolutionTree(length_values, max_length);
	tree->BuildSolution();
	Solutions solutions = tree->GetAllSolution();

	delete tree;

	for (std::list<int>::const_iterator iter = length_values.begin();
		iter != length_values.end(); iter++)
	{
		if (*iter > max_length / 2)
		{
			std::vector<int> sol = std::vector<int>();
			sol.push_back(*iter);
			solutions.push_back(sol);
		}
	}

	return RemoveDuplication(solutions);
}

