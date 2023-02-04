#define _CRT_SECURE_NO_WARNINGS
#include "AllF.h"

int Key(int K[], int sizeB) //������� ����� ������ �������������
{
	cout << "������� ���� �� ����� �����: " << endl << endl;
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
		cout << endl;
	}
	cout << endl;
	cout << "����: ";
	for (int i = 0; i < sizeB; i++)
	{
		cout << K[i];
	}
	cout << endl << endl;
	return NULL;
}

void MatrixShifr()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//���� ���������
	string message;
	cout << "������� ���������:" << endl;
	getline(cin, message);
	cout << endl;
	cout << "������ ���������: " << message.size() << endl;
	//basic array
	char* A = new char[message.size()];
	strcpy(A, message.c_str());

	//�������� ������� �������
	int s, c;
	s = sqrt(message.size());
	c = s;
	while (c * s < message.size())
	{
		c++;
	}

	cout << "� ������� ���������� " << c << " �����" << endl;
	cout << "� ������� ���������� " << s << " ��������" << endl;

	//��������� ������
	char** mtrx = new char* [c];
	for (int i = 0; i < c; i++)
	{
		mtrx[i] = new char[s];
	}

	int flage = 0, help = 0;
	cout << endl;
	cout << "������� 1 ��� ���������� ��� ������� 2 ��� ������������: ";
	cin >> flage;
	cout << endl;

	//����������
	if (flage == 1)
	{
		//key
		int* K = new int[c];
		cout << "���� �����: " << endl;
		Key(K, c);
		//���������� �������
		for (int i = 0; i < c; i++)
		{
			for (int j = 0; j < s; j++)
			{
				mtrx[K[i] - 1][j] = A[help];
				help++;
			}
		}
		//����� ������������ �������
		cout << "�������: " << endl;
		for (int i = 0; i < c; i++)
		{
			for (int j = 0; j < s; j++)
			{
				cout << " " << mtrx[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		//key2
		cout << "���� ��������: " << endl;
		Key(K, s);
		//����� �������������� ���������
		cout << "������������� ���������: ";
		for (int j = 0; j < s; j++)
		{
			for (int i = 0; i < c; i++)
			{
				cout << mtrx[i][K[j] - 1];
			}
		}
		delete[]K;
	}

	//��c��������
	else if (flage == 2)
	{
		//�������� ������� ���������
		if (c * s != message.size())
		{
			cout << "��������� ����� ������������ ������, ���������� �����! ";
		}
		else
		{
			//key
			int* K = new int[c];
			cout << "���� ��������: " << endl;
			Key(K, s);
			//���������� �������
			for (int j = 0; j < s; j++)
			{
				for (int i = 0; i < c; i++)
				{
					mtrx[i][K[j] - 1] = A[help];
					help++;
				}
			}

			//key2
			cout << "���� �����: " << endl;
			Key(K, c);
			//����� ��������������� ���������
			cout << "�������������� ���������: ";
			for (int i = 0; i < c; i++)
			{
				for (int j = 0; j < s; j++)
				{
					cout << mtrx[K[i] - 1][j];
				}
			}
			delete[]K;
		}
	}
	//����� ������������ �������
	else cout << "��� ����� �������" << endl;
	delete[]A;
	delete[] mtrx[0];
	delete[] mtrx;
}