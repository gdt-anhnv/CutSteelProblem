#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <iostream>
#include <list>
#include <vector>

#define Solutions			std::vector<std::vector<int>>

class Solution
{
private:
	std::list<int> length_values;
	int max_length;
public:
	Solution(int len);
	~Solution();

	void AddLength(int len);
	Solutions GetAllSolution() const;
};

#endif