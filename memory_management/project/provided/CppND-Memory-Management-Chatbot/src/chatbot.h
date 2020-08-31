#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include"chatlogic.h"

class GraphNode; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();
    ChatBot(ChatBot&);
    ChatBot(ChatBot&&);
    ChatBot& operator=(ChatBot&);
    ChatBot& operator=(ChatBot&&);

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    GraphNode* GetCurrentNode(){return _currentNode;}
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    GraphNode* GetRootNode(){return _rootNode;}
    void SetChatLogic(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    ChatLogic* GetChatLogic(){return _chatLogic;}
    wxBitmap *GetImage() { return _image; }
    void InvalidateNonOwned(){ _currentNode = nullptr; _rootNode =nullptr; _chatLogic = nullptr;}
    void UpdateChatLogicToThis(){_chatLogic->SetChatbotHandle(this);}
    ChatBot* GetChatbotFromChatLogic() {return (_chatLogic!=nullptr)? _chatLogic->GetChatbotHandle(): nullptr;}

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */
