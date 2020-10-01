#include <iostream>
#include "AnyType.h"

using std::cout;


int main()
{
	AnyType any_type = 1;
	any_type = 1.7;
	AnyType second_any_type = 'c';
	any_type.Swap(second_any_type);

	std::string type = any_type.get_type();
	if (type == std::string(typeid(bool).name()))
	{
		cout<<any_type.get_bool();
	}
	else if(type == std::string(typeid(double).name()))
	{
		cout << any_type.get_double();
	}
	else if (type == std::string(typeid(char).name()))
	{
		cout << any_type.get_char();
	}
	try
	{
		cout<<any_type.get_long_long();
	}
	catch (const std::bad_variant_access excep)
	{
		cout << excep.what();
	}
	return 0;
}