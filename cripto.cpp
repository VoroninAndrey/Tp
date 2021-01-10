#include "cripto.h"


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

bool cripto::format(string& len)
{
	bool flag = true;
	string s;
	for (unsigned int i = 0; i < len.size(); i++) {
		if (len[i] <= 'Z' && len[i] >= 'A' || len[i] <= 'z' && len[i] >= 'a') {
			if (len[i] <= 'Z' && len[i] >= 'A') len[i] = tolower(len[i]);
			s += len[i];
		}
		else if (len[i] <= 'Я' && len[i] >= 'А' || len[i] <= 'я' && len[i] >= 'а') flag = false;
	}
	len = s;
	return flag;
}





//методы класса Ceasar
string& Ceasar::CaesarCodAndDec(int shift)
{
	
	char c = shift % 26;
	unsigned char code; //вводится переменная с возможным значением 0-255 для того, чтобы смещение не приводило к ситуации, когда символ больше 127
	for (size_t i = 0; i < Cstr.size(); i++) {
		if (Cstr[i] <= 'z' && Cstr[i] >= 'a') {
			code = Cstr[i] + (shift % 26);

			
			if (code > 'z') code -= 26;
			else if (code < 'a') code += 26;
			Cstr[i] = code;
		}
	}
	return Cstr;
}



//методы класса Vishner
string& Vishner::VishnerCoding()
{
	for (size_t i = 0; i < Cstr.size(); i++)
	{
		int c = Cstr[i];
		c += key[i] - 'a';
		if (c > 'z') c -= 26;
		else if (c < 'a') c += 26;
		Cstr[i] = c;
	}
	return Cstr;
}

//методы кодирования-декодирования Вижнера
string& Vishner::VishnerDecoding()
{

	for (size_t i = 0; i < Cstr.size(); i++)
	{
		int c = Cstr[i];
		c -= key[i] - 'a';
		if (c > 'z') c -= 26;
		else if (c < 'a') c += 26;
		Cstr[i] = c;
	}
	return Cstr;
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

	for (unsigned int x = 0; x < Cstr.size(); x++) {
		int ct_letter = li(Cstr[x]);
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
	Cstr = output;
	return Cstr;
}


//методы класса Vishner
string& myCod::MyCoding()
{
	for (size_t i = 0; i < Cstr.size(); i++)
	{
		int c = Cstr[i];
		c += key[i] - 'a';
		if (c > 'z') c -= 26;
		else if (c < 'a') c += 26;
		Cstr[i] = c;
	}
	return Cstr;
}

//методы кодирования-декодирования Вижнера
string& myCod::MyDecoding()
{

	for (size_t i = 0; i < Cstr.size(); i++)
	{
		int c = Cstr[i];
		c -= key[i] - 'a';
		if (c > 'z') c -= 26;
		else if (c < 'a') c += 26;
		Cstr[i] = c;
	}
	return Cstr;
}

bool formatname(string& len)
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
