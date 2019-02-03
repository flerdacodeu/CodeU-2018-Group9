#include <iostream>
#include <vector>
#include "binary_tree.hpp"


// just to check the tree (in general would have been moved to a binary tree class if was needed for anything)
template <class T>
void pre(Node<T> *node)
{
	if(node == nullptr)
		return;
	std::cout << node->data << std::endl;
	pre(node->get_left());
	pre(node->get_right());
}

int main()
{
	Btree<int> *btree = new Btree<int>();
	btree->insert(7);
	btree->insert(3);
	btree->insert(4);
	btree->insert(2);
	btree->insert(5);
	btree->insert(8);
	btree->insert(1);
	btree->insert(6);
	//  7
	// | |
	// 3 4 
	//  | 
	//  2 5
	//   | |
	//   8 1
	//    |
	//    6
	// ==> ancestors of 6 are 7->4->5->1 in any order (I`m doing in order of insertion)
	// question 1
	std::vector<int> res; // a vector to store the ancestors (not to print in the function) 
	btree->print_ancestors(res, 6);
	for ( size_t i = 0; i < res.size(); i++ )
		if ( i == res.size()-1 ) std::cout << res.at(i) << std::endl; 
		else std::cout << res.at(i) << "->";

	// question 2 
	Node<int> *lca = btree->least_common_ancestor(btree->get_root(), 2, 6);
	std::cout << lca->get_data();

	// clearing it out 
	delete btree;
	return 0;
}
