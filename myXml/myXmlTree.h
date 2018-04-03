#pragma once
#include "Typedef.h"
#include "myXmlNode.h"


namespace MyXml
{
    class Tree:
        public Element
    {
    public:
        using Iter = Tree*;
        Tree();
        Tree(const Char* rootName);
        Tree(Tree&&);
       ~Tree();
        Char* AsCharStr() const;
    protected:
        using Element::ToCharStr;
        static Char* RecursiveSelfCharStrCast(Node::SuperConstIter root);
        static void RecursiveSelfDestruction(Node::ConstIter root);
        friend class Document;
    };
}