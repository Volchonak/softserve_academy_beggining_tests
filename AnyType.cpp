#include <variant>
#include <typeinfo>
#include "AnyType.h"



AnyType::AnyType(const AnyType& other) noexcept
{
	m_data = other.m_data;
}
AnyType::AnyType(AnyType&& old) noexcept
{
	m_data = std::move(old.m_data);
}
AnyType::~AnyType() noexcept
{

}
AnyType& AnyType::operator=(const AnyType& other) noexcept
{
	m_data = other.m_data;
	return *this;
}
AnyType& AnyType::operator=(char value) noexcept
{
	m_data = value;
	return *this;
}
AnyType& AnyType::operator=(int value) noexcept
{
	m_data = value;
	return *this;
}
AnyType& AnyType::operator=(long value) noexcept
{
	m_data = value;
	return *this;
}
AnyType& AnyType::operator=(long long value) noexcept
{
	m_data = value;
	return *this;
}
AnyType& AnyType::operator=(double value) noexcept
{
	m_data = value;
	return *this;
}
AnyType& AnyType::operator=(bool value) noexcept
{
	m_data = value;
	return *this;
}
//
//operators +=  -=  *= are not implemented

void AnyType::Swap(AnyType& other) noexcept
{
	variant_fundamental value_for_swap = m_data;
	m_data = other.m_data;
}
const char* AnyType::get_type() const noexcept
{
	auto return_type = std::visit([](auto const& value) {
		return typeid(value).name();
		}, m_data);
	return return_type;
}
char AnyType::get_char()const
{
	if (std::holds_alternative<char>(m_data))
	{
		return std::get<char>(m_data);
	}
	else
	{
		throw std::bad_variant_access();
	}
}
int AnyType::get_int()const
{
	if (std::holds_alternative<int>(m_data))
	{
		return std::get<int>(m_data);
	}
	else
	{
		throw std::bad_variant_access();
	}
}
long AnyType::get_long()const
{
	if (std::holds_alternative<long>(m_data))
	{
		return std::get<long>(m_data);
	}
	else
	{
		throw std::bad_variant_access();
	}
}
long long AnyType::get_long_long()const
{
	if (std::holds_alternative<long long>(m_data))
	{
		return std::get<long long>(m_data);
	}
	else
	{
		throw std::bad_variant_access();
	}
}
double AnyType::get_double()const
{
	if (std::holds_alternative<double>(m_data))
	{
		return std::get<double>(m_data);
	}
	else
	{
		throw std::bad_variant_access();
	}
}
bool AnyType::get_bool()const
{
	if (std::holds_alternative<bool>(m_data))
	{
		return std::get<bool>(m_data);
	}
	else
	{
		throw std::bad_variant_access();
	}
}
void AnyType::set_data(char value)
{
	m_data = value;
}
void AnyType::set_data(int value)
{
	m_data = value;
}
void AnyType::set_data(long value)
{
	m_data = value;
}
void AnyType::set_data(long long value)
{
	m_data = value;
}
void AnyType::set_data(double value)
{
	m_data = value;
}
void AnyType::set_data(bool value)
{
	m_data = value;
}