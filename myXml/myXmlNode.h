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
        using SuperConstIter = const Node * const;

        Node(const Char* nodeName);
        Node(const Char* nodeName, PropertyChain& nodeProperties);
		Node(const Char* nodeName, const Char* nodeText);
        Node(const Char* nodeName, const Char* nodeText, PropertyChain& nodeProperties);
        Node(Node&& source);
		virtual ~Node();

        Node::Iter AppendChildrenPtr(Node::Iter);
        Node::Iter AppendSiblingsPtr(Node::Iter);
        Node::Iter AppendPropertiesPtr(Property*);

        Node& AppendChildren(Node&);
        Node& AppendSiblings(Node&);
        Node& AppendProperties(Property&);

        Node::Iter           FirstChild()   const;
        Node::Iter           NextSibling()  const;
        const Char*          Name()         const;
        const Char*          Value()        const;
        const PropertyChain& Properties()   const;

        virtual Char* ToCharStr() const;

        Node::Iter operator->();

        template<class...Args>
        Node::Iter AppendChildrenPtr(Node::Iter p, Args...args)
        {
            return AppendChildrenPtr(p)->AppendChildrenPtr(args...);
        }
        template<class...Args>
        Node::Iter AppendSiblingsPtr(Node::Iter p, Args...args)
        {
            return AppendSiblingsPtr(p)->AppendSiblingsPtr(args...);
        }
        template<class...Args>
        Node::Iter AppendPropertiesPtr(Property* p, Args...args)
        {
            return AppendPropertiesPtr(p)->AppendPropertiesPtr(args...);
        }
        template<class...Args>
        Node& AppendChildren(Node&e, Args&...args)
        {
            return AppendChildren(static_cast<Node&&>(e)).AppendChildren(static_cast<Args&&>(args)...);
        }
        template<class...Args>
        Node& AppendSiblings(Node&e, Args&...args)
        {
            return AppendSiblings(static_cast<Node&&>(e)).AppendSiblings(static_cast<Args&&>(args)...);
        }
        template<class...Args>
        Node& AppendProperties(Property& p, Args&...args)
        {
            return AppendProperties(static_cast<Property&&>(p)).AppendProperties(static_cast<Args&&>(args)...);
        }        
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
        using Iter = Element*;

        Element(const Char* elementName);
        Element(const Char* elementName, PropertyChain& elementProperties);
        Element(const Char* elementName, const Char* elementText);
        Element(const Char* elementName, const Char* elementText, PropertyChain& elementProperties);
        Element(Element&&);
       ~Element();
    protected:
        Element() = default;
    };

    class Comment:
        public Element
    {
    public:
        using Iter = Comment*;
        Comment(const Char* commentText);
        Comment(Comment&&);
       ~Comment();
        virtual Char* ToCharStr() const override;
        operator Node && ();
    private:
        using Element::AppendChildren;
        using Element::AppendProperties;
        using Element::FirstChild;
    };

    class Declaration :
        public Element
    {
    public:
        using Iter = Declaration*;
        Declaration();
        Declaration(Declaration&&);
        Declaration(PropertyChain& declarationPropeties);
        virtual Char* ToCharStr() const override;
    private:
        using Element::AppendChildren;
        using Element::AppendSiblings;
    };
}