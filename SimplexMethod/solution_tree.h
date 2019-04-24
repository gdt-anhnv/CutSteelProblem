#ifndef _SOLUTION_TREE_H_
#define _SOLUTION_TREE_H_

#include <iostream>
#include <list>
#include <vector>

class SolutionNode;

#define Solutions			std::vector<std::vector<int>>
#define SolutionNodes		std::list<SolutionNode*>

class SolutionTree
{
private:
	SolutionNode* root;
	std::list<int> length_values;
	int root_value;
public:
	SolutionTree(const std::list<int>& lvs, int rv);
	~SolutionTree();

	void BuildSolution();
	Solutions GetAllSolution() const;
};

class SolutionNode
{
private:
	int origin_value;
	int subtract_value;

	SolutionNodes children;
	friend Solutions SolutionTree::GetAllSolution() const;
public:
	SolutionNode(int ori_val, int sub_val);
	~SolutionNode();

	SolutionNodes AddChildren(const std::list<int>& len_vals);
};

#endif
