#include <bits/stdc++.h>

using namespace std;

struct IndicePair {
  int start;
  int end;
  IndicePair(int start, int end) {
    this->start = start;
    this->end = end;
  }
  IndicePair() {

  }
};

struct Node {
  IndicePair indices;
  Node *parent;
  vector<Node*> children;
  int distanceFromRoot;
  bool isRoot;
  bool isEmpty;

  Node(int start, int end, Node *parent, int distanceFromRoot, bool isEmpty) {
    IndicePair ip = IndicePair(start, end);
    this->indices = ip;
    this->parent = parent;
    this->children = {};
    this->distanceFromRoot = distanceFromRoot;
    this->isRoot = false;
    this->isEmpty = isEmpty;
  }
  Node() {
    this->children = {};
    this->distanceFromRoot = 0;
    this->isRoot = true;
  }
};

void addSuffixInTree(Node *current, int start, int end, string str) {
  if (current->children.size() == 0) {
    Node* newNode = new Node(start, end, current, current->distanceFromRoot + 1, false);
    current->children.push_back(newNode);
    if (!current->isRoot) {
      Node* newEmptyNode = new Node(-1, -1, current, current->distanceFromRoot + 1, true);
      current->children.push_back(newEmptyNode);
    }
  } else {
    bool found = false;
    for (Node *child : current->children) {
      if (!(child->isEmpty) && str[start] == str[child->indices.start]) {
        int childSize = (child->indices.end - child->indices.start) + 1;
        int suffixSize = (end - start) + 1;

        int aux = 1;
        while(1) {
          if (aux == childSize) {
            addSuffixInTree(child, start+aux, end, str);
            break;
          }
          if (str[start + aux] != str[(child->indices.start) + aux]) {
            
            Node* newNode = new Node((child->indices.start) + aux, end, child, child->distanceFromRoot + 1, false);
            child->children.push_back(newNode);

            child->indices.end = ((child->indices.start) + aux) - 1;

            addSuffixInTree(child, start+aux, end, str);

            break;
          } else {
            aux++;
          }
        }

        found = true;
        break;
      }
    }

    if(!found) {
      Node* newNode = new Node(start, end, current, current->distanceFromRoot + 1, false);
      current->children.push_back(newNode);
    }


  }
}

int main() {

  string teste = "minimize";
  Node root = Node();

  for(int i=(teste.length())-1; i>=0; i--) {
    addSuffixInTree(&root, i, teste.length() - 1, teste);
  }

  cout << root.children[4]->indices.start << " " << root.children[4]->indices.end << endl;

  return 0;
}