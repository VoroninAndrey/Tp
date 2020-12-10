#include "kripto.h"
#include <iostream>
#include <fstream>
#include<Windows.h>
#include <string>
#include <cmath>
#include <locale>
bool cripto::format(string& len)
{
	bool flag = true;
	string s;
	for (unsigned int i = 0; i < len.size(); i++) {
		if (len[i] <= 'Z' && len[i] >= 'A' || len[i] <= 'z' && len[i] >= 'a') {
			if (len[i] <= 'Z' && len[i] >= 'A') len[i] = tolower(len[i]);
			s += len[i];
		}
		else if (len[i] <= 'Я' && len[i] >= 'А' || len[i] <= 'я' && len[i] >= 'а') flag= false;
	}
	len = s;
	return flag;
}

bool formatname(string &len)
{
	int flag = true;
	string format;
	for (auto i : len) {
		if (i == '/' || i == '?' || i == '\\' || i == '*' || i == '<' || i == '>' || i == ':')flag = false;
		else format += i;

	}
	len = format;
	return flag;
}
long cripto::mod26(long a)//циклический сдвиг
{
	return (a % 26 + 26) % 26;
}

int cripto::li(char l)//возвращает код буквы от 0-25
{
	return l - 'a';
}

int cripto::indexof(char* array, int find)//вычисление индекса массива
{
	return strchr(array, find) - array;
}

void cripto::coding(istream & in, ostream & out, bool iflag, bool oflag)
{
	if (iflag == false)
	{
		cout << "Введите строку для кодирования:" << endl;//ввод строки с клавиатуры, 
		//если пустая строка или строка содержит русские буквы, ввод заново
		in.ignore();
		getline(in, zesar);
		while (true) {
			try {

				if (!format(zesar)) throw "Строка содержала запрещённые символы";
				if (zesar == "") throw "Введена пустая строка";
				zesar = MethodOfCoding(zesar);
				if (oflag == false)out << "Закодированная строка: " << endl;
				out << zesar;
				out << endl;
				break;
			}
			catch (const char* a) {

				cout << a << endl << "Ведите строку заново" << endl;
				getline(in, zesar);
			}
		}
	}
	else
	{
		if (!in.eof()) {
			do
			{

				try {
					getline(in, zesar);
					if (zesar == "") throw "Введена пустая строка в файле";
					if (!format(zesar)) throw "В строке содержатся запрещенные символы, она кодироваться не будет";
					zesar = MethodOfCoding(zesar);
					if (oflag == false)out << "Закодированная строка: " << endl;
					out << zesar;
					out << endl;
				}
				catch (const char* error) {
					cout << error << endl;

				}
			} while (!in.eof());
		}
		else cout << "Файл пуст" << endl;
	}
}

void cripto::decoding(istream & in, ostream & out, bool iflag, bool oflag)
{
	if (oflag == false)
	{
		try {
			if (iflag == true) {
				if (!in.eof()) {
					do {
						getline(in, zesar);
						if (!format(zesar)) throw "В строке содержатся запрещенные символы, она кодироваться не будет";
						zesar = MethodOfDecoding(zesar);
						if (oflag == false)out << "Декодированная строка: " << endl;
						out << zesar;
						out << endl;
					} while (!in.eof());
				}
				else throw "Файл пуст";
			}
			else {
				if (zesar == "0") throw "Сообщение для декодирования не найдено";
				zesar = MethodOfDecoding(zesar);
				cout << "Декодированная строка: " << endl;
				cout << zesar;
				cout << endl;
			}
		}
		catch (const char* error) {
			cout << error << endl;

		}

	}
	else
	{
		if (!in.eof()) {
			do
			{

				try {
					getline(in, zesar);
					if (zesar == "") throw "Введена пустая строка в файле";
					if (!format(zesar)) throw "В строке содержатся запрещенные символы, она кодироваться не будет";
					zesar = MethodOfDecoding(zesar);
					if (oflag == false)out << "Закодированная строка: " << endl;
					out << zesar;
					out << endl;
				}
				catch (const char* error) {
					cout << error << endl;

				}
			} while (!in.eof());
		}
		else cout << "Файл пуст" << endl;

	}
}





//методы класса Ceasar
string& Ceasar::CaesarCodAndDec(int shift)
{
	unsigned char code; //вводится переменная с возможным значением 0-255 для того, чтобы смещение не приводило к ситуации, когда символ больше 127
	for (size_t i = 0; i < zesar.size(); i++) {
		if (zesar[i] <= 'z' && zesar[i] >= 'a') {
			code = zesar[i] + (shift % 26);

			//zesar[i] += shift;//сдвиг
			if (code > 'z') code -= 26;
			else if (code < 'a') code += 26;
			zesar[i] = code;
		}
	}
	return zesar;
}

