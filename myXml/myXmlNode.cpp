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
static char* filePath = MyXml::AllocateACatOf((char*)__FILE__, ".txt");
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
MyXml::Node::Node(const Char* nodeName):
    Node()
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
MyXml::Node::Node(Node && source):
    name(source.name),
    text(source.text),
    firstChild(source.firstChild),
    nextSister(source.nextSister),
    properties(static_cast<PropertyChain&&>(source.properties))

{
    source.name = source.text = nullptr;
    source.firstChild = source.nextSister = nullptr;
    Log.InRed("->Node();");
}
MyXml::Node::~Node()
{
    Log.InRed("~Node();");

	if (name)
		delete[] name;
	if (text)
		delete[] text;
}

MyXml::Node::Iter MyXml::Node::AppendChildrenPtr(Node::Iter newChild)
{
    //std::cout << this << " " << this->name << " ap c " << newChild->name << std::endl;  
    if(!newChild->nextSister)
        newChild->nextSister = this->firstChild;
    else
        newChild->AppendSiblingsPtr(this->firstChild);

    this->firstChild = newChild;

    return &(*this);
}
MyXml::Node::Iter MyXml::Node::AppendSiblingsPtr(Node::Iter newSibling)
{
    //std::cout << this << " " << this->name << " ap s " << newSibling->name << std::endl;
    if (!this->nextSister)
        this->nextSister = newSibling;
    else
    {
        this->nextSister->AppendSiblingsPtr(newSibling);
    }
    return &(*this);
}
MyXml::Node::Iter MyXml::Node::AppendPropertiesPtr(Property* newProperty)
{
    properties.Append(newProperty);
    return this;
}
MyXml::Node& MyXml::Node::AppendChildren(Node& source)
{
    return static_cast<Node&>(*AppendChildrenPtr(new Node(static_cast<Node&&>(source))));
}
MyXml::Node& MyXml::Node::AppendSiblings(Node& source)
{
    return static_cast<Node&>(*AppendSiblingsPtr(new Node(static_cast<Node&&>(source))));
}
MyXml::Node& MyXml::Node::AppendProperties(Property& source)
{
    return static_cast<Node&>(*AppendPropertiesPtr(new Property(static_cast<Property&&>(source))));
}
MyXml::Node::Iter MyXml::Node::FirstChild() const
{
    return firstChild;
}
MyXml::Node::Iter MyXml::Node::NextSibling() const
{
    return nextSister;
}
const MyXml::Char* MyXml::Node::Name() const
{
    return const_cast<const Char*>(name);
}
const MyXml::Char* MyXml::Node::Value() const
{
    return const_cast<const Char*>(text);
}
const MyXml::PropertyChain& MyXml::Node::Properties() const
{
    return const_cast<const PropertyChain&>(properties);
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
MyXml::Node::Iter MyXml::Node::operator->()
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
MyXml::Element::Element(Element&& source):
    Node(std::move(static_cast<Node&>(source)))
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
MyXml::Comment::Comment(Comment && source):
    Element(static_cast<Element&&>(source))
{}
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

MyXml::Comment::operator Node && ()
{
    return dynamic_cast<Node&&>(*this);
}

MyXml::Declaration::Declaration():
    Declaration(static_cast<PropertyChain&>(PropertyChain(new Property("version", 1.0), new Property("encoding", "ascii"), new Property("standalone", "yes"))))
{}
MyXml::Declaration::Declaration(Declaration && source):
    Element(static_cast<Element&&>(source))
{}
MyXml::Declaration::Declaration(PropertyChain& declarationPropeties):
    Element("xml", static_cast<PropertyChain&>(declarationPropeties))
{}
MyXml::Char* MyXml::Declaration::ToCharStr() const
{
    Char buff[buffsizeSmall] = "";
    Char* ptr = properties.ToCharStr();
    sprintf(buff, "<?xml %s ?>", ptr);
    delete[] ptr;

    return AllocateCopyOf(buff);
}
