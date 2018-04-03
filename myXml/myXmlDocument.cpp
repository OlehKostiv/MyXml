#include "myXmlDocument.h"
#include "myCstrFunctional.h"
#include <cassert>

MyXml::Document::Document():
    Document("theUgliestDefaultDocNameEver", Tree(), Declaration())
{}
MyXml::Document::Document(Char * docName, Tree&& docRoot, Declaration&& xmlDeclaration):
    name(AllocateCopyOf(docName)),
    root(new Tree(static_cast<Tree&&>(docRoot))),
    declaration(new Declaration(static_cast<Declaration&&>(xmlDeclaration)))
{
}
MyXml::Document::~Document() 
{
    if(name)
        delete[] name;
    if (declaration)
        delete declaration;
    if (root)
    {   
        Tree::RecursiveSelfDestruction(root);
    }
}
MyXml::Element& MyXml::Document::Root() const
{
    return static_cast<Element&>(*root);
}

MyXml::Char* MyXml::Document::ToCharStr() const
{
    Char buff[buffsizeHuge];

    Char* declStr = declaration->ToCharStr();
    Char* rootStr = root->AsCharStr();

    sprintf(buff, "%s\n%s", declStr, rootStr);

    delete[] declStr;
    delete[] rootStr;

    return AllocateCopyOf(buff);
}

MyXml::Document::Iterator::Iterator():
    ptr(nullptr)
{}

MyXml::Document::Iterator::Iterator(Element::Iter nodePtr):
    ptr(nodePtr)
{}

MyXml::Element::Iter MyXml::Document::Iterator::operator->() const
{
    return ptr;
}

MyXml::Element& MyXml::Document::Iterator::operator*() const
{
    assert(ptr != nullptr);
    return static_cast<Element&>(*ptr);
}

MyXml::Document::Iterator& MyXml::Document::Iterator::operator++()
{
    assert(ptr != nullptr);
    assert(ptr->NextSibling() != nullptr);
    {
        ptr = dynamic_cast<Element*>(ptr->NextSibling());
    }
    return *this;
}

MyXml::Document::Iterator MyXml::Document::Iterator::operator++(int)
{
    Iterator copyOf(*this);
    ++*this;
    return copyOf;
}

MyXml::Bool MyXml::Document::Iterator::operator==(const Iterator& other) const
{
    return{ ptr == other.ptr };
}

MyXml::Bool MyXml::Document::Iterator::operator!=(const Iterator& other) const
{
    return{ !(*this == other) };
}
