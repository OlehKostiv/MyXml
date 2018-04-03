#include "Logger.h"
#include "myCstrFunctional.h"
#include "PropertyChain.h"

#include <cstring>
#include <cassert>

#ifdef _DEBUG
static Logger Log(std::cout);
#else 
#include <fstream>
static char* filePath = MyXml::AllocateACatOf((char*)__FILE__, ".txt");
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
MyXml::PropertyChain & MyXml::PropertyChain::Append(Property&& source)
{
    return Append(new Property(static_cast<Property&&>(source)));
}
MyXml::PropertyChain::PropertyChain(Property *p):
    PropertyChain()
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
MyXml::PropertyChain::PropertyChain():
    firstProperty(nullptr)
{}
MyXml::PropertyChain::PropertyChain(Property&& rr):
    PropertyChain(new Property(static_cast<Property&&>(rr)))
{}
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
MyXml::Property::Property(Property&& source)
{
    name = source.name;
    text = source.text;
    next = source.next;

    source.name = nullptr;
    source.text = nullptr;
    source.next = nullptr;
}
MyXml::Property::~Property()
{
    if (name)
        delete[] name;
    if (text)
        delete[] text;
    Log.InRed("~Property();");
}

MyXml::Char* MyXml::Property::ToCharStr() const
{
    Char buff[buffsizeSmall];

    std::sprintf(buff, "%s=\"%s\"", name, text);

    return AllocateCopyOf(buff);
}
