#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Position.h"
#include "Direction.h"

class Node;

struct Edge {
  Direction direction;
  std::unique_ptr<Node> node;

  Edge(Direction direction, Node* node);
};

class Node {
private:
  Node* parent;
  std::vector<Edge> children;
  Position pos;
  bool isGoal;

public:
  Node(Position pos, bool isGoal);

  bool isAncestor(Node& node);
  void addChild(Direction direction, Node* child);

  Position getPosition() const;
  bool getIsGoal() const;

  std::string toString(int level = 0);
};

bool operator==(const Node& a, const Node& b);