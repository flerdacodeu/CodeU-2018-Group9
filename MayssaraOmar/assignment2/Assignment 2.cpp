/* ASSUMPTIONS
 * find_ancestors method: Binary Tree has unique keys
 * common_ancestor method: if a node is an ancestor of the other node, return that node // that way there is always an answer
 */
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

template<class T>
class binary_tree;

enum child_type {
	left_child, right_child
};

template<class T>
class tree_node {
	T data;
	tree_node *left, *right;
public:
	tree_node(const T &data, tree_node* left, tree_node* right) :
			data(data), left(left), right(right) {
	}
	const T& get_data() const {
		return data;
	}
	const tree_node* get_left() const {
		return left;
	}
	const tree_node* get_right() const {
		return right;
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
	tree_node<T>* insert_root(const T &data); // insert root and returns pointer to it // if root already exists, it overwrites its data and returns pointer to its existing node
	tree_node<T>* insert_child(const T &parent_data, const T &child_data,
			child_type type); // insert an element to the left/right of the node (depends on child_type) returns pointer to it // if an element already exists, it overwrites its data and returns pointer to it // returns nullptr if parent doesn't exist
	tree_node<T>* get_root(); // returns root node if exists, otherwise returns nullptr
	tree_node<T>* get_child(const T &parent_data, child_type type); // returns pointer to child node to the left/right (depends on child_type) // if parent node doesn't exist, it returns nullptr
	void remove_leaf_root(); // removes root if and only if it's also a leaf, otherwise it doesn't remove anything
	void remove_leaf_child(const T& parent_data, child_type type); // removes a leaf node // if the node isn't a leaf it doesn't remove anything
	tree_node<T>* find(const T &data); // returns tree_node pointer if data found in the tree, else it returns nullptr
	bool empty();
	void clear();
	bool find_ancestors(const T &target, vector<T> &ancestors); // returns false if target key doesn't exist in the tree and returns true otherwise // the vector ancestors parameter will contain ancestors keys starting from the parent of target node to the root or vector will be empty if target key is the root's key
	tree_node<T>* common_ancestor(const T &first_data, const T &second_data); // returns a pointer to common ancestor node // in case of an error, it returns nullptr

	enum printing_order {
		inorder, preorder, postorder
	};
	void binary_tree<T>::print(tree_node<T>* current, printing_order);

private:
	tree_node<T>* find(const T &data, tree_node<T>* current);
	void clear(tree_node<T>*);
	bool find_ancestors(tree_node<T>* current, const T &target,
			vector<T> &ancestors);
	pair<tree_node<T>*, int> common_ancestor(tree_node<T>* current,
			tree_node<T>* first, tree_node<T>* second); //returns a pair of which the first part is the found common ancestor (or nullptr in case of an error) and the second part represent how many nodes of the 2 nodes (first and second) were found

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
	// insert root
	if (!root) {
		root = new tree_node<T>(data, nullptr, nullptr);
	} else {
		root->data = data;
	}
	return root;
}
template<class T>
tree_node<T>* binary_tree<T>::insert_child(const T &parent_data,
		const T &child_data, child_type type) {
	// tree can't have duplicate data
	tree_node<T>* found = find(child_data);
	if (found) { // data to be inserted already exists in tree
		return found;
	}
	// insert child
	tree_node<T>* parent = find(parent_data);
	if (parent) { // node exists in tree
		tree_node<T>** new_node =
				(type == left_child) ? &parent->left : &parent->right;
		if (!*new_node) {
			*new_node = new tree_node<T>(child_data, nullptr, nullptr);
		} else {
			(*new_node)->data = child_data;
		}
		return *new_node;
	}
	return nullptr;
}
template<class T>
tree_node<T>* binary_tree<T>::get_root() {
	return root;
}
template<class T>
tree_node<T>* binary_tree<T>::get_child(const T &parent_data, child_type type) {
	tree_node<T>* parent = find(parent_data);
	if (parent) {
		return type == left_child ? parent->left : parent->right;
	}
	return nullptr;
}
template<class T>
void binary_tree<T>::remove_leaf_root() {
	if (root && !root->left && !root->right) {
		delete root;
		root = nullptr;
	}
}
template<class T>
void binary_tree<T>::remove_leaf_child(const T& parent_data, child_type type) {
	tree_node<T>* parent = find(parent_data);
	if (parent) {
		tree_node<T>** child =
				(type == left_child) ? &parent->left : &parent->right;
		if (!*child) {
			return;
		} else if (!(*child)->left && !(*child)->right) { // leaf node
			delete *child;
			*child = nullptr;
		}
	}
}
template<class T>
tree_node<T>* binary_tree<T>::find(const T& data) {
	return find(data, root);
}
template<class T>
tree_node<T>* binary_tree<T>::find(const T& data, tree_node<T>* current) {
	if (!current) {
		return nullptr;
	}
	if (current->data == data) {
		return current;
	}
	tree_node<T>* ret = find(data, current->left);
	return ret ? ret : find(data, current->right);
}
template<class T>
bool binary_tree<T>::empty() {
	return root == nullptr;
}
template<class T>
void binary_tree<T>::clear() {
	clear(root);
	root = nullptr;
}
template<class T>
void binary_tree<T>::clear(tree_node<T>* current) {
	if (!current) {
		return;
	}
	clear(current->left);
	clear(current->right);
	delete current;
}
template<class T>
bool binary_tree<T>::find_ancestors(tree_node<T>* current, const T &target,
		vector<T>& ancestors) {
	if (!current) {
		return false;
	}
	if (find_ancestors(current->left, target, ancestors)
			|| find_ancestors(current->right, target, ancestors)) {
		ancestors.push_back(current->data);
		return true;
	}
	if (current->data == target) {
		return true;
	}
	return false;
}
template<class T>
bool binary_tree<T>::find_ancestors(const T &target, vector<T> &ancestors) {
	return find_ancestors(root, target, ancestors);
}
template<class T>
pair<tree_node<T>*, int> binary_tree<T>::common_ancestor(tree_node<T>* current,
		tree_node<T>* first, tree_node<T>* second) {

	if (!current || !first || !second || first == second) {
		return make_pair(nullptr, 0);
	}

	pair<tree_node<T>*, int> res_left = common_ancestor(current->left, first,
			second);
	if (res_left.first) {
		return res_left;
	}

	pair<tree_node<T>*, int> res_right = common_ancestor(current->right, first,
			second);
	if (res_right.first) {
		return res_right;
	}

	if (current == first || current == second)
		res_left.second++;
	res_left.second = res_left.second + res_right.second;
	if (res_left.second == 2) {
		res_left.first = current;
	}
	return res_left;
}
template<class T>
tree_node<T>* binary_tree<T>::common_ancestor(const T &first_data,
		const T &second_data) {
	tree_node<T>* first = find(first_data);
	tree_node<T>* second = find(second_data);
	pair<tree_node<T>*, int> result = common_ancestor(root, first, second);
	return result.first;
}
template<class T>
void binary_tree<T>::print(tree_node<T>* current, printing_order order) {
	if (!current) {
		return;
	}
	if (order == preorder) {
		cout << current->data << ' ';
	}
	print(current->left, order);
	if (order == inorder) {
		cout << current->data << ' ';
	}
	print(current->right, order);
	if (order == postorder) {
		cout << current->data << ' ';
	}
}
int main() {
	binary_tree<int> bt;

	// build test binary tree
	bt.insert_root(7);
	bt.insert_child(7, 3, left_child);
	bt.insert_child(7, 4, right_child);
	bt.insert_child(4, 8, right_child);
	bt.insert_child(3, 5, right_child);
	bt.insert_child(3, 2, left_child);
	bt.insert_child(2, 6, right_child);
	bt.insert_child(2, 1, left_child);
	bt.print(bt.get_root(), bt.preorder);
	cout << endl;

	// test print_ancestors
	vector<int> ancestors;
	cout << endl << "Test find_ancestors method:" << endl;
	// error
	cout << "10 Ancestors: ";
	if (!bt.find_ancestors(10, ancestors)) {
		cout << "key not found in tree" << endl;
	} else {
		for (int ancestor : ancestors) {
			cout << ancestor << " ";
		}
		cout << endl;
	}
	// prints new line // root (no ancestors)
	cout << "7 Ancestors: ";
	if (!bt.find_ancestors(7, ancestors)) {
		cout << "ERROR: key not found in tree" << endl;
	} else {
		for (int ancestor : ancestors) {
			cout << ancestor << " ";
		}
		cout << endl;
	}
	// print ancestors
	cout << "6 Ancestors: ";
	if (!bt.find_ancestors(6, ancestors)) {
		cout << "ERROR: key not found in tree" << endl;
	} else {
		for (int ancestor : ancestors) {
			cout << ancestor << " ";
		}
		cout << endl;
	}

	// test common_ancestor
	cout << endl << "Test common_ancestor method:" << endl;

	tree_node<int>* result;

	result = bt.common_ancestor(5, 6); // node with key 5, node with key 6 // 3
	cout << "Common ancestor for node with key 5 and node with key 6: ";
	if (!result) {
		cout << "ERROR" << endl;
	} else {
		cout << (*result).get_data() << endl;
	}

	result = bt.common_ancestor(8, 4); // node with key 8, node with key 4 // 4
	cout << "Common ancestor for node with key 8 and node with key 4: ";
	if (!result) {
		cout << "ERROR" << endl;
	} else {
		cout << (*result).get_data() << endl;
	}

	result = bt.common_ancestor(4, 4); // node with key 4, node with key 4 // same node // error
	cout
			<< "Common ancestor for node with key 4 and node with key 4 (same node): ";
	if (!result) {
		cout << "ERROR" << endl;
	} else {
		cout << (*result).get_data() << endl;
	}
	result = bt.common_ancestor(7, 2); // root with key 7 (root), node with key 2 // 7
	cout << "Common ancestor for node with key 7 (root) and node with key 2: ";
	if (!result) {
		cout << "ERROR" << endl;
	} else {
		cout << (*result).get_data() << endl;
	}
	result = bt.common_ancestor(7, 100); // root with key 7, node with key 100 (doesn't exist) // error
	cout << "Common ancestor for node with key 7 and nullptr: ";
	if (!result) {
		cout << "ERROR" << endl;
	} else {
		cout << (*result).get_data() << endl;
	}

	// test node's getters
	cout << endl << "test node's getters:" << endl;
	tree_node<int> * node = bt.find(4);
	if (node) {
		cout << node->get_data() << ' ';
		if (node->get_left() == nullptr)
			cout << "null" << ' ';
		else
			cout << node->get_left()->get_data() << ' ';
		if (node->get_right() == nullptr)
			cout << "null" << endl;
		else
			cout << node->get_right()->get_data() << endl;
	}

	// test remove leaf
	cout << endl << "test remove leaf:" << endl;
	bt.print(bt.get_root(), bt.inorder);
	cout << endl;
	bt.remove_leaf_child(4, right_child);
	bt.print(bt.get_root(), bt.inorder);
	cout << endl;

	// test clear and empty methods
	cout << endl << "Test clear and empty methods:" << endl;
	cout << "Before clearing: " << bt.empty() << endl;
	bt.clear();
	cout << "After clearing: " << bt.empty() << endl;

	return 0;
}

