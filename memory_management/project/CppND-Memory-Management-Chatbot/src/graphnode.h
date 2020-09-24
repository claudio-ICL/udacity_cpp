#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include "chatbot.h"
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

// forward declarations
class GraphEdge;

class GraphNode {
private:
  // data handles (owned)
  std::vector<std::unique_ptr<GraphEdge>>
      _childEdges; // edges to subsequent nodes
  // data handles (not owned)
  std::vector<GraphEdge *> _parentEdges; // edges to preceding nodes
  ChatBot _chatBot;

  // proprietary members
  int _id;
  std::vector<std::string> _answers;

public:
  // constructor / destructor
  GraphNode(int id);
  ~GraphNode();

  // getter / setter
  int GetID() const { return _id; }
  int GetNumberOfChildEdges() const { return _childEdges.size(); }
  GraphEdge *GetChildEdgeAtIndex(int index);
  std::vector<std::string> GetAnswers() { return _answers; }
  int GetNumberOfParents() const { return _parentEdges.size(); }
  bool IsRoot() { return this == _chatBot.GetRootNode(); }

  // proprietary functions
  void AddToken(std::string token); // add answers to list
  void AddParentEdge(GraphEdge *edge);
  void AddChildEdge(std::unique_ptr<GraphEdge> &&edge);
  void MoveChatbotHere(ChatBot );
  void MoveChatbotToNewNode(GraphNode *newNode);
};

#endif /* GRAPHNODE_H_ */
