#pragma once

#include "Logger.h"
#include "Typedef.h"

namespace MyXml
{
    Char* AllocateCopyOf(const Char* source);
    Char* AllocateACatOf(const Char* first, const Char* second);
    Char* IntToCharStr(Int value);
    Char* DoubleToCharStr(Double value);
}
