#pragma once
#include "Typedef.h"
#include "PropertyChain.h"
namespace MyXml
{
	class Node
	{
	public:
        using Iter = Node * ;
        using ConstIter = const Node::Iter;
        using SuperConstIter = const Node const * const;

        Node(const Char* nodeName);
        Node(const Char* nodeName, PropertyChain& nodeProperties);
		Node(const Char* nodeName, const Char* nodeText);
        Node(const Char* nodeName, const Char* nodeText, PropertyChain& nodeProperties);
		virtual ~Node();

        Node::Iter AppendChild(Node::Iter);
        Node::Iter AppendSibling(Node::Iter);
        Node::Iter AppendProperty(Property*);

        template<class...Args>
        Node::Iter AppendChild(Node::Iter p, Args...args)
        {
            return AppendChild(p)->AppendChild(args...);
        }
        template<class...Args>
        Node::Iter AppendSibling(Node::Iter p, Args...args)
        {
            return AppendSibling(p)->AppendSibling(args...);
        }
        template<class...Args>
        Node::Iter AppendProperty(Property* p, Args...args)
        {
            return AppendProperty(p)->AppendProperty(args...);
        }

        Node::Iter FirstChild()   const;
        Node::Iter NextSibling()  const;

        virtual Char* ToCharStr() const;

        Node::Iter operator->();
	protected:
		Node();
		Node::Iter firstChild;
		Node::Iter nextSister;

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
    private:
        using Element::AppendChild;
        using Element::AppendProperty;
        using Element::FirstChild;
    };
}