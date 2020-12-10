#include <iostream>
#include <fstream>
#include<Windows.h>
#include <string>
#include <cmath>
#include <locale>
#include"kripto.h"
using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cripto *C[3]; 
	C[0] = new Ceasar();
	C[1] = new Vishner();
	C[2] = new Enigma();
	string namef;
	int ans = 1;
	bool iflag = false;
	bool oflag = false;
	ifstream fin;
	fstream fout;

	while (ans != 0)
	{
		system("cls");
		cout << "Выберите входной поток данных:" << endl;
		cout << "|1| - Консоль;" << endl;
		cout << "|2| - Файл;" << endl;
		cin >> ans;
		try {
			if (ans == 2) {
				iflag = true;
				cout << "Введите название файла: " << endl;
				cin.get();
				getline(cin, namef);
				fin.open(namef, ios::in);
				if (!fin.is_open())
					throw "Невозможно найти файл с таким именем";
			
				//cout << fin.is_open() << endl;
			}
			cout << "Выберите выходной поток данных:" << endl;
			cout << "|1| - Консоль;" << endl;
			cout << "|2| - Файл;" << endl;
			cin >> ans;
			if (ans == 2)
			{
				oflag = true;
				cout << "Введите название файла: " << endl;
				cin.get();
				getline(cin, namef);
				if (!formatname(namef)) throw namef;
				fout.open(namef, ios::out);
			}
		}
		catch (const char* error) {
			cout << error << endl;
			system("pause");
			continue;
		}
		catch (string namef) {
			cout << "Нельзя создать файл с таким именем\n имя файла измененено на " << namef << endl;
			fout.open(namef, ios::out);
		}
		system("cls");
		cout << "Выбор операции" << endl;
		cout << "|1|-Зашифровать Цезаря\n|2|-Расшифровать Цезаря\n|3|-Зашифровать Вижнера\n|4|-Расшифровать Вижнера\n|5|-Зашифровать Энигма\n|6|-Расшифровать Энигма\n|0|- для выхода\n->";
		cin >> ans;
		switch (ans)
		{
		case 1:

			C[0]->coding(
				(iflag == true) ? fin : cin,
				(oflag == true) ? fout : cout,
				(iflag == true) ? true : false,
				(oflag == true) ? true : false
			);
			cout << endl;
			break;
		case 2:

			C[0]->decoding(
				(iflag == true) ? fin : cin,
				(oflag == true) ? fout : cout,
				(iflag == true) ? true : false,
				(oflag == true) ? true : false
			);
			break;
		case 3:

			C[1]->coding(
				(iflag == true) ? fin : cin,
				(oflag == true) ? fout : cout,
				(iflag == true) ? true : false,
				(oflag == true) ? true : false
			);
			break;
		case 4: 
			C[1]->decoding(
				(iflag == true) ? fin : cin,
				(oflag == true) ? fout : cout,
				(iflag == true) ? true : false,
				(oflag == true) ? true : false
			);
			break;
		case 5:

			C[2]->coding(
				(iflag == true) ? fin : cin,
				(oflag == true) ? fout : cout,
				(iflag == true) ? true : false,
				(oflag == true) ? true : false
			);
			break;
		case 6:
			C[2]->decoding(
				(iflag == true) ? fin : cin,
				(oflag == true) ? fout : cout,
				(iflag == true) ? true : false,
				(oflag == true) ? true : false
			);
			break;
		case 0:
			cout << "Выход из программы..." << endl;
		}
		system("pause");
		if (iflag == true)fin.close();
		if (oflag == true)fout.close();
		iflag = oflag = false;
	}
	delete[] *C;
	return 0;

}
