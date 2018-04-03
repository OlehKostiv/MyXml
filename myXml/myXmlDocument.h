#pragma once
#include "Typedef.h"
#include "PropertyChain.h"
#include "myXmlTree.h"

namespace MyXml
{
    class Document
    {
    public:
        Document();
        Document(Char* docName, Tree&& docRoot, Declaration&& xmlDeclaration);
       ~Document();
        
        class Iterator
        {
        public:
            Iterator();
            Iterator(Element::Iter nodePtr);
            Iterator(const Iterator&) = default;

            Element::Iter   operator->()    const;
            Element&        operator*()     const;
            Iterator&    operator++();
            Iterator     operator++(int);
            Bool         operator==(const Iterator&) const;
            Bool         operator!=(const Iterator&) const;
        protected:
            Element::Iter ptr;
        };
        typedef const Iterator ConstIterator;

        Element& Root() const;

        Char* ToCharStr() const;

    protected:
        Char* name;
        Declaration::Iter declaration;
        Tree::Iter root;
    };

}