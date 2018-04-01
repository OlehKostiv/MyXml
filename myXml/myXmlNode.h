#pragma once
#include "Typedef.h"
#include "PropertyChain.h"
namespace MyXml
{
	class Node
	{
	public:
        using Iter = Node * ;

		Node(const Char* nodeName, const Char* nodeText);
        Node(const Char* nodeName, const Char* nodeText, PropertyChain& nodeProperties);
		virtual ~Node();

        Node& AppendChild(Node*);
        Node& AppendSibling(Node*);
        
        Char* ToPchar() const;
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

    };
}