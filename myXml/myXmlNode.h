#pragma once
#include "Typedef.h"
#include "PropertyChain.h"
namespace MyXml
{
	class Node
	{
	public:
        using Iter = Node * ;
        using ConstIter = const Node*;
        using SuperConstIter = const Node const * const;

        Node(const Char* nodeName);
        Node(const Char* nodeName, PropertyChain& nodeProperties);
		Node(const Char* nodeName, const Char* nodeText);
        Node(const Char* nodeName, const Char* nodeText, PropertyChain& nodeProperties);
        //Node(Node&);
		virtual ~Node();

        Node* AppendChild(Node*);
        Node* AppendSibling(Node*);
        Node* AppendProperty(Property*);

        template<class...Args>
        Node* AppendChild(Node* p, Args...args)
        {
            return AppendChild(p)->AppendChild(args...);
        }
        template<class...Args>
        Node* AppendSibling(Node* p, Args...args)
        {
            return AppendSibling(p)->AppendSibling(args...);
        }
        template<class...Args>
        Node* AppendProperty(Property* p, Args...args)
        {
            return AppendProperty(p)->AppendProperty(args...);
        }

        Node* FirstChild() const;
        Node* NextSibling() const;

        virtual Char* ToCharStr() const;

        Node* operator->();
       /* void* operator new(size_t size) {
            return ::new Node();
        }*/
	protected:
		Node();
		Node* firstChild;
		Node* nextSister;

		Char* name;
		Char* text;

		PropertyChain properties;
	};

    class Element:
        public Node
    {
    public:
        Element(const Char* elementName);
        Element(const Char* elementName, PropertyChain& elementProperties);
        Element(const Char* elementName, const Char* elementText);
        Element(const Char* elementName, const Char* elementText, PropertyChain& elementProperties);
       ~Element();
    protected:
        Element() = default;
    };

    class Comment:
        public Element
    {
    public:
        Comment(const Char* commentText);
       ~Comment();
       virtual Char* ToCharStr() const override;
    };
}