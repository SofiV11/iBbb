#pragma once

#include <string>
#include <iostream>

using namespace std;

enum customerType
{
	user, admin, unknown
};

// пользователь
class customer
{
public:
	customer();
	customer(const string& login, const string& password, const customerType& type);

	string get_login() const;
	string get_password() const;
	customerType get_type() const;

	void set_login(const string& login);
	void set_password(const string& password);
	void set_type(const customerType& type);
private:
	string m_login;
	string m_password;
	customerType m_type;

	friend ostream& operator<<(ostream& out, const customer& c);
	friend istream& operator>>(istream& out, customer& c);
};