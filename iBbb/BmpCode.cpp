#include "AllF.h"

using namespace std;

unsigned char signature[2];

int h, w;

vector<vector <char>> mtrx; //двумерный вектор(вектор вектора)

vector<char> vec; //вводим глобальные переменные


int get_pix_near(int& x, int& y) //j=x;i=y функция для поиска соседних пикселей для определения направления
{
	if ((mtrx[y + 1][x] == '1' && mtrx[y + 1][x - 1] == '0' && mtrx[y][x - 1] == '0') && ((vec.size() == 0) || (vec.back() != '1'))) {  // 0 вверх
		y = y + 1;
		return 0;
	}
	if ((mtrx[y - 1][x] == '1' && mtrx[y][x + 1] == '0' && mtrx[y - 1][x + 1] == '0') && ((vec.size() == 0) || (vec.back() != '0'))) //1=вниз
	{
		y = y - 1;
		return 1;
	}
	if ((mtrx[y][x - 1] == '1' && mtrx[y - 1][x] == '0' && mtrx[y - 1][x - 1] == '0') && ((vec.size() == 0) || (vec.back() != '3'))) //влево
	{
		x = x - 1;
		return 2;
	}
	if ((mtrx[y][x + 1] == '1' && mtrx[y + 1][x] == '0' && mtrx[y + 1][x + 1] == '0') && ((vec.size() == 0) || (vec.back() != '2')))   //вправо                    
	{
		x = x + 1;
		return 3;
	}
	if ((mtrx[y + 1][x - 1] == '1' && mtrx[y][x - 1] == '0' && mtrx[y - 1][x - 1] == '0') && ((vec.size() == 0) || (vec.back() != '6')))   //по диагонали 
	{
		x = x - 1;
		y = y + 1;
		return 4;
	}
	if ((mtrx[y + 1][x + 1] == '1' && mtrx[y + 1][x - 1] == '0' && mtrx[y + 1][x] == '0') && ((vec.size() == 0) || (vec.back() != '7')))                 //5=по диагонали вниз вправо
	{
		x = x + 1;
		y = y + 1;
		return 5;
	}
	if ((mtrx[y - 1][x + 1] == '1' && mtrx[y + 1][x + 1] == '0' && mtrx[y][x + 1] == '0') && ((vec.size() == 0) || (vec.back() != '4')))                 //6=по диагонали вниз влево
	{
		x = x + 1;
		y = y - 1;
		return 6;
	}
	if ((mtrx[y - 1][x - 1] == '1' && mtrx[y - 1][x] == '0' && mtrx[y - 1][x + 1] == '0') && ((vec.size() == 0) || (vec.back() != '5')))                 //7=по диагонали вниз влево
	{
		x = x - 1;
		y = y - 1;
		return 7;
	}

}

void give_pix(char res,int &x, int &y)
{

	if(res == '0')
	{
		mtrx[y + 1][x] = '1'; 
		y = y + 1;
	}
	if (res == '1')
	{
		mtrx[y - 1][x] = '1';
		y = y - 1;
	}
	if (res == '2')
	{
		mtrx[y][x - 1] = '1';
		x = x - 1;
	}
	if (res == '3')
	{
		mtrx[y][x + 1] = '1';
		x = x + 1;
	}
	if (res == '4')
	{
		mtrx[y + 1][x - 1] = '1';
		x = x - 1;
		y = y + 1;
	}
	if (res == '5')
	{
		mtrx[y + 1][x + 1] = '1';
		x = x + 1;
		y = y + 1;
	}
	if (res == '6')
	{
		mtrx[y - 1][x + 1] = '1';
		x = x + 1;
		y = y - 1;
	}
	if (res == '7')
	{
		mtrx[y - 1][x - 1] = '1';
		x = x - 1;
		y = y - 1;
	}
} 

//___________________________________________________________________________________________________________________________________

void BmpCode()
{
	signature[0] = 'B';
	signature[1] = 'M';
	int choice = 0;

	int size = 0, pixels_adress = 0, width = 0, height = 0;
	short int bits_per_pixel = 0;

	cout << "Vvedite 1(code) or 2(decode) : ";
	cin >> choice;
	cout << endl;
	//________________________________________________________________________________________________________________________________
	if (choice == 1)
	{
		//ifstream file("data.txt");
		ifstream file;
		file.open("picture1.bmp");
		if (!file) cout << "file not found" << endl;
		else
		{
			cout << "File open" << endl;
			file.seekg(2, ios::beg); // Переходим на 2 байт
			file.read((char*)&size, sizeof(int)); // Считываем размер файлa
			file.seekg(10, ios::beg); // Переходим на 10 байт
			file.read((char*)&pixels_adress, sizeof(int)); // Считываем адрес начала массива пикселей
			file.seekg(18, ios::beg);
			file.read((char*)&width, sizeof(int));
			file.read((char*)&height, sizeof(int)); // Считываем ширину и высоту изображения (в пикселях)
			file.seekg(28, ios::beg);
			file.read((char*)&bits_per_pixel, sizeof(short int));
			file.seekg(pixels_adress, ios::beg);

			//cout << "Size: " << size << endl;
			//cout << "pixels_adress: " << pixels_adress << endl;
			cout << "bits per pixel: " << bits_per_pixel << endl;
			cout << "Width: " << width << endl;
			cout << "Height: " << height << endl;

			int h, w;
			h = height;
			w = width;

			mtrx.resize(h, vector<char>(w)); //заполняем двумерный вектор значениями 0 и 1 char
			if (bits_per_pixel == 24)
			{
				unsigned int pix = 0; //

				for (int i = 0; i < h; i++)
				{
					for (int j = 0; j < w; j++)
					{
						file.read((char*)&pix, 3); //24-бит на пиксель на каждый цвет 1 байт (8 бит)

						if (pix == 0xFFFFFF)//pix==0xF0 || pix==0x0F || pix == 0xFFF ||pix==0xFF )
							mtrx[i][j] = '0';
						else
							mtrx[i][j] = '1';

					}
					file.read((char*)&pix, 1);
				}
			}

			cout << "MTRX:" << endl; //
			for (int i = 0; i < h; ++i)
			{
				for (int j = 0; j < w; j++)
				{
					cout << " " << mtrx[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;

			bool start = false;
			int start_x = 0, start_y = 0;

			for (int i = 0; i < h; i++)        //x=i; y=j 
			{
				for (int j = 0; j < w; j++)
				{
					if (mtrx[i][j] == '1')
					{
						start = true;                   // поиск точки старта(попадаем в контур)
						start_x = j;  
						start_y = i; 
						break;
					}
					if (start) break;
				}
			}
			cout << "start coordinates: " << "(" << start_y + 1 << "," << start_x + 1 << ")" << endl;

			int x = start_x; //присваиваем значения точки старта
			int y = start_y;

			do
			{
				vec.push_back(get_pix_near(x, y) + '0'); //начиная с точки старта идем по контуру и добавляем в вектор значение
				cout << x << " " << y << endl; //вывод каждой координаты
			} while (!(x == start_x && y == start_y)); //пока не пройдем весь контур и не окажемся в точке старта

			for (int i = 0; i < vec.size(); i++) //вывод значений направления при обходе контура
			{
				cout << vec[i];
			}

			cout << endl;
			cout << "***" << endl;
			file.close();
		}
	}
	//_____________________________________________________________________________________________________________________________

	else if (choice == 2)
	{
	int h, w;
	cout << "VVedite h: ";
	cin >> h;
	cout << "Vvedite w: ";
	cin >> w;
	cout << endl;

	int x;
	int y;
	//cout << "Vvedite startovie koordinati" << endl; //точка старта 
	cout << "x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	cout << endl;

	cout << "Vvedite kod: " << endl; //код напрaвлений
	
	vector<char> code;
	{
		string c;
		cin >> c;
		for (int i = 0; i < c.size(); ++i)
			if (c[i] >= '0' && c[i] <= '7')
				code.push_back(c[i]);
		for (int i = 0; i < code.size(); i++) cout << code[i];
	}
	cout << endl;
 
	mtrx.resize(h, vector<char>(w));

	for (int i = 0; i < h; ++i) //заполним двумкрный вектор-матрицу 0
	{
		for (int j = 0; j < w; j++)
		{
			mtrx[i][j]='0';
		}
	}
	cout << endl;

	
	for (int i = 0; i < code.size(); ++i)

	{
		give_pix(code[i], x, y);
	}

	cout << "MTRX:" << endl;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; j++)
		{
			cout << " " << mtrx[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

		unsigned int pix = 0;
		ofstream file_out;
		file_out.open("res.bmp");

		unsigned int Size = w * h * 3 + h + 54;
		unsigned int reserved = 0;
		unsigned int pos_of_start = 54;
		unsigned int size_header = 40;
		unsigned int hieght = h;
		unsigned int wieght = w;
		unsigned short biPlanes = 1;
		unsigned short bit_per_pixel = 24;
		unsigned int compression = 0;
		unsigned int size_of_image = 0;
		unsigned int horizontal_resolution = 0;
		unsigned int vertical_resolution = 0;
		unsigned int used_color = 0;
		unsigned int main_color = 0;
		file_out.write((char*)&signature, 2); //unsigned char[2] "BM" (без символа завершения строки т.е. = 2 байта ,вносиv по одному символу)
		file_out.write((char*)&Size, 4);//unsigned int size -  размер изображения в байтах (при создании изображения 600на 600 получается что он равен 600*600*3+54=1080054) 
		file_out.write((char*)&reserved, 4);
		file_out.write((char*)&pos_of_start, 4);  //unsigned int- позиция начала изображения,смещение=54 в байтах
		file_out.write((char*)&size_header, 4); //unsigned int -размер информация об изображении =40 в байтах
		file_out.write((char*)&wieght, 4);  //unsigned int - ширина
		file_out.write((char*)&hieght, 4); //unsigned int- высота
		file_out.write((char*)&biPlanes, 2); //unsigned short- глубина цвета (использую 24)
		file_out.write((char*)&bit_per_pixel, 2); //unsigned short- глубина цвета (использую 24)
		file_out.write((char*)&compression, 4); //unsigned int- сжатие =0 
		file_out.write((char*)&size_of_image, 4); //unsigned int- размер сжатия =0
		file_out.write((char*)&horizontal_resolution, 4);//unsigned int- вертикальное разрешение =0
		file_out.write((char*)&vertical_resolution, 4); //unsigned int- горизонтальное разрешение =0
		file_out.write((char*)&used_color, 4); //unsigned int =0
		file_out.write((char*)&main_color, 4); //unsigned int =0

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (mtrx[i][j] == '1')
					pix = 0x000000;
				else
					pix = 0xFFFFFF;

				file_out.write((char*)&pix, 3);

			}
			char pix = 0;
			file_out.write(&pix, 1);
		}

		cout << endl;
		cout << "***" << endl;
		file_out.close();
	}

	else cout << "Null" << endl;

}