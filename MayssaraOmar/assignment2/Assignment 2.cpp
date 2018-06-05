/* ASSUMPTIONS
 * print_ancestors method: Binary Tree has unique keys
 * common_ancestor method: if a node is an ancestor of the other node, return that node // that way there is always an answer
 */
#include <iostream>
#include <stack>
#include <utility>
using namespace std;

template<class T>
class binary_tree;

template<class T>
class tree_node {
	T data;
	tree_node *left, *right;
public:
	tree_node(const T &data, tree_node* left, tree_node* right) :
			data(data), left(left), right(right) {
	}
	friend class binary_tree<T> ;
// the binary_tree class is declared as tree_node's friend which means that binary_tree can access the private members of tree_node
};

template<class T>
class binary_tree {

	tree_node<T> *root;
public:
	binary_tree();
	~binary_tree();
	tree_node<T>* insert_root(const T &);
	tree_node<T>* insert_left(tree_node<T>*, const T &); // insert an element to the left of the node // if an element to the left already exists, it overwrites it
	tree_node<T>* insert_right(tree_node<T>*, const T &); // insert an element to the right of the node // if an element to the right already exists, it overwrites it
	tree_node<T>* get_root();
	tree_node<T>* get_left(tree_node<T>*);
	tree_node<T>* get_right(tree_node<T>*);
	void remove_leaf(tree_node<T>*); // removes a leaf node // if the node isn't a leaf it doesn't remove anything
	bool empty();
	void clear();
	void print_ancestors(const T &target); // print ancestors' keys starting from the parent to the root separated by spaces
	pair<tree_node<T>*, T> common_ancestor(tree_node<T>*, tree_node<T>*); // in case of an error, the first part of the returned pair will be nullptr
private:
	bool print_ancestors_helper(tree_node<T>* current, const T &target);
	pair<tree_node<T>*, int> common_ancestor_helper(tree_node<T>*,
			tree_node<T>*, tree_node<T>*);

};
template<class T>
binary_tree<T>::binary_tree() {
	root = nullptr;
}

template<class T>
binary_tree<T>::~binary_tree() {
	clear();
}

template<class T>
tree_node<T>* binary_tree<T>::insert_root(const T &data) {
	return root = new tree_node<T>(data, nullptr, nullptr);
}

template<class T>
tree_node<T>* binary_tree<T>::insert_left(tree_node<T>* current,
		const T &data) {
	if (current) {
		if (!current->left) {
			current->left = new tree_node<T>(data, nullptr, nullptr);
		} else {
			current->left->data = data;
		}
		return current->left;
	}
	return nullptr;
}
template<class T>
tree_node<T>* binary_tree<T>::insert_right(tree_node<T>* current,
		const T &data) {
	if (current) {
		if (!current->right) {
			current->right = new tree_node<T>(data, nullptr, nullptr);

		} else {
			current->right->data = data;
		}
		return current->right;
	}
	return nullptr;
}
template<class T>
tree_node<T>* binary_tree<T>::get_root() {
	return root;
}
template<class T>
tree_node<T>* binary_tree<T>::get_left(tree_node<T>* current) {
	if (current) {
		return current->left;
	}
	return nullptr;
}
template<class T>
tree_node<T>* binary_tree<T>::get_right(tree_node<T>* current) {
	if (current) {
		return current->right;
	}
	return nullptr;
}
template<class T>
void binary_tree<T>::remove_leaf(tree_node<T>* current) {
	if (current && !current->left && !current->right) {
		delete current;
	}
}

