#include "Logger.h"
#include "myCstrFunctional.h"
#include "PropertyChain.h"

#include <cstring>
#include <cassert>

#ifdef _DEBUG
static Logger Log(std::cout);
#else 
#include <fstream>
static char* fp = __FILE__;
static char* filePath = MyXml::AllocateACatOf(fp, ".txt");
static std::ofstream logFile(filePath, std::ios::out);
static Logger Log(logFile);
static int freeFP = []() { delete[] filePath; return 0;}();
#endif

MyXml::PropertyChain& MyXml::PropertyChain::Append(Property* prp)
{
    assert(prp != nullptr);

    prp->next = this->firstProperty;
    this->firstProperty = prp;

    return *this;
}
MyXml::PropertyChain::PropertyChain(Property *p)
{
    Append(p);
}
MyXml::PropertyChain::~PropertyChain()
{
    while (firstProperty)
    {
        Property::Iter killer = firstProperty;
        firstProperty = firstProperty->next;
        delete killer;
    }
}
MyXml::PropertyChain::PropertyChain(PropertyChain&& source)
{
    firstProperty = source.firstProperty;
    source.firstProperty = nullptr;
}
MyXml::PropertyChain& MyXml::PropertyChain::operator=(PropertyChain && source)
{
    firstProperty = source.firstProperty;
    source.firstProperty = nullptr;
    return *this;
}

MyXml::Char* MyXml::PropertyChain::ToCharStr() const
{
    Char buff[buffsizeHuge] = "";
    for (Property::Iter it = firstProperty; it; it = it->next)
    {
        Char* ptr = it->ToCharStr();
        std::strcat(buff, ptr);
        if (it->next)
            std::strcat(buff, " ");
    }
    return AllocateCopyOf(buff);
}

MyXml::Bool MyXml::PropertyChain::IsEmpty() const
{
    return firstProperty == nullptr;
}
const MyXml::Property::Iter MyXml::PropertyChain::FirstProperty() const
{
    return firstProperty;
}
MyXml::Property::Property(const Char* propName, const Char* propValue)
{
    name = AllocateCopyOf(propName);
    text = AllocateCopyOf(propValue);
}
MyXml::Property::Property(const Char* propName, const Double propValue)
{
    name = AllocateCopyOf(propName);
    text = DoubleToCharStr(propValue);
}
MyXml::Property::Property(const Char* propName, Int propValue)
{
    name = AllocateCopyOf(propName);
    text = IntToCharStr(propValue);
}
MyXml::Property::~Property()
{
    //Log.InRed("~Property();: ", " ").InRed(name, ", ").InRed(text);
    delete[] name;
    delete[] text;
    Log.InRed("~Property();");
}

MyXml::Char* MyXml::Property::ToCharStr() const
{
    Char buff[buffsizeSmall];

    std::sprintf(buff, "%s=\"%s\"", name, text);

    return AllocateCopyOf(buff);
}
