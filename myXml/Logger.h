#pragma once
#include <iostream>

class Logger
{
public:
	using Ostream = std::ostream;
	using Char = char;
	using Void = void;

	Logger(Ostream& outputTarget) : 
		target(outputTarget) {};

	enum class Color{red, white};

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
		// change color;
		target << text << endl;
		// change color back;
        return *this;
	}
	Ostream& target;	
};