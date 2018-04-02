#pragma once

#ifdef _DEBUG
#include <Windows.h>
#include <iostream>
#else
#include <fstream>
#endif // _DEBUG

class Logger
{
public:
    using Ostream =
        #ifdef _DEBUG
            std::ostream;
        #else
            std::ofstream;
        #endif
	using Char = char;

	Logger(Ostream& outputTarget) : 
		target(outputTarget) 
    {};

	enum class Color{red = 12, white = 15};

	Logger& InRed(const Char* text, const Char* endl = "\n")
	{
		return InColor(Color::red, text, endl);		
	}
	Logger& InWhite(const Char* text, const Char* endl = "\n")
	{
		return InColor(Color::white, text, endl);
	}
protected:
	Logger& InColor(const Color clr, const Char* text, const Char* endl)
	{
        #ifdef _DEBUG
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)clr);
            target << text << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Color::white);
        #else
            target << text << endl;
        #endif
        return *this;
	}
	Ostream& target;	
};