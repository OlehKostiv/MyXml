#include "Logger.h"
#include "myXmlNode.h"
#include "myCstrFUnctional.h"

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
MyXml::Node::Node(const Char * nodeName)
{
    name = AllocateCopyOf(nodeName);
}
MyXml::Node::Node(const Char* nodeName, const Char* nodeText):
    Node(nodeName)
{
    text = AllocateCopyOf(nodeText);
}
MyXml::Node::Node(const Char* nodeName, PropertyChain& nodeProperties):
    Node(nodeName)
{
    properties = static_cast<PropertyChain&&>(nodeProperties);
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
MyXml::Char* MyXml::Node::ToPChar() const
{
    Char buff[1024] = "";
    
    Char* props = properties.ToPChar();
    std::sprintf(buff, "<%s %s", name, props);
    delete[] props;

    if (firstChild || text)
    {
        std::strcat(buff, ">");
        
        if (firstChild)
        {
            std::strcat(buff, "%s");            
        }
        if (text)
        {
            std::strcat(buff, text);
        }

        Char* buffCat = buff;
        while (*++buffCat);
        std::sprintf(buffCat, "</%s>", name);
    }
    else
    {
        std::strcat(buff, " />");
    }
    return AllocateCopyOf(buff);
}

MyXml::Element::Element(const Char * elementName, const Char * elementText):
    Node(elementName, elementText)
{}
MyXml::Element::Element(const Char * elementName, const Char * elementText, PropertyChain & elementProperties):
    Node(elementName, elementText, elementProperties)
{}
MyXml::Element::~Element()
{
    Log.InRed("~Element();");
}

MyXml::Comment::Comment(const Char * commentText):
    Node()
{
    text = AllocateCopyOf(commentText);
}

MyXml::Comment::~Comment()
{
    Log.InRed("~Comment();");
}
