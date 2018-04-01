#pragma once
#include "Typedef.h"
#include "PropertyChain.h"
namespace MyXml
{
	class Node
	{
	public:
        using Iter = Node * ;

        Node(const Char* nodeName);
        Node(const Char* nodeName, PropertyChain& nodeProperties);
		Node(const Char* nodeName, const Char* nodeText);
        Node(const Char* nodeName, const Char* nodeText, PropertyChain& nodeProperties);
		virtual ~Node();

        Node& AppendChild(Node*);
        Node& AppendSibling(Node*);
        
        virtual Char* ToPChar() const;
	protected:
		Node();
		PNode firstChild;
		PNode nextSister;

		Char* name;
		Char* text;

		PropertyChain properties;
	};

    class Element:
        public Node
    {
    public:
        Element(const Char* elementName, const Char* elementText);
        Element(const Char* elementName, const Char* elementText, PropertyChain& elementProperties);
       ~Element();

    };

    class Comment:
        public Node
    {
    public:
        Comment(const Char* commentText);
       ~Comment();
    };
}