template<class T>
bool binary_tree<T>::empty() {
	return root == nullptr;
}
template<class T>
void binary_tree<T>::clear() {
	if (empty()) {
		return;
	}
	stack<tree_node<T>*> st;
	st.push(root);
	while (!st.empty()) {
		tree_node<T>* node = st.top();
		st.pop();
		if (node->right)
			st.push(node->right);
		if (node->left)
			st.push(node->left);
		delete node;
	}
	root = nullptr;
	return;
}
template<class T>
bool binary_tree<T>::print_ancestors_helper(tree_node<T>* current,
		const T &target) {
	if (!current) {
		return false;
	}

	if (print_ancestors_helper(current->left, target)) {
		cout << current->data << ' ';
		return true;
	}
	if (print_ancestors_helper(current->right, target)) {
		cout << current->data << ' ';
		return true;
	}
	if (current->data == target) {
		return true;
	}
	return false;
}
template<class T>
void binary_tree<T>::print_ancestors(const T &target) {
	if (!print_ancestors_helper(root, target)) {
		cout << "ERROR: key not found in tree";
	}
	cout << endl;
}
template<class T>
pair<tree_node<T>*, int> binary_tree<T>::common_ancestor_helper(
		tree_node<T>* current, tree_node<T>* first, tree_node<T>* second) {

	if (!current || !first || !second || first == second) {
		return make_pair(nullptr, 0);
	}

	pair<tree_node<T>*, int> res_left = common_ancestor_helper(current->left,
			first, second);
	if (res_left.first)
		return res_left;

	pair<tree_node<T>*, int> res_right = common_ancestor_helper(current->right,
			first, second);
	if (res_right.first)
		return res_right;

	if (current == first || current == second)
		res_left.second++;
	res_left.second = res_left.second + res_right.second;
	if (res_left.second == 2) {
		res_left.first = current;
		return res_left;
	}

	return res_left;
}
template<class T>
pair<tree_node<T>*, T> binary_tree<T>::common_ancestor(tree_node<T> *first,
		tree_node<T>* second) {
	pair<tree_node<T>*, int> result = common_ancestor_helper(root, first,
			second);
	if (result.first) {
		result.second = result.first->data;
	}
	return result;
}

int main() {
	binary_tree<int> bt;

	// build test binary tree
	bt.insert_root(7);
	tree_node<int>* nl = bt.insert_left(bt.get_root(), 3);
	tree_node<int>* nr = bt.insert_right(bt.get_root(), 4);
	bt.insert_right(nr, 8);
	bt.insert_right(nl, 5);
	nl = bt.insert_left(nl, 2);
	bt.insert_right(nl, 6);
	bt.insert_left(nl, 1);

	// test print_ancestors
	cout << "Test print_ancestors method:" << endl;
	cout << "10 Ancestors: "; bt.print_ancestors(10); // error
	cout << "7 Ancestors: "; bt.print_ancestors(7); // prints new line // root (no ancestors)
	cout << "6 Ancestors: "; bt.print_ancestors(6); // prints ancestors

	// test common_ancestor
	cout << endl << "Test common_ancestor method:" << endl;

	pair<tree_node<int>*, int> result;

	result = bt.common_ancestor(bt.get_right(bt.get_left(bt.get_root())),
			bt.get_right(nl)); // node with key 5, node with key 6
	cout << "Common ancestor for node with key 5 and node with key 6: ";
	if (!result.first) {
		cout << "ERROR" << endl;
	} else {
		cout << result.second << endl;
	}

	result = bt.common_ancestor(bt.get_right(nr), nr); // node with key 8, node with key 4
	cout << "Common ancestor for node with key 8 and node with key 4: ";
	if (!result.first) {
		cout << "ERROR" << endl;
	} else {
		cout << result.second << endl;
	}

	result = bt.common_ancestor(nr, nr); // node with key 4, node with key 4 // same node
	cout << "Common ancestor for node with key 4 and node with key 4 (same node): ";
	if (!result.first) {
		cout << "ERROR" << endl;
	} else {
		cout << result.second << endl;
	}
	result = bt.common_ancestor(bt.get_root(), nl); // root with key 7 (root), node with key 2
	cout << "Common ancestor for node with key 7 (root) and node with key 2: ";
	if (!result.first) {
		cout << "ERROR" << endl;
	} else {
		cout << result.second << endl;
	}
	result = bt.common_ancestor(bt.get_root(), nullptr); // root with key 7, nullptr
	cout << "Common ancestor for node with key 7 and nullptr: ";
	if (!result.first) {
		cout << "ERROR" << endl;
	} else {
		cout << result.second << endl;
	}

	// test clear and empty methods
	cout << endl << "Test clear and empty methods:" << endl;
	cout << "Before clearing: " << bt.empty() << endl;
	bt.clear();
	cout << "After clearing: " << bt.empty() << endl;
	return 0;
}

