#pragma once

#include <fstream>
#include <vector>

#include "customer.h"

using namespace std;

class Authenticator
{
public:
	Authenticator(const string& addressDB);
	customer sign_in(const string& login, const string& password);
	void add_customer(const customer& c);
	void delete_customer(const customer& c);
	bool find_log(const string& login);

	vector<customer> usersDB();

	~Authenticator();
private:
	vector<customer> m_usersDB;
	string m_addressDB;
};

//////////////////////////////////////////////////////////////

class program
{
public:
	program(const Authenticator authenticator);

	void sign_in(const string& login, const string& password);
	void run();
private:
	void menu();

	Authenticator m_authenticator;
	customer m_currentUser;
};

void rangeError(int& value, const int& leftBorder, const int& rightBorder);

void rangeErrorWithAddValue(int& value, const int& addValue, const int& leftBorder, const int& rightBorder);