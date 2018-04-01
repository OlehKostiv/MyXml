#pragma once
#include "Typedef.h"

namespace MyXml
{
    class Property
    {
    public:
        using Iter = Property * ;

        Property(const Char* propName, const Char* propValue);
        Property(const Char* propName, const Double propValue);
        Property(const Char* propName, const Int propValue);
        ~Property();

        Char* ToPChar() const;

        Char* name = nullptr;
        Char* text = nullptr;
        Iter  next = nullptr;
    };

	class PropertyChain
	{
	public:
        PropertyChain & Append(Property*);
        template <class...Args>
        PropertyChain& Append(Property* p, Args...args) // appends backwards
        {
            return Append(p).Append(args...);
        }

       ~PropertyChain();
        PropertyChain() = default;
        PropertyChain(Property*);
        template <class...Args>
        PropertyChain(Property* p, Args...args)
        {            
            Append(p, args...);
        }

        PropertyChain(PropertyChain&& source);
        PropertyChain& operator = (PropertyChain&& source);

        Char* ToPChar() const;

       Bool IsEmpty() const;
       const Property::Iter FirstProperty() const;
	protected:
		Property::Iter firstProperty = nullptr;
	};
}