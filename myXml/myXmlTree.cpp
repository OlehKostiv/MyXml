#include "myXmlTree.h"
#include "myCstrFunctional.h"

MyXml::Tree::Tree()
{}
MyXml::Tree::Tree(const Char * rootName):
    Element(rootName)
{}
MyXml::Tree::Tree(Tree && source):
    Element(static_cast<Element&&>(source))
{}
MyXml::Tree::~Tree()
{
    RecursiveSelfDestruction(this);
}

MyXml::Char* MyXml::Tree::AsCharStr() const
{
    return RecursiveSelfCharStrCast(this);
}

void MyXml::Tree::RecursiveSelfDestruction(Node::ConstIter root)
{
    Node::Iter kinSlayer;
    {
        kinSlayer = root->NextSibling();
        if (kinSlayer)
        {
            RecursiveSelfDestruction(kinSlayer);
            delete kinSlayer;
        }

        kinSlayer = root->FirstChild();
        if (kinSlayer)
        {
            RecursiveSelfDestruction(kinSlayer);
            delete kinSlayer;
        }
    }
}
MyXml::Char* MyXml::Tree::RecursiveSelfCharStrCast(Node::SuperConstIter root)
{
    Char buff[buffsizeHuge];

    Char* rootFormat = root->ToCharStr();
    sprintf(buff, "%s", rootFormat);

    Node::ConstIter childPrinter = root->FirstChild();
    {
        if (childPrinter)
        {
            Char* childFormat = RecursiveSelfCharStrCast(childPrinter);
            sprintf(buff, rootFormat, childFormat);
            delete[] childFormat;
        }
    }
    delete[] rootFormat;

    Node::ConstIter siblingPrinter = root->NextSibling();
    {
        if (siblingPrinter)
        {
            Char* siblingFormat = RecursiveSelfCharStrCast(siblingPrinter);
            strcat(buff, siblingFormat);
            delete[] siblingFormat;
        }
    }

    return AllocateCopyOf(buff);
}