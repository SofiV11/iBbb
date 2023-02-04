#define _CRT_SECURE_NO_WARNINGS
#include"AllF.h"

long int p, q, n, t, temp[100], j;
long int decrypText[100], encrypText[100], i, len;
bool flage;
string msg;

//Функция Зашифровки сообщения
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
	cout << "\n Зашифрованное сообщение: \n";
	for (i = 0; i < len; i++)
		printf("%c", encrypText[i]);
}

//Функция расшифровки сообщения
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
	cout << "\n Разшифрованное шифрованное сообщение: \n";
	for (i = 0; i < len; i++)
		printf("%c", decrypText[i]);
	printf("\n");
}

//Посчёт промежуточной пееременной для поиска закрытого ключа
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

//Функция проверки числа кол-во делителей (нахождение простого числа)
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

//Подсчёт открытого ключа e
long int calculateE()
{
	for (i = 2; i < t; i++)
	{
		if (gcalcul(i, t) == 1)
			return i;
	}
	return -1;
}

//Посчёт закрытого ключа d
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
	cout << "Добро пожаловать в программу кодировки RSA" << endl;

	//Ввод сообщения
	cout << "Введите сообщение: \n";
	fflush(stdin);
	getline(cin, msg);
	int flag = 0;
	cout << "\n Зашифровка-1, Разшифровка-2 : ";
	cin >> flag;
	if (flag == 1)
	{
		//Ввод первого простого числа
		do
		{
			cout << "Введите номер Р: " << endl;
			cin >> p;
			flage = isPrime(p);

			if (flage == false)
			{
				cout << "Неправильный ввод ";
			}
		} while (flage == 0);

		//Ввод второго простого числа
		do
		{
			cout << "Введите номер q: " << endl;
			cin >> q;
			flage = isPrime(q);

			if (flage == false)
			{
				cout << "Неправильный ввод ";
			}
		} while (flage == 0);

		//Подсчёт и перевод символов в числа
		for (i = 0; msg[i] != NULL; i++)
			decrypText[i] = msg[i];
		cout << "Количество символов в сообщении: " << i;

		//Вычисление ключей
		n = p * q;
		t = (p - 1) * (q - 1);
		long int e = calculateE();
		long int d = calculateD(e);

		//Зашифровка сообщения
		encrypt(e);
		cout << endl << "Ваш отрытый ключ: (" << e << "," << n << ")" << endl;
		cout << "Ваш закрытый ключ, не сообщайте его никому: " << d << endl;
	}
	else if (flag == 2)
	{
		long int d, n;
		int count = 0;
		cout << "Введите закрытый ключ: ";
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
		cout << "Нет такой команды";

	cin.get();
}

