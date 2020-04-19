#include "BFS.h"

#include "../tree/QueueFrontier.h"
#include "../tree/Visited.h"
#include "../exceptions/NoPathFoundException.h"

Tree BFS::search(Grid& grid) {
  QueueFrontier frontier;
  Visited visited;

  auto root = grid.getAgentNode();
  frontier.push(root);

  while (!frontier.empty()) {
    auto node = visited.add(frontier.pop());

    if (node->getIsGoal()) {
      return Tree(root, node);
    }

    // We want UP -> LEFT -> DOWN -> RIGHT but we insert in reverse because our 
    // BFS is implemented with a queue.
    Node* up = visited.nullIfContains(grid.getEmptyNode(node->getPosition().shift(Direction::UP)));
    Node* left = visited.nullIfContains(grid.getEmptyNode(node->getPosition().shift(Direction::LEFT)));
    Node* down = visited.nullIfContains(grid.getEmptyNode(node->getPosition().shift(Direction::DOWN)));
    Node* right = visited.nullIfContains(grid.getEmptyNode(node->getPosition().shift(Direction::RIGHT)));

    frontier.push(up);
    frontier.push(left);
    frontier.push(down);
    frontier.push(right);

    // We add the child nodes in the normal order so the order of children
    // matches the order of evaluation.
    node->addChild(Direction::UP, up);
    node->addChild(Direction::LEFT, left);
    node->addChild(Direction::DOWN, down);
    node->addChild(Direction::RIGHT, right);
  }

  throw NoPathFoundException();
}