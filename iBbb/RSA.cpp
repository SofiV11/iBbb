#define _CRT_SECURE_NO_WARNINGS
#include"AllF.h"

long int p, q, n, t, temp[100], j;
long int decrypText[100], encrypText[100], i, len;
bool flage;
string msg;

//������� ���������� ���������
void encrypt(long int e)
{
	long int pt, ct, key = e, k;
	i = 0;
	len = msg.length();
	while (i != len)
	{
		pt = decrypText[i];
		pt = pt - 97;
		k = 1;
		for (j = 0; j < key; j++)
		{
			k = k * pt;
			k = k % n;
		}
		temp[i] = k;
		ct = k + 97;
		encrypText[i] = ct;
		i++;
	}
	encrypText[i] = -1;
	cout << "\n ������������� ���������: \n";
	for (i = 0; i < len; i++)
		printf("%c", encrypText[i]);
}

//������� ����������� ���������
void decrypt(long int d, long int n, long int temp[], int len)
{
	long int pt, ct, key = d, k;
	i = 0;
	while (i != len)
	{
		ct = temp[i];
		k = 1;
		for (j = 0; j < key; j++)
		{
			k = k * ct;
			k = k % n;
		}
		temp[i] = k;
		pt = k + 97;
		decrypText[i] = pt;
		i++;
	}
	decrypText[i] = -1;
	cout << "\n �������������� ����������� ���������: \n";
	for (i = 0; i < len; i++)
		printf("%c", decrypText[i]);
	printf("\n");
}

//������ ������������� ����������� ��� ������ ��������� �����
long int gcalcul(long int a, long int b)
{
	{
		if (b == 0)
		{
			return a;
		}
		else
			return gcalcul(b, a % b);
	}
}

//������� �������� ����� ���-�� ��������� (���������� �������� �����)
bool isPrime(long int pr)
{
	int i;
	j = (long int)sqrt((long double)pr);
	for (i = 2; i <= j; i++)
	{
		if (pr % i == 0)
		{
			return false;
		}
	}
	return true;
}

//������� ��������� ����� e
long int calculateE()
{
	for (i = 2; i < t; i++)
	{
		if (gcalcul(i, t) == 1)
			return i;
	}
	return -1;
}

//������ ��������� ����� d
long int calculateD(long int x)
{
	long int k = 1;
	while (1)
	{
		k = k + t;
		if (k % x == 0)
			return(k / x);
	}
}

void RSA()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "����� ���������� � ��������� ��������� RSA" << endl;

	//���� ���������
	cout << "������� ���������: \n";
	fflush(stdin);
	getline(cin, msg);
	int flag = 0;
	cout << "\n ����������-1, �����������-2 : ";
	cin >> flag;
	if (flag == 1)
	{
		//���� ������� �������� �����
		do
		{
			cout << "������� ����� �: " << endl;
			cin >> p;
			flage = isPrime(p);

			if (flage == false)
			{
				cout << "������������ ���� ";
			}
		} while (flage == 0);

		//���� ������� �������� �����
		do
		{
			cout << "������� ����� q: " << endl;
			cin >> q;
			flage = isPrime(q);

			if (flage == false)
			{
				cout << "������������ ���� ";
			}
		} while (flage == 0);

		//������� � ������� �������� � �����
		for (i = 0; msg[i] != NULL; i++)
			decrypText[i] = msg[i];
		cout << "���������� �������� � ���������: " << i;

		//���������� ������
		n = p * q;
		t = (p - 1) * (q - 1);
		long int e = calculateE();
		long int d = calculateD(e);

		//���������� ���������
		encrypt(e);
		cout << endl << "��� ������� ����: (" << e << "," << n << ")" << endl;
		cout << "��� �������� ����, �� ��������� ��� ������: " << d << endl;
	}
	else if (flag == 2)
	{
		long int d, n;
		int count = 0;
		cout << "������� �������� ����: ";
		cin >> d;
		cout << " ";
		cin >> n;
		for (i = 0; msg[i] != NULL; i++)
		{
			encrypText[i] = msg[i];
			count++;
		}

		for (i = 0; encrypText[i] != NULL; i++)
		{
			temp[i] = encrypText[i] - 97;
		}

		decrypt(d, n, temp, count);
	}
	else
		cout << "��� ����� �������";

	cin.get();
}

