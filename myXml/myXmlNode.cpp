#include "Logger.h"
#include "myXmlNode.h"
#include "myCstrFUnctional.h"

#include <cstring>
#include <cassert>
#include <iostream>

#ifdef _DEBUG
static Logger Log(std::cout);
#else 
#include <fstream>
static char* fp = __FILE__;
static char* filePath = MyXml::AllocateACatOf(fp, ".txt");
static std::ofstream logFile(filePath, std::ios::out);
static Logger Log(logFile);
static int freeFP = []() { delete[] filePath; return 0;}();
#endif



MyXml::Node::Node() :
	nextSister		(nullptr),
	firstChild		(nullptr),
	name			(nullptr),
	text			(nullptr)
{}
MyXml::Node::Node(const Char* nodeName)
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
MyXml::Node::Node(const Char* nodeName, const Char* nodeText, PropertyChain& nodeProperties):
    Node(nodeName, nodeText)
{
    properties = static_cast<PropertyChain&&>(nodeProperties);
}
MyXml::Node::~Node()
{
    Log.InRed("~Node();");

	if (name)
		delete[] name;
	if (text)
		delete[] text;
}

MyXml::Node* MyXml::Node::AppendChild(Node* newChild)
{
    //std::cout << this << " " << this->name << " ap c " << newChild->name << std::endl;  
    if(!newChild->nextSister)
        newChild->nextSister = this->firstChild;
    else
        newChild->AppendSibling(this->firstChild);

    this->firstChild = newChild;

    return &(*this);
}
MyXml::Node* MyXml::Node::AppendSibling(Node* newSibling)
{
    //std::cout << this << " " << this->name << " ap s " << newSibling->name << std::endl;
    if (!this->nextSister)
        this->nextSister = newSibling;
    else
    {
        this->nextSister->AppendSibling(newSibling);
    }
    return &(*this);
}
MyXml::Node* MyXml::Node::AppendProperty(Property* newProperty)
{
    properties.Append(newProperty);
    return this;
}
MyXml::Node* MyXml::Node::FirstChild() const
{
    return firstChild;
}
MyXml::Node* MyXml::Node::NextSibling() const
{
    return (nextSister);
}
MyXml::Char* MyXml::Node::ToCharStr() const
{
    Char buff[buffsizeHuge] = "";
        
    std::sprintf(buff, "<%s", name);

    if (!properties.IsEmpty()) 
    {
        Char propBuff[buffsizeSmall] = " ";
        Char* props = properties.ToCharStr();
        std::strcat(propBuff, props);
        delete[] props;
        std::strcat(buff, propBuff);
    }

    if (firstChild || text)
    {
        std::strcat(buff, ">\n");
        
        if (firstChild)
        {
            std::strcat(buff, "%s");            
        }
        if (text)
        {
            std::strcat(buff, text);
            std::strcat(buff, "\n");
        }

        Char* buffCat = buff;
        while (*++buffCat);
        std::sprintf(buffCat, "</%s>\n", name);
    }
    else
    {
        std::strcat(buff, "/>\n");
    }
    return AllocateCopyOf(buff);
}
MyXml::Node* MyXml::Node::operator->()
{
    return this;
}

MyXml::Element::Element(const Char* elementName):
    Node(elementName)
{}
MyXml::Element::Element(const Char* elementName, PropertyChain& elementProperties):
    Node(elementName, elementProperties)
{}
MyXml::Element::Element(const Char* elementName, const Char* elementText):
    Node(elementName, elementText)
{}
MyXml::Element::Element(const Char* elementName, const Char* elementText, PropertyChain& elementProperties):
    Node(elementName, elementText, elementProperties)
{}
MyXml::Element::~Element()
{
    Char buff[buffsizeSmall] = "~Element(): ";
    if (name)
        std::strcat(buff, name);
    Log.InRed(buff);
}

MyXml::Comment::Comment(const Char* commentText):
    Element()
{
    text = AllocateCopyOf(commentText);
}
MyXml::Comment::~Comment()
{
    Char buff[buffsizeSmall] = "~Comment();";
    if (text)
        std::strcat(buff, text);
    Log.InRed(buff);
}
MyXml::Char* MyXml::Comment::ToCharStr() const
{
    Char buff[buffsizeHuge];
    sprintf(buff, "<!--%s-->\n", text);
    return AllocateCopyOf(buff);
}
