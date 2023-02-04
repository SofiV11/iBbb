#include "customer.h"

customer::customer() : m_type(customerType::unknown) {}

customer::customer(const std::string& login, const std::string& password, const customerType& type)
	: m_login(login), m_password(password), m_type(type) {}

std::string customer::get_login() const
{
	return m_login;
}

std::string customer::get_password() const
{
	return m_password;
}

customerType customer::get_type() const
{
	return m_type;
}

void customer::set_login(const std::string& login)
{
	m_login = login;
}

void customer::set_password(const std::string& password)
{
	m_password = password;
}

void customer::set_type(const customerType& type)
{
	m_type = type;
}

std::ostream& operator<<(std::ostream& out, const customer& c) ////!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	out << c.m_login << ' ' << c.m_password << ' ';

	if (c.m_type == customerType::admin)
	{
		out << "admin";
	}
	else if (c.m_type == customerType::user)
	{
		out << "user";
	}
	else
	{
		out << "unknown";
	}

	return out;
}

std::istream& operator>>(std::istream& in, customer& c)
{
	in >> c.m_login >> c.m_password;

	std::string type;

	in >> type;

	if (type == "admin")
	{
		c.m_type = customerType::admin;
	}
	else if (type == "user")
	{
		c.m_type = customerType::user;
	}
	else
	{
		c.m_type = customerType::unknown;
	}

	return in;
}