#define _CRT_SECURE_NO_WARNINGS
#include "AllF.h"


void Reshuffle()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i = 0, key = 0, flage = 0, sizeB;
	string message, str = "*";
	cout << "Введите сообщение:" << endl;
	//getline(cin, message);
	cin >> message;
	cout << "Размер сообщения: " << message.size() << endl;


	char* A = new char[message.size()];

	//Новый массив 
	char* C = new char[message.size()];

	cout << "Введите 1 для ЗАШИФРОВКИ или введите 2 для РАССШИФРОВКИ: ";
	cin >> flage;

	//Зашифровка
	if (flage == 1)
	{
		//Задание размера
		cout << "Введите размер блока:";
		cin >> sizeB;
		while (message.size() % sizeB != 0)
		{
			message += str;
		}
		cout << "Размер сообщения: " << message.size() << endl;
		strcpy(A, message.c_str());
		//Ввод ключа
		int* K = new int[sizeB];
		cout << "Введите ключ по одной цифре: " << endl;
		for (int i = 0; i < sizeB; i++)
		{
			cout << "Введите " << i + 1 << "-й элемент ключа:";
			cin >> K[i];
			while (K[i] > sizeB || K[i] < 1)
			{
				cout << "Этот элемент слишком большой, маленький, или уже был такой элемент, введите другой: " << endl;
				cout << "Введите " << i + 1 << "-й элемент ключа:";
				cin >> K[i];
			}

			for (int j = 0; j < i; j++)
			{
				while (K[i] > sizeB || K[i] == K[j] || K[i] < 1)
				{
					cout << "Этот элемент слишком большой, маленький, или уже был такой элемент, введите другой: " << endl;
					cout << "Введите " << i + 1 << "-й элемент ключа:";
					cin >> K[i];
				}
			}
		}
		cout << "Ключ: ";
		for (int i = 0; i < sizeB; i++)
		{
			cout << K[i];
		}
		//Цикл перестановки символов
		for (int i = 0; i < (message.size() / sizeB); i++)
		{
			for (int j = 0; j < sizeB; j++)
				C[i * sizeB + j - 1] = A[i * sizeB + K[j] - 1];
		}
		//Вывод шифра

		cout << endl << "Shifr: ";
		for (int i = 0; i < message.size(); i++)
		{
			cout << C[i - 1];
		}
		delete[]K;
	}
	//Раcшифровка
	else if (flage == 2)
	{
		//Задание размера
		cout << "Введите размер блока:";
		cin >> sizeB;
		bool check = false;
		while (check != true)
		{
			if (message.size() % sizeB == 0)
			{
				cout << "Размер подходит" << endl;
				check = true;
			}
			else
			{
				cout << "Размер не подходит" << endl;
				cin >> sizeB;
			}
		}
		strcpy(A, message.c_str());
		//Ввод ключа
		int* K = new int[sizeB];
		cout << "Введите ключ по одной цифре: " << endl;
		for (int i = 0; i < sizeB; i++)
		{
			cout << "Введите " << i + 1 << "-й элемент ключа:";
			cin >> K[i];

			while (K[i] > sizeB || K[i] < 1)
			{
				cout << "Этот элемент слишком большой, маленький, или уже был такой элемент, введите другой: " << endl;
				cout << "Введите " << i + 1 << "-й элемент ключа:";
				cin >> K[i];
			}

			for (int j = 0; j < i; j++)
			{
				while (K[i] > sizeB || K[i] == K[j] || K[i] < 1)
				{
					cout << "Этот элемент слишком большой, маленький, или уже был такой элемент, введите другой: " << endl;
					cin >> K[i];
				}
			}
		}
		cout << "Ключ: ";
		for (int i = 0; i < sizeB; i++)
		{
			cout << K[i];
		}
		//Цикл перестановки символов
		for (int i = 0; i < message.size() / sizeB; i++)
		{
			for (int j = 0; j < sizeB; j++)
				C[i * sizeB + K[j] - 2] = A[i * sizeB + j];
		}
		//Вывод шифра
		cout << endl << "Fist message: ";
		for (int i = 0; i < message.size(); i++)
		{
			cout << C[i - 1];
		}
		delete[]K;
	}

	//flage < 1 or flage > 2
	else cout << "Нет такой команды" << endl;
	delete[]C;
	delete[]A;
}