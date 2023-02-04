#define _CRT_SECURE_NO_WARNINGS
#include "AllF.h"

int* Shifr(double** mtrx, int C[], int& sizeB, int K[], int message) //������� ���������� ���������
{
	int help = 0;
	while (help < message)
	{
		for (int i = 0; i < sizeB; i++)
		{
			K[i + help] = 0;
			for (int j = 0; j < sizeB; j++)
			{
				K[i + help] += mtrx[i][j] * C[j + help];
			}
		}
		help += sizeB;

	}

	return K;
}

int* NOShifr(double** mtrx, int K[], int& sizeB, int C[], int Def, int message) //������� ����������� ���������
{
	int help = 0;
	while (help < message)
	{
		for (int i = 0; i < sizeB; i++)
		{
			C[i + help] = 0;
			for (int j = 0; j < sizeB; j++)
			{
				C[i + help] += mtrx[i][j] * K[j + help];
			}
		}
		help += sizeB;

	}
	return C;
}

void inversion(double** A, int N) //������� ���������� �������� �������
{
	double temp;

	double** E = new double* [N];

	for (int i = 0; i < N; i++)
		E[i] = new double[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			E[i][j] = 0.0;

			if (i == j)
				E[i][j] = 1.0;
		}

	for (int k = 0; k < N; k++)
	{
		temp = A[k][k];

		for (int j = 0; j < N; j++)
		{
			A[k][j] /= temp;
			E[k][j] /= temp;
		}

		for (int i = k + 1; i < N; i++)
		{
			temp = A[i][k];

			for (int j = 0; j < N; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}

	for (int k = N - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = A[i][k];

			for (int j = 0; j < N; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			A[i][j] = E[i][j];

	for (int i = 0; i < N; i++)
		delete[] E[i];

	delete[] E;
}

void clearMemory(double** a, int n) { //������� ������������ ������, ���������� ��� ��������� ������������ ������
	for (int i = 0; i < n; i++) {
		delete[] a[i];
	}
	delete[] a;
}

int findDet(double** a, int n) //������� ���������� ������������ �������
{
	//����������� ������� ���������� ������������ �������
	if (n == 1)
		return a[0][0];
	else if (n == 2)
		return a[0][0] * a[1][1] - a[0][1] * a[1][0];
	else
	{
		int d = 0;
		for (int k = 0; k < n; k++)
		{
			double** m = new double* [n - 1];
			for (int i = 0; i < n - 1; i++)
			{
				m[i] = new double[n - 1];
			}
			for (int i = 1; i < n; i++)
			{
				int t = 0;
				for (int j = 0; j < n; j++)
				{
					if (j == k)
						continue;
					m[i - 1][t] = a[i][j];
					t++;
				}
			}
			d += pow(-1, k + 2) * a[0][k] * findDet(m, n - 1);
			clearMemory(m, n - 1); //����������� ������, ���������� ��� �������������� ����������
		}
		return d; //���������� ������������ �������
	}
}

void MatrixVectorShifr()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//���� ���������
	string message, str;
	str = "*";
	int sizeB = 3, help = 0, flage = 0;
	double Det = 0;
	cout << "������� ��������� (���� ��� ����� �������������, �� ���������� ��� ����): " << endl;
	getline(cin, message);

	//basic array
	char* A = new char[message.size()];
	strcpy(A, message.c_str());
	int* C = new int[message.size()];

	cout << endl << "������� 1 ��� ���������� ��� ������� 2 ��� ������������: ";
	cin >> flage;
	cout << endl;

	//����������
	if (flage == 1)
	{
		//������ ������� ���������
		cout << "������ ���������: " << message.size() << endl;
		if (message.size() % sizeB != 0)
			cout << endl << "������ ����������� ��������: ";
		while (message.size() % sizeB != 0)
		{
			message += str;
		}
		cout << "������������� ������: " << message.size() << endl;
		strcpy(A, message.c_str());

		//�������� �������
		double** mtrx = new double* [sizeB];
		for (int i = 0; i < sizeB; i++)
		{
			mtrx[i] = new double[sizeB];
		}

		//���������� ������� �������������
		cout << endl << "��������� �������: " << endl;
		for (int i = 0; i < sizeB; i++)
		{
			for (int j = 0; j < sizeB; j++)
			{
				cout << "������� ������� [" << i << "]" << "[" << j << "]:  ";
				cin >> mtrx[i][j];
				while (mtrx[i][j] == 0)
				{
					cout << "������� ������� ������� �� ����������������, ������� ������ �������: \t";
					cin >> mtrx[i][j];
				}
			}
		}

		//����� ������� � �������
		cout << endl << "�� ����� �������: " << endl;
		for (int i = 0; i < sizeB; i++)
		{
			for (int j = 0; j < sizeB; j++)
			{
				cout << " " << mtrx[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;

		//�������� �� ������������� �������� �������
		Det = findDet(mtrx, sizeB);
		if (Det == 0)
		{
			cout << "�� ���������� �������� ������� ��� ������ �����, �� �� ������� ������������ ������ ��������� ";
		}
		else
		{
			//������� ��������� � ����� �����
			cout << "�������� ��������� � ������: " << endl;
			for (int i = 0; i < message.size(); i++)
			{
				C[i] = (int)A[i];
				cout << C[i] << "\t";
			}
			cout << endl;

			// ���������� ���������
			int* K = new int[message.size()];
			Shifr(mtrx, C, sizeB, K, message.size());

			//����� �������������� ���������
			cout << endl << "����: " << endl;
			for (int i = 0; i < message.size(); i++)
			{
				cout << K[i] << "\t";
			}
			cout << endl << endl;
			delete[] K;
		}
		clearMemory(mtrx, sizeB);
	}

	//��c��������
	else if (flage == 2)
	{
		// ���������� ��������� � ��������� 
		int message = 0;
		cout << "������� ���-�� ����� � �����: ";
		cin >> message;
		while (message % sizeB != 0)
		{
			cout << "����������� ���-�� ��������, ���������� �����: ";
			cin >> message;
		}

		//���� ����� ���������
		cout << endl << "������� ���� ���������: " << endl;
		int* K = new int[message];
		for (int i = 0; i < message; i++)
		{
			cout << "������������� ������� " << i << ":  ";
			cin >> K[i];
			cout << endl;
		}

		for (int i = 0; i < message; i++)
		{
			cout << K[i] << "\t";
		}
		cout << endl;

		//�������� �������
		double** mtrx = new double* [sizeB];
		for (int i = 0; i < sizeB; i++)
		{
			mtrx[i] = new double[sizeB];
		}

		//���������� ������� �������������
		cout << "��������� �������: " << endl;
		for (int i = 0; i < sizeB; i++)
		{
			for (int j = 0; j < sizeB; j++)
			{
				cout << "������� ������� [" << i << "]" << "[" << j << "]:   ";
				cin >> mtrx[i][j];
				while (mtrx[i][j] == 0)
				{
					cout << "������� ������� ������� �� ����������������, ������� ������ �������: \t";
					cin >> mtrx[i][j];
				}
			}
		}

		//����� ������� �� �����
		cout << endl << "�� ����� �������: " << endl;
		for (int i = 0; i < sizeB; i++)
		{
			for (int j = 0; j < sizeB; j++)
			{
				cout << " " << mtrx[i][j] << " ";
			}
			cout << endl;
		}

		//�������� �� ������������� �������� �������
		Det = findDet(mtrx, sizeB);
		if (Det == 0)
		{
			cout << "�� ���������� �������� ������� ��� ������ �����, ���������� ����� ";
		}
		else
		{
			// ���������� �������� �������
			inversion(mtrx, sizeB);
			cout << endl;
			for (int i = 0; i < sizeB; i++)
			{
				for (int j = 0; j < sizeB; j++)
				{
					cout << " " << mtrx[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;

			//����������� ���������
			NOShifr(mtrx, K, sizeB, C, Det, message);

			help = 1;

			//����� ��������� ��������� � ������� ����
			cout << endl << "�������� ��������� � ������: " << endl;
			for (int i = 0; i < message; i++)
			{

				if (i != help)
					A[i] = (char)C[i] + 1;
				else
				{
					A[i] = (char)C[i];
					help += 3;
				}
				cout << A[i];
			}
		}
		delete[] K;
	}
	else cout << "��� ����� �������" << endl;
	delete[] A;
	delete[] C;

}