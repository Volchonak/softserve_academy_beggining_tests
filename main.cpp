// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include "AnyType.h"

using std::cout;


int main()
{
	AnyType any_type = 1;
	any_type = 1.7;
	AnyType second_any_type = 'c';
	any_type.Swap(second_any_type);

	try
	{
		std::string type = any_type.get_type();
		if (type == std::string(typeid(bool).name()))
		{
			cout<<any_type.toBool();
		}
		else if(type == std::string(typeid(double).name()))
		{
			cout << any_type.toDouble();
		}
		else if (type == std::string(typeid(char).name()))
		{
			cout << any_type.toChar();
		}
		cout<<any_type.toLongLong();
	}
	catch (const std::bad_variant_access& excep)
	{
		cout << excep.what();
	}
	return 0;
}