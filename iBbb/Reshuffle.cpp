#define _CRT_SECURE_NO_WARNINGS
#include "AllF.h"


void Reshuffle()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i = 0, key = 0, flage = 0, sizeB;
	string message, str = "*";
	cout << "������� ���������:" << endl;
	//getline(cin, message);
	cin >> message;
	cout << "������ ���������: " << message.size() << endl;


	char* A = new char[message.size()];

	//����� ������ 
	char* C = new char[message.size()];

	cout << "������� 1 ��� ���������� ��� ������� 2 ��� ������������: ";
	cin >> flage;

	//����������
	if (flage == 1)
	{
		//������� �������
		cout << "������� ������ �����:";
		cin >> sizeB;
		while (message.size() % sizeB != 0)
		{
			message += str;
		}
		cout << "������ ���������: " << message.size() << endl;
		strcpy(A, message.c_str());
		//���� �����
		int* K = new int[sizeB];
		cout << "������� ���� �� ����� �����: " << endl;
		for (int i = 0; i < sizeB; i++)
		{
			cout << "������� " << i + 1 << "-� ������� �����:";
			cin >> K[i];
			while (K[i] > sizeB || K[i] < 1)
			{
				cout << "���� ������� ������� �������, ���������, ��� ��� ��� ����� �������, ������� ������: " << endl;
				cout << "������� " << i + 1 << "-� ������� �����:";
				cin >> K[i];
			}

			for (int j = 0; j < i; j++)
			{
				while (K[i] > sizeB || K[i] == K[j] || K[i] < 1)
				{
					cout << "���� ������� ������� �������, ���������, ��� ��� ��� ����� �������, ������� ������: " << endl;
					cout << "������� " << i + 1 << "-� ������� �����:";
					cin >> K[i];
				}
			}
		}
		cout << "����: ";
		for (int i = 0; i < sizeB; i++)
		{
			cout << K[i];
		}
		//���� ������������ ��������
		for (int i = 0; i < (message.size() / sizeB); i++)
		{
			for (int j = 0; j < sizeB; j++)
				C[i * sizeB + j - 1] = A[i * sizeB + K[j] - 1];
		}
		//����� �����

		cout << endl << "Shifr: ";
		for (int i = 0; i < message.size(); i++)
		{
			cout << C[i - 1];
		}
		delete[]K;
	}
	//��c��������
	else if (flage == 2)
	{
		//������� �������
		cout << "������� ������ �����:";
		cin >> sizeB;
		bool check = false;
		while (check != true)
		{
			if (message.size() % sizeB == 0)
			{
				cout << "������ ��������" << endl;
				check = true;
			}
			else
			{
				cout << "������ �� ��������" << endl;
				cin >> sizeB;
			}
		}
		strcpy(A, message.c_str());
		//���� �����
		int* K = new int[sizeB];
		cout << "������� ���� �� ����� �����: " << endl;
		for (int i = 0; i < sizeB; i++)
		{
			cout << "������� " << i + 1 << "-� ������� �����:";
			cin >> K[i];

			while (K[i] > sizeB || K[i] < 1)
			{
				cout << "���� ������� ������� �������, ���������, ��� ��� ��� ����� �������, ������� ������: " << endl;
				cout << "������� " << i + 1 << "-� ������� �����:";
				cin >> K[i];
			}

			for (int j = 0; j < i; j++)
			{
				while (K[i] > sizeB || K[i] == K[j] || K[i] < 1)
				{
					cout << "���� ������� ������� �������, ���������, ��� ��� ��� ����� �������, ������� ������: " << endl;
					cin >> K[i];
				}
			}
		}
		cout << "����: ";
		for (int i = 0; i < sizeB; i++)
		{
			cout << K[i];
		}
		//���� ������������ ��������
		for (int i = 0; i < message.size() / sizeB; i++)
		{
			for (int j = 0; j < sizeB; j++)
				C[i * sizeB + K[j] - 2] = A[i * sizeB + j];
		}
		//����� �����
		cout << endl << "Fist message: ";
		for (int i = 0; i < message.size(); i++)
		{
			cout << C[i - 1];
		}
		delete[]K;
	}

	//flage < 1 or flage > 2
	else cout << "��� ����� �������" << endl;
	delete[]C;
	delete[]A;
}