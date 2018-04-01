#include "myCstrFunctional.h"
#include <cstring>
#include <cmath>
#include <cassert>

MyXml::Char* MyXml::AllocateCopyOf(const Char* source)
{
    assert(source != nullptr);

    Char* result = nullptr;
    if (source)
    {
        size_t size = std::strlen(source) + 1;
        if (result = new Char[size])
        {
            std::strcpy(result, source);
        }
    }
    return result;
}

MyXml::Char* MyXml::AllocateACatOf(const Char* next, const Char* second)
{
    assert(next != nullptr);
    assert(second != nullptr);

    size_t lenFirst  = std::strlen(next);
    size_t lenSecond = std::strlen(second);
    size_t sizeResult = lenFirst + lenSecond + 1;
    
    Char* result = new Char[sizeResult];
    std::strcpy(result, next);
    std::strcat(result, second);

    return result;
}

MyXml::Char* MyXml::IntToPChar(Int value)
{
    Char* result;
    if (value)
    {
        Bool isNegative = value < 0 ? true : false;
        value = std::abs(value);

        size_t size = 12; // str(int_max) = sign + 10 
        Char buff[12];

        Char* p = &(buff[11] = 0) - 1;

        while (value)
        {
            Int tenthOf = value / 10;
            Int digit = value - tenthOf * 10;
            *p = '0' + digit;
            --p;
            value = tenthOf;
        }
        if (isNegative)
            *p = '-';
        else
            ++p;

        result = AllocateCopyOf(p);
    }
    else
    {
        Char buff[] = "0";
        result = AllocateCopyOf(buff);
    }
    return result;
}

MyXml::Char* MyXml::DoubleToPChar(Double value)
{
    Int whole = (Int)value;
    Int part;
    {
        Double dPart = value - whole + 1; // +1 for '.'
        while (std::abs(dPart - (Int)dPart) > 0.00001)
            dPart *= 10;
        part = dPart;
    }
    Char* w = IntToPChar(whole);
    Char* p = IntToPChar(part);
    p[0] = '.';

    Char* result = AllocateACatOf(w, p);

    delete[]w;
    delete[]p;

    return result;    
}
