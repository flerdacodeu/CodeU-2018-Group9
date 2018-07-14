#include "Graph.h"

/*returns a pointer of the son having data equal to the given node's data in
the graph,
otherwise returns null*/
Node* Graph::Node::findSon(Node* node) {
  if (node == nullptr) {
    return nullptr;
  }

  for (Node* son : sons) {
    if (son == nullptr) {
      continue;
    }
    if (son->data == node->data) {
      return son;
    }
  }
  return nullptr;
}

Graph::Node::Node(char data) : data(data), sons(vector<Node*>()), inRank(0) {}

/*Adds node as a son of this node if it's not already a son of it.
returns true if the son is succefully added, and false otherwise*/
bool Graph::Node::addSon(Node* node) {
  if (node == nullptr) {
    return false;
  }
  Node* actualSon = findSon(node);
  if (actualSon == nullptr) {
    node->inRank++;
    sons.push_back(node);
    return true;
  }
  return false;
}

/******************************************************************************/

/*helping method that inserts the vertices's data to the alphabet vetctor,
in a topoligical order*/
void Graph::topologicalSortAux(vector<Node*> nodes, vector<char>& alphabet) {
  if (nodes.size() == 0) {
    return;
  }
  for (vector<Node*>::iterator i = nodes.begin(); i != nodes.end(); i++) {
    if (*i == nullptr) {
      continue;
    }
    if ((*i)->inRank == 0) {
      alphabet.push_back((*i)->data);
      for (Node* son : (*i)->sons) {
        if (son != nullptr) {
          son->inRank--;
        }
      }
      nodes.erase(i);
      topologicalSortAux(nodes, alphabet);
      break;
    }
  }
}

/*helping function to the Graph desrtructor,
it deletes the vertices in a topoligical order*/
void Graph::topologicalOrderDelete(vector<Node*> nodes) {
  if (nodes.size() == 0) {
    return;
  }
  for (vector<Node*>::iterator i = nodes.begin(); i != nodes.end(); i++) {
    if (*i == nullptr) {
      continue;
    }
    if ((*i)->inRank == 0) {
      for (Node* son : (*i)->sons) {
        if (son != nullptr) {
          son->inRank--;
        }
      }
      delete (*i);
      nodes.erase(i);
      topologicalOrderDelete(nodes);
      break;
    }
  }
}

Graph::Graph() : vertices(vector<Node*>()) {}

Graph::~Graph() { topologicalOrderDelete(vertices); }
/*searches for a vertix with the given char data and returns a pointer to it,
returns nullptr in any case of error and in case it's not found in the graph*/
Node* findVertix(char c) {
  for (Node* node : vertices) {
    if (node == nullptr) {
      continue;
    }
    if (node->data == c) {
      return node;
    }
  }
  return nullptr;
}

/*adds edge from the vertox with char data a to vertox with char data b,
return true if adding the edge has been succefully done,and false otherwise*/
bool Graph::addEdge(char a, char b) {
  Node* from = findVertix(a);
  if (from == nullptr) {
    from = new Node(a);
    vertices.push_back(from);
  }
  Node* to = findVertix(b);
  if (to == nullptr) {
    to = new Node(b);
    vertices.push_back(to);
  }
  from->addSon(to);
}

/*returns a vector of the data in the graph in a topological order */
vector<char> Graph::topologicalSort() {
  vector<char> alphabet = vector<char>();
  topologicalSortAux(vertices, alphabet);
  return alphabet;
}