string & Ceasar::MethodOfCoding(string & len)
{
	zesar = len;
	cout << "введите сдвиг" << endl << "->";
	while (!(cin >> shift))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Некорректный сдвиг" << endl;
	}
	return (CaesarCodAndDec(shift));
}

string & Ceasar::MethodOfDecoding(string & len)
{
	zesar = len;
	cout << "введите сдвиг" << endl << "->";
	while (!(cin >> shift))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Некорректный сдвиг" << endl;
	}
	return (CaesarCodAndDec(-1 * shift));
}


//методы класса Vishner
string& Vishner::VishnerCoding()
{
	for (size_t i = 0; i < zesar.size(); i++)
	{
		int c = zesar[i];
		c += key[i] - 'a';
		if (c > 'z') c -= 26;
		else if (c < 'a') c += 26;
		zesar[i] = c;
	}
	return zesar;
}

//методы кодирования-декодирования Вижнера
string& Vishner::VishnerDecoding()
{

	for (size_t i = 0; i < zesar.size(); i++)
	{
		int c = zesar[i];
		c -= key[i] - 'a';
		if (c > 'z') c -= 26;
		else if (c < 'a') c += 26;
		zesar[i] = c;
	}
	return zesar;
}

string & Vishner::MethodOfCoding(string & len)
{
	cout << "Введите кодовое слово" << endl;
	cin.ignore();
	getline(cin, code);
	while (true) {
		try {
			zesar = len;
			if (!format(code)) throw "Кодовое слово содержит запрещенные символы";
			if (len.size() < code.size()) throw "Кодовое слово больше длины сообщения";
			getKey();
			return (VishnerCoding());

		}
		catch (const char* error) {
			cout << error << endl << "Введите новое кодовое слово" << endl;
			/*	cin.ignore();*/
			getline(cin, code);
		}
	}

}

string & Vishner::MethodOfDecoding(string & len)
{
	cout << "Введите кодовое слово" << endl;
	cin.ignore();
	getline(cin, code);
	while (true) {
		try {
			zesar = len;
			if (!format(code)) throw "Кодовое слово содержит запрещенные символы";
			if (len.size() < code.size()) throw "Кодовое слово больше длины сообщения";
			getKey();
			return (VishnerDecoding());

		}
		catch (const char* error) {
			cout << error << endl << "Введите новое кодовое слово" << endl;
			/*	cin.ignore();*/
			getline(cin, code);
		}
	}
}

string & Vishner::getKey()
{
	key = zesar;
	int size = code.size();
	for (size_t k = 0; k < zesar.size(); k++) {//делаем ключ
		key[k] = code[k % size];
	}
	return key;
}

// методы кодирования-декодирования Энеигма
string& Enigma::EnigmaCodingAndDecoding()
{
	char alpha[] = "abcdefghijklmnopqrstuvwxyz";
	char rotors[3][27] =
	{
	  "ekmflgdqvzntowyhxuspaibrcj",
	  "ajdksiruxblhwtmcqgznpyfvoe",
	  "bdfhjlcprtxvznyeiwgakmusqo"
	};
	char reflector[] = "yruhqsldpxngokmiebfzcwvjat";
	char key[] = "cuq";
	//присваивание начальных значений роторам (код буквы от 0-25)
	int L = li(key[0]);
	int M = li(key[1]);
	int R = li(key[2]);

	string output;

	for (unsigned int x = 0; x < zesar.size(); x++) {
		int ct_letter = li(zesar[x]);
		/*повороты роторов*/
		R = mod26(R + 1);//правый ротор
		if (R == li(key[2])) M = mod26(M + 1);//если правый повернулся полностью, повернуть центральный 
		if (M == li(key[1])) L = mod26(L + 1);//если центральный полностью повернулся, повернуть левый
		/*вход в машину*/
		char a = rotors[2][mod26(R + ct_letter)];//правый ротор
		char b = rotors[1][mod26(M + li(a) - R)];//центральный ротор
		char c = rotors[0][mod26(L + li(b) - M)];//левый ротор

		char ref = reflector[mod26(li(c) - L)];//рефлектор
		/*обратный путь*/

		int d = mod26(indexof(rotors[0], alpha[mod26(li(ref) + L)]) - L);//левый
		int e = mod26(indexof(rotors[1], alpha[mod26(d + M)]) - M);//центр 
		char f = alpha[mod26(indexof(rotors[2], alpha[mod26(e + R)]) - R)];//правый (в массиве, где алфавит выбирает получившуюся букву)

		output += f;//цапись закодированной буквы в выходную строку
	}
	zesar = output;
	return zesar;
}

string & Enigma::MethodOfCoding(string & len)
{
	zesar = len;
	return (EnigmaCodingAndDecoding());
}

string & Enigma::MethodOfDecoding(string & len)
{
	zesar = len;
	return (EnigmaCodingAndDecoding());
}

