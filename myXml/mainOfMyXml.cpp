//#ifndef _DEBUG
//#include <iostream>
//
//int main()
//{
//	return 0;
//}
//#endif 
//
//#ifdef _DEBUG
#include <iostream>
#include <fstream>
#include <cstring>

#include "myCstrFunctional.h"

using namespace MyXml;
#include "PropertyChain.h"
#include "myXmlNode.h"
#include "myXmlTree.h"

void TestAllocateCopyOf()
{
    Char buff[buffsizeSmall];
    std::cin.getline(buff, sizeof(buff));
    Char* copyPtr = AllocateCopyOf(buff);
    std::cout << copyPtr << std::endl;
    std::cout << std::strlen(copyPtr);
    delete[] copyPtr;
}
void TestIntToCharStr()
{
    Int number;
    std::cin >> number;
    Char* ptr = IntToCharStr(number);
    std::cout << ptr;
    delete[] ptr; 
}
void TestAllocateACatOf()
{
    Char buff1[buffsizeSmall];
    Char buff2[buffsizeSmall];

    std::cin.getline(buff1, buffsizeSmall);
    std::cin.getline(buff2, buffsizeSmall);

    Char* ptr = AllocateACatOf(buff1, buff2);
    std::cout << ptr;
    delete[] ptr;
}
void TestDoubleToPchar()
{
    Double number;
    std::cin >> number;
    Char* ptr = DoubleToCharStr(number);
    std::cout << ptr;
    delete[] ptr;
}
void TestPropertyToPchar()
{
    Char* ptr;

    Property pp1("name", "PoopyAmen!");
    ptr = pp1.ToCharStr();
    std::cout << ptr << std::endl;
    delete[] ptr;

    Property pp2("age", 24);
    ptr = pp2.ToCharStr();
    std::cout << ptr << std::endl;
    delete[] ptr;

    Property pp3("weight", 79.5);
    ptr = pp3.ToCharStr();
    std::cout << ptr << std::endl;
    delete[] ptr;

    Property* p = new Property("hint", "kek");
    ptr = p->ToCharStr();
    std::cout << ptr << std::endl;
    delete[] ptr;
    delete p;
}
void TestPropertyChain()
{
    PropertyChain pc1(new Property("p10", 0));
    pc1.Append(new Property("p11", 0.1)).Append(new Property("p12", 0.2)).Append(new Property("p13", 0.3));

    PropertyChain pc2(new Property("p20", 0));
    pc2.Append(new Property("p21", 1), new Property("p22", 2), new Property("p23", 3));

    Char* pc1_repr = pc1.ToCharStr();
    Char* pc2_repr = pc2.ToCharStr();

    std::cout << pc1_repr << std::endl;
    std::cout << pc2_repr << std::endl;

    delete[] pc1_repr;
    delete[] pc2_repr;
}

void PrintTree(const Node& node)
{
    Char* ptr = node.ToCharStr();
    std::cout << ptr << std::endl;
    delete[] ptr;
    
    Node::Iter child = node.FirstChild();
    if (child)
        PrintTree(*child);
    
    Node::Iter sibling = node.NextSibling();
    if (sibling)
        PrintTree(*sibling);
}

void TestNode()
{
    Tree root("root");

    root->AppendChild(
        new Element("el1", 
                    PropertyChain(new Property("first_name", "Poop"), 
                                  new Property("last_name", "Amen")
                    )
        )
    );
    root->AppendChild(new Element("el2", "this is element 2"));

    Node& rootChild = *(root.FirstChild());

    rootChild->AppendProperty(new Property("taste", "awful")); 
    rootChild->AppendProperty(new Property("color", "black"));

    rootChild->AppendChild(new Comment("this is my comment"), (new Element("element"))->AppendProperty(new Property("elp", 0)));

    rootChild->AppendChild((new Element("e2"))->AppendProperty(new Property("elp", 1), new Property("elp",2)), new Element("e3"));

    root->AppendChild
    (
        (new Element("exp"))
        ->AppendSibling
        (
            (new Element("exp_sibling"))
            ->AppendChild
            (
                new Element("exp_sibling_child1"),
                new Element("exp_Sibling_child2")
            )
            ->AppendSibling
            (
                new Element("exp_sibling_sibling1"),
                new Element("exp_sibling_sibling1")
            )
        )
        ->AppendSibling
        (
            new Element("exp_sibling_2", "exp_sibling_text")
        )
    );

    Comment c("this is comment");
    //c.AppendChild(new Element("asd"));

        //->AppendProperty(new Property("exp_prop", "exp_prop_value"))
        //
        //->AppendChild(
        //    (new Element("exp_chind"))
        //    ->AppendChild(
        //         new Element("exp_chind2")
        //    )
        //    //->AppendProperty(new Property("exp_chilp_prop", 0))
        //    //->AppendChild(new Element("exp_child_child"))
        //)
        //->AppendChild(
        //(new Element("exp_chind2"))
        //->AppendProperty(new Property("exp_chilp_prop", 0))
        //->AppendChild(new Element("exp_child_child"))
    //)

    //root->FirstChild()->AppendSibling(new Element("sib_2"));
    //root->FirstChild()->AppendSibling(new Element("exp_sibling", "exp_sibling_text"));

   // PrintTree(root);
    Char* ptr = root.AsCharStr();
    std::ofstream file("file.xml", std::ios::out);
    file << ptr << std::endl;
    file.close();
    delete[] ptr;
}

int main()
{
    //TestAllocateCopyOf();
    //TestIntToCharStr();
    //TestAllocateACatOf();
    //TestDoubleToPchar();
    //TestPropertyToPchar();
    //TestPropertyChain();
    TestNode();

    return system("pause");
}

//#endif // _DEBUG
