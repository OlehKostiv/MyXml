#include "Logger.h"
#include "myXmlNode.h"

#include <cstring>
#include <cassert>

#ifdef _DEBUG
static Logger Log(std::cout);
#else 
#include <fstream>
static char filePath[] = __FILE__ ".txt";
static std::ofstream logFile(filePath, std::ios::out);
static Logger Log(logFile);
#endif

MyXml::Node::Node() :
	nextSister		(nullptr),
	firstChild		(nullptr),
	name			(nullptr),
	text			(nullptr)
{
	Log.InRed("Node();");
}

MyXml::Node::Node(const Char* nodeName, const Char* nodeText):
	Node()
{
	if (nodeName)
	{
		size_t nameLength = std::strlen(nodeName);
		name = new Char[nameLength + 1];
		std::strcpy(name, nodeName);
	}

	if (nodeText)
	{
		size_t textLength = std::strlen(nodeText);
		text = new Char[textLength + 1];
		std::strcpy(text, nodeText);
	}

	Log.InRed("Node(...)");
}

MyXml::Node::Node(const Char * nodeName, const Char * nodeText, PropertyChain& nodeProperties):
    Node(nodeName, nodeText)
{
    properties = static_cast<PropertyChain&&>(nodeProperties);
}

MyXml::Node::~Node()
{
	if (name)
		delete[] name;
	if (text)
		delete[] text;

    Log.InRed("~Node();");
}
MyXml::Node& MyXml::Node::AppendChild(Node* newChild)
{
    assert(newChild != nullptr);

    newChild->nextSister = this->firstChild;
    this->firstChild = newChild;

    return *this;
}
MyXml::Node& MyXml::Node::AppendSibling(Node* newSibling)
{
    assert(newSibling != nullptr);

    newSibling->nextSister = this->nextSister;
    this->nextSister = newSibling;

    return *this;
}

MyXml::Char * MyXml::Node::ToPchar() const
{
    Char buff[1024]{ 0 };
    /*
    if (firstChild == nullptr)
    {
        std::sprintf(buff, "<%s", name);
        for (Property::Iter pi = properties.firstProperty)
    }

    sprintf("<%s>", )*/

    return nullptr;
}
