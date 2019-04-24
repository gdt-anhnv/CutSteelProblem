#include "solution_tree.h"
#include <queue>

SolutionNode::SolutionNode(int ori_val, int sub_val) :
	origin_value(ori_val),
	subtract_value(sub_val),
	children(SolutionNodes())
{
}

SolutionNode::~SolutionNode()
{
	for (SolutionNodes::iterator iter = children.begin();
		iter != children.end(); iter++)
		delete (*iter);

	children.clear();
}

SolutionNodes SolutionNode::AddChildren(const std::list<int>& len_vals)
{
	for (std::list<int>::const_iterator iter = len_vals.begin();
		iter != len_vals.end(); iter++)
	{
		if (*iter > subtract_value)
			continue;
		children.push_back(new SolutionNode(*iter, subtract_value - *iter));
	}

	return children;
}

SolutionTree::SolutionTree(const std::list<int>& lvs, int rv) :
	root(nullptr),
	length_values(lvs),
	root_value(rv)
{
}

SolutionTree::~SolutionTree()
{
	if (nullptr != root)
		delete root;
}

void SolutionTree::BuildSolution()
{
	if (nullptr != root)
		return;

	root = new SolutionNode(0, root_value);
	std::queue<SolutionNode*> queue_nodes = std::queue<SolutionNode*>();
	queue_nodes.push(root);

	while (!queue_nodes.empty())
	{
		SolutionNode* curr_node = queue_nodes.front();
		queue_nodes.pop();

		SolutionNodes children = curr_node->AddChildren(length_values);
		for (SolutionNodes::iterator iter = children.begin();
			iter != children.end(); iter++)
			queue_nodes.push(*iter);
	}
}

#define ListSolution		std::list<SolutionNodes>
Solutions SolutionTree::GetAllSolution() const
{
	ListSolution solutions = ListSolution();
	for (SolutionNodes::iterator iter = root->children.begin();
		iter != root->children.end(); iter++)
	{
		SolutionNodes sub_solution = SolutionNodes();
		sub_solution.push_back(*iter);
		solutions.push_back(sub_solution);
	}

	Solutions ret = Solutions();
	for (ListSolution::iterator iter = solutions.begin(); iter != solutions.end();)
	{
		if (iter->back()->children.empty())
		{
			std::vector<int> gen_sol = std::vector<int>();
			for (SolutionNodes::const_iterator sol_iter = iter->begin();
				sol_iter != iter->end(); sol_iter++)
				gen_sol.push_back((*sol_iter)->origin_value);
			ret.push_back(gen_sol);
		}
		else
		{
			for (SolutionNodes::const_iterator new_iter = iter->back()->children.begin();
				new_iter != iter->back()->children.end(); new_iter++)
			{
				SolutionNodes new_sol = *iter;
				new_sol.push_back(*new_iter);
				solutions.push_back(new_sol);
			}
		}
		solutions.erase(iter++);
	}

	return ret;
}
