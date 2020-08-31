#include "graphedge.h"
#include "graphnode.h"
#include<cassert>

GraphNode::GraphNode(int id): _id(id){
}

GraphNode::~GraphNode()
{
  //The owned data handles are smart pointers, so their de-allocation is automatic
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddParentEdge(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddChildEdge(std::unique_ptr<GraphEdge>&& edge)
{
    _childEdges.push_back(std::move(edge));
}

void GraphNode::MoveChatbotHere(ChatBot &chatbot)
{
  _chatBot = new ChatBot();
  *_chatBot = std::move(chatbot);
  _chatBot->UpdateChatLogicToThis();
  _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(*_chatBot);
    delete _chatBot;
}

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{

    return _childEdges[index].get();

}
