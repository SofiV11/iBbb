#include "AutoF.h"
#include "ALLF.h"

Authenticator::Authenticator(const string& addressDB) : m_addressDB(addressDB)
{
	ifstream ifs(addressDB);

	customer tmp;

	while (!ifs.eof())
	{
		ifs >> tmp;
		m_usersDB.push_back(tmp);
	}
}

customer Authenticator::sign_in(const string& login, const string& password)
{
	size_t size = m_usersDB.size();

	for (size_t i = 0; i < size; i++)
	{
		if (m_usersDB[i].get_login() == login && m_usersDB[i].get_password() == password)
		{
			return m_usersDB[i];
		}
	}

	return customer();
}

void Authenticator::add_customer(const customer& c)
{
	m_usersDB.push_back(c);
}

void Authenticator::delete_customer(const customer& c)
{
	int size = m_usersDB.size();

	for (int i = 0; i < size; ++i)
	{
		if (m_usersDB[i].get_login() == c.get_login() && m_usersDB[i].get_password() == c.get_password())
		{
			m_usersDB.erase(m_usersDB.begin() + i); /////!!!!!!!!!!!!!
			return;
		}
	}
}

bool Authenticator::find_log(const string& login)
{
	size_t size = m_usersDB.size();

	for (size_t i = 0; i < size; i++)
	{
		if (m_usersDB[i].get_login() == login)
		{
			return true;
		}
	}

	return false;
}

vector<customer> Authenticator::usersDB()
{
	return m_usersDB;
}

Authenticator::~Authenticator() /////////!!!!!!!!!!!!!!!
{
	int size = m_usersDB.size();

	ofstream ofs(m_addressDB);

	for (int i = 0; i < size; i++)
	{
		ofs << m_usersDB[i];

		if (i != size - 1)
		{
			ofs << '\n';
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////

program::program(const Authenticator authenticator) : m_authenticator(authenticator) {}

void program::sign_in(const string& login, const string& password)
{
	m_currentUser = m_authenticator.sign_in(login, password);
}

void program::run()
{
	int command;
	if (m_currentUser.get_type() == customerType::unknown)
	{
		cout << "�������� ����� ��� ������!\n";
	}
	else
	{
		do
		{
			menu();
			cout << "> ";

			cin >> command;

			if (m_currentUser.get_type() == customerType::admin)
			{
				rangeError(command, 1, 10);
			}
			else
			{
				rangeErrorWithAddValue(command, 10, 1, 5);
			}

			switch (command)
			{
			case 1:
			{
				cout << "���� 1" << endl;
				Reshuffle();
				break;
			}
			case 2:
			{
				cout << "���� 2" << endl;
				MatrixShifr();
				break;
			}
			case 3:
			{
				cout << "���� 3"<<endl;
				MatrixVectorShifr();
				break;
			}
			case 4:
			{
				cout << "���� 4" << endl;
				CodeMatrixAndPref();
				break;
			}
			case 5:
			{
				cout << "���� 5" << endl;
				RSA();
				break;
			}
			case 6:
			{
				cout << "���� 6" << endl;
				BmpCode();
				break;
			}
			}

			// 6) �������� ������������
			if (m_currentUser.get_type() == customerType::admin && command == 7)
			{
				customer tmp;
				string login, password, type;

				cout << "login: ";
				cin >> login;
				cout << "password: ";
				cin >> password;
				cout << "type: ";
				cin >> type;

				ofstream file;
				file.open("data.txt");
				if(file.is_open())
				file << login << " " << password << " " << type;

				tmp.set_login(login);
				tmp.set_password(password);

				if (type == "admin")
				{
					tmp.set_type(customerType::admin);
				}
				else if (type == "user")
				{
					tmp.set_type(customerType::user);
				}

				if (m_authenticator.find_log(login))
				{
					cout << "������������ � ����� ������� ��� ����������!\n";
				}
				else
				{
					m_authenticator.add_customer(tmp);
				}
			}
			// 7) ������� ������������
			if (m_currentUser.get_type() == customerType::admin && command == 8)
			{
				customer tmp;
				string login, password;

				cout << "login: ";
				cin >> login;
				cout << "password: ";
				cin >> password;

				tmp.set_login(login);
				tmp.set_password(password);

				m_authenticator.delete_customer(tmp);
			}
			// 8) �������� ���� �������������
			if (m_currentUser.get_type() == customerType::admin && command == 9)
			{
				vector<customer> db = m_authenticator.usersDB();

				int DBsize = db.size();

				cout << "log pas type\n";
				for (int i = 0; i < DBsize; i++)
				{
					cout << db[i] << '\n';
				}
			}

		} while (command != 10);
	}
}

void program::menu() ////////////////!!!!!!!!!!!!��������
{
	cout << "1) ���������� �������������\n"
		<< "2) ��������� ����������\n"
		<< "3) ��������-��������� ����������\n"
		<< "4) ������������ ������� ��� ���������� ����\n"
		<< "5) ������ ���������� RSA\n"
	    << "6) ����������� ������� ������ �� �����������\n";

	if (m_currentUser.get_type() == customerType::admin)
	{
		cout << "7) �������� ������������\n"
			<< "8) ������� ������������\n"
			<< "9) �������� ���� �������������\n";
	}

	cout << "10) �����\n";
}

void rangeError(int& value, const int& leftBorder, const int& rightBorder)
{
	while (value < leftBorder || value > rightBorder)
	{
		std::cout << "�������� ��������� ���������� ������� �� ���������� �������! ���������� ��� ���!\n> ";
		std::cin >> value;
	}
}

void rangeErrorWithAddValue(int& value, const int& addValue, const int& leftBorder, const int& rightBorder)
{
	while ((value < leftBorder || value > rightBorder) && value != addValue)
	{
		std::cout << "�������� ��������� ���������� ������� �� ���������� �������! ���������� ��� ���!\n> ";
		std::cin >> value;
	}
}