#ifndef _DEBUG
#include <iostream>

int main()
{
	return 0;
}
#endif 

#ifdef _DEBUG
#include <iostream>


#include "myCstrFunctional.h"

using namespace MyXml;

#include "PropertyChain.h"
void TestAllocateCopyOf()
{
    Char buff[128];
    std::cin.getline(buff, sizeof(buff));
    Char* copyPtr = AllocateCopyOf(buff);
    std::cout << copyPtr << std::endl;
    std::cout << std::strlen(copyPtr);
    delete[] copyPtr;
}
void TestIntToPChar()
{
    Int number;
    std::cin >> number;
    Char* ptr = IntToPChar(number);
    std::cout << ptr;
    delete[] ptr; 
}
void TestAllocateACatOf()
{
    Char buff1[128];
    Char buff2[128];

    std::cin.getline(buff1, 128);
    std::cin.getline(buff2, 128);

    Char* ptr = AllocateACatOf(buff1, buff2);
    std::cout << ptr;
    delete[] ptr;
}
void TestDoubleToPchar()
{
    Double number;
    std::cin >> number;
    Char* ptr = DoubleToPChar(number);
    std::cout << ptr;
    delete[] ptr;
}
void TestPropertyToPchar()
{
    Char* ptr;

    Property pp1("name", "PoopyAmen!");
    ptr = pp1.ToPChar();
    std::cout << ptr << std::endl;
    delete[] ptr;

    Property pp2("age", 24);
    ptr = pp2.ToPChar();
    std::cout << ptr << std::endl;
    delete[] ptr;

    Property pp3("weight", 79.5);
    ptr = pp3.ToPChar();
    std::cout << ptr << std::endl;
    delete[] ptr;

    Property* p = new Property("hint", "kek");
    ptr = p->ToPChar();
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

    Char* pc1_repr = pc1.ToPChar();
    Char* pc2_repr = pc2.ToPChar();

    std::cout << pc1_repr << std::endl;
    std::cout << pc2_repr << std::endl;

    delete[] pc1_repr;
    delete[] pc2_repr;
}

int main()
{
    //TestAllocateCopyOf();
    //TestIntToPChar();
    //TestAllocateACatOf();
    //TestDoubleToPchar();
    //TestPropertyToPchar();
    //TestPropertyChain();

    return system("pause");
}

#endif // _DEBUG
