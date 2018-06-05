#include "BinaryTreeAncestors.h"

void printAncestorVector(vector<int> ancestors) {
  for (int a : ancestors) {
    cout << a << " ";
  }
  cout << endl;
}
void tree1Test() {
  /*Building the binary tree - tree1 in the assignment example */
  /*
                7
            |      |
            3      4
        |    |       |
        2    5       8
      |   |
      1   6
  */
  BinaryTree<int> tree1 = BinaryTree<int>(7);
  tree1.insert(4, 7, Right);
  tree1.insert(3, 7, Left);
  tree1.insert(8, 4, Right);
  tree1.insert(5, 3, Right);
  tree1.insert(2, 3, Left);
  tree1.insert(1, 2, Left);
  tree1.insert(6, 2, Right);
  cout << "--- tree1 testing ---" << endl;
  printAncestorVector(tree1.getAncestors(1));  // must print 2 3 7
  cout << "---" << endl;
  printAncestorVector(tree1.getAncestors(6));  // must print 2 3 7
  cout << "---" << endl;
  printAncestorVector(tree1.getAncestors(7));  // must print nothing
  cout << "---" << endl;
  printAncestorVector(tree1.getAncestors(8));  // must print 4 7
  cout << "---" << endl;
  printAncestorVector(tree1.lowestCommonAncestor(4, 8));  // must print 4
  cout << "---" << endl;
  printAncestorVector(tree1.lowestCommonAncestor(1, 8));  // must print 7
  cout << "---" << endl;
}

void tree2Test() {
  /*Building the binary tree - tree2 */
  /*
                3
            |      |
            6      8
        |   |       |
        2  11       13
           |         |
           6         7
         |  |
         9  5
  */
  BinaryTree<int> tree2 = BinaryTree<int>(3);
  tree2.insert(8, 3, Right);
  tree2.insert(6, 3, Left);
  tree2.insert(11, 6, Right);
  tree2.insert(2, 6, Left);
  tree2.insert(5, 11, Right);
  tree2.insert(9, 11, Left);
  tree2.insert(13, 8, Right);
  tree2.insert(7, 13, Right);
  cout << "--- tree2 testing ---" << endl;
  printAncestorVector(tree2.getAncestors(9));  // must print 11 6 3
  cout << "---" << endl;
  printAncestorVector(tree2.getAncestors(6));  // must print 3
  cout << "---" << endl;
  printAncestorVector(tree2.getAncestors(13));  // must print 8 3
  cout << "---" << endl;
  printAncestorVector(tree2.getAncestors(5));  // must print 11 6 3
  cout << "---" << endl;
  printAncestorVector(tree2.lowestCommonAncestor(2, 5));  // must print 6
  cout << "---" << endl;
  printAncestorVector(tree2.lowestCommonAncestor(7, 9));  // must print 3
  cout << "---" << endl;
  printAncestorVector(tree2.lowestCommonAncestor(7, 8));  // must print 8
  cout << "---" << endl;
  printAncestorVector(tree2.lowestCommonAncestor(5, 13));  // must print 3
  cout << "---" << endl;
}

int main() {
  tree1Test();
  tree2Test();
  return 0;
}
