#define _CRT_SECURE_NO_WARNINGS
#include "AllF.h"

int Key(int K[], int sizeB) //Функция ввода ключей пользователем
{
	cout << "Введите ключ по одной цифре: " << endl << endl;
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
		cout << endl;
	}
	cout << endl;
	cout << "Ключ: ";
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
	//Ввод сообщения
	string message;
	cout << "Введите сообщение:" << endl;
	getline(cin, message);
	cout << endl;
	cout << "Размер сообщения: " << message.size() << endl;
	//basic array
	char* A = new char[message.size()];
	strcpy(A, message.c_str());

	//Рассчёты размера матрицы
	int s, c;
	s = sqrt(message.size());
	c = s;
	while (c * s < message.size())
	{
		c++;
	}

	cout << "В матрице получается " << c << " строк" << endl;
	cout << "В матрице получается " << s << " столбцов" << endl;

	//Матричный массив
	char** mtrx = new char* [c];
	for (int i = 0; i < c; i++)
	{
		mtrx[i] = new char[s];
	}

	int flage = 0, help = 0;
	cout << endl;
	cout << "Введите 1 для ЗАШИФРОВКИ или введите 2 для РАССШИФРОВКИ: ";
	cin >> flage;
	cout << endl;

	//Зашифровка
	if (flage == 1)
	{
		//key
		int* K = new int[c];
		cout << "Ключ строк: " << endl;
		Key(K, c);
		//Заполнение матрицы
		for (int i = 0; i < c; i++)
		{
			for (int j = 0; j < s; j++)
			{
				mtrx[K[i] - 1][j] = A[help];
				help++;
			}
		}
		//Вывод получившейся матрицы
		cout << "Матрица: " << endl;
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
		cout << "Ключ столбцов: " << endl;
		Key(K, s);
		//вывод зашифрованного сообщения
		cout << "Зашифрованное сообщение: ";
		for (int j = 0; j < s; j++)
		{
			for (int i = 0; i < c; i++)
			{
				cout << mtrx[i][K[j] - 1];
			}
		}
		delete[]K;
	}

	//Раcшифровка
	else if (flage == 2)
	{
		//Проверка размера сообщения
		if (c * s != message.size())
		{
			cout << "Сообщение имеет неправильный размер, попробуйте снова! ";
		}
		else
		{
			//key
			int* K = new int[c];
			cout << "Ключ столбцов: " << endl;
			Key(K, s);
			//Заполнение матрицы
			for (int j = 0; j < s; j++)
			{
				for (int i = 0; i < c; i++)
				{
					mtrx[i][K[j] - 1] = A[help];
					help++;
				}
			}

			//key2
			cout << "Ключ строк: " << endl;
			Key(K, c);
			//вывод расшифрованного сообщения
			cout << "Расшифрованное сообщение: ";
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
	//Выбор неправильной команды
	else cout << "Нет такой команды" << endl;
	delete[]A;
	delete[] mtrx[0];
	delete[] mtrx;
}