#include "BinaryTreeAncestors.h"

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
  tree1.insert(4, 7, "right");
  tree1.insert(3, 7, "left");
  tree1.insert(8, 4, "right");
  tree1.insert(5, 3, "right");
  tree1.insert(2, 3, "left");
  tree1.insert(1, 2, "left");
  tree1.insert(6, 2, "right");
  cout << "--- tree1 testing ---" << endl;
  tree1.printAncestors(1);  // must print 2 3 7
  cout << "---" << endl;
  tree1.printAncestors(6);  // must print 2 3 7
  cout << "---" << endl;
  tree1.printAncestors(7);  // must print nothing
  cout << "---" << endl;
  tree1.printAncestors(8);  // must print 4 7
  cout << "---" << endl;
  tree1.printLowestCommonAncestor(4, 8);  // must print 4
  cout << "---" << endl;
  tree1.printLowestCommonAncestor(1, 8);  // must print 7
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
  tree2.insert(8, 3, "right");
  tree2.insert(6, 3, "left");
  tree2.insert(11, 6, "right");
  tree2.insert(2, 6, "left");
  tree2.insert(5, 11, "right");
  tree2.insert(9, 11, "left");
  tree2.insert(13, 8, "right");
  tree2.insert(7, 13, "right");
  cout << "--- tree2 testing ---" << endl;
  tree2.printAncestors(9);  // must print 11 6 3
  cout << "---" << endl;
  tree2.printAncestors(6);  // must print 3
  cout << "---" << endl;
  tree2.printAncestors(13);  // must print 8 3
  cout << "---" << endl;
  tree2.printAncestors(5);  // must print 11 6 3
  cout << "---" << endl;
  tree2.printLowestCommonAncestor(2, 5);  // must print 6
  cout << "---" << endl;
  tree2.printLowestCommonAncestor(7, 9);  // must print 3
  cout << "---" << endl;
  tree2.printLowestCommonAncestor(7, 8);  // must print 8
  cout << "---" << endl;
  tree2.printLowestCommonAncestor(5, 13);  // must print 3
  cout << "---" << endl;
}

int main() {
  tree1Test();
  tree2Test();
  return 0;
}