#define _CRT_SECURE_NO_WARNINGS
#include"AllF.h"

void CodeMatrixAndPref()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//���� ���������
	string message;
	cout << "������� ���������: ";
	getline(cin, message);
	cout << endl;
	cout << "����� �������� � ���������: " << message.size() << endl;

	int s;
	s = message.size(); //����� �������� � ���������
	char* A = new char[s]; //����� ���������� � ������ 
	strcpy(A, message.c_str());


	vector <char> vec;

	int count = 0; //���������� ����� ��������� ��������
	bool f;

	for (int i = 0; i < s; i++)
	{
		f = true;
		for (int j = 0; j <= i; j++)
		{
			if (A[i] == A[j] && i != j)f = false;
		}
		if (f)
		{
			count++;
			vec.push_back(A[i]);
		}

	}
	cout << endl;
	cout << count << " -����� ��������� ��������" << endl;

	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " "; // ������ ������ � ���� ��� ������� ��� ����������

	}

	//���������� �� ��������
	int* K = new int[vec.size()];
	char* words = new char[vec.size()];
	for (int i = 0; i < vec.size(); i++)
	{
		int k = 0;
		for (int j = 0; j < s; j++)
		{
			if (vec[i] == A[j])
				k++;
		}
		words[i] = vec[i];
		K[i] = k;

		cout << "���������� ���������� " << vec[i] << ": " << k << endl;
	}

	for (int i = 1; i < vec.size(); ++i)
	{
		for (int j = 0; j < vec.size() - i; j++)
		{
			if (K[j] < K[j + 1])
			{
				int temp = K[j];
				int temp1 = words[j];
				K[j] = K[j + 1];
				words[j] = words[j + 1];
				K[j + 1] = temp;
				words[j + 1] = temp1;
			}
		}
	}
	cout << "���������� �� ������� " << endl;
	for (int i = 0; i < vec.size(); ++i)
	{
		cout << " " << words[i] << " " << K[i] << endl;
	}

	// ������� � �������� �������
	string* C = new string[vec.size()];
	C[0] = '1';

	for (int i = 1; i < vec.size(); i++)
	{
		C[i] = ('0') + C[i - 1];
	}
	cout << C[0] << endl;
	for (int i = 1; i < vec.size(); i++)
	{
		cout << C[i] << endl;
	}

	//���������� ���������� ���
	int V;
	V = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		V += K[i] * C[i].size();

	}
	cout << "������ �������������� ���������: " << V << endl;

}