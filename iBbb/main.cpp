#include <iostream>
#include <cmath>
#include <string>
#include <windows.h>
#include <cstdio>
#include <typeinfo>
#include "ALLF.h"
#include "AutoF.h"


using namespace std;

void menu()
{
	cout << "1) Вход\n2) Выход\n";
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	string command;

	Authenticator A("data.txt");
	program P(A);

	do
	{
		menu();
		cout << "> ";

		cin >> command;

		//rangeError(command, 1, 2);
		while ((command != "1" && command != "2")) {
			cout << "out of range \n";
			menu();
			cout << "> ";
			cin >> command;
			break;
		};

		//switch (command)
		//{
		//case "1":
		if (command == "1")
		{
			string login, password;

			cout << "login: ";
			cin >> login;
			cout << "password: ";
			cin >> password;

			P.sign_in(login, password);
			P.run();

			//break;
		};

	} while (command != "2");
}
