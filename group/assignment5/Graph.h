#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*The Graph class: to be built according to a dictionary*/
class Graph {
  /******************************************************************************/
  class Node {
    char data;
    vector<Node*> sons;
    /*counts the number of edges entring to this node*/
    int inRank;
    friend class Graph;

    /*returns a pointer of the son having data equal to the given node's data in
    the graph,
    otherwise returns null*/
    Node* findSon(Node* node);

   public:
    Node(char data);

    /*Adds node as a son of this node if it's not already a son of it.
    returns true if the son is succefully added, and false otherwise*/
    bool addSon(Node* node);
  };
  /******************************************************************************/

  /*the vertices in te graph contains*/
  vector<Node*> vertices;

  /*helping method that inserts the vertices's data to the alphabet vetctor,
  in a topoligical order*/
  void topologicalSortAux(vector<Node*> nodes, vector<char>& alphabet);

  /*helping function to the Graph desrtructor,
  it deletes the vertices in a topoligical order*/
  void topologicalOrderDelete(vector<Node*> nodes);

 public:
  Graph() : vertices(vector<Node*>()) {}

  ~Graph() { topologicalOrderDelete(vertices); }
  /*searches for a vertix with the given char data and returns a pointer to it,
  returns nullptr in any case of error and in case it's not found in the graph*/
  Node* findVertix(char c);
  /*adds edge from the vertox with char data a to vertox with char data b,
  return true if adding the edge has been succefully done,and false otherwise*/
  bool addEdge(char a, char b);

  /*returns a vector of the data in the graph in a topological order */
  vector<char> topologicalSort();
};
