#pragma once
#include <iostream>
#include <string>
using namespace std;
class cripto
{
protected:
	string Cstr;
	bool format(string& len);		//метод форматирования строки
	long mod26(long a);				//циклический сдвиг 
	int li(char l);					//возвращает код буквы l
	int indexof(char* array, int find);//вычисление индекса элемента find

public:
	//виртуальные методы кодирования и декодирования
	virtual void setShift(int in) {};
	virtual void setCode(string& in) {};
	virtual string& Mcoding(string& str) = 0;		//в main стоит использовать эту функцию для кодирования 
	virtual string& Mdecoding(string& str) = 0;		//а эту для декодирования, потому что нет смысла на сервере ч.л. выводить в консоль
};


class Ceasar : public cripto
{
	int shift = 0;
	string& CaesarCodAndDec(int shift);
public:
	string& Mcoding(string& str)override
	{
		Cstr = str;
		format(Cstr);
		cout << "Ожидание сдвига..." << endl;
		cout << "Полученный сдвиг " << shift << endl;
		return (CaesarCodAndDec(shift));
	}
	string& Mdecoding(string& len)override
	{
		Cstr = len;
		format(Cstr);
		cout << "Ожидание сдвига..." << endl;
		cout << "Полученный сдвиг " << shift << endl;
		return (CaesarCodAndDec(-1 * shift));
	}
	void setShift(int in)override//метод для установки сдвига
	{
		shift = in;
	}

};


class Vishner : public cripto
{
	string key;
	string code;
protected:
	string& VishnerCoding();
	string& VishnerDecoding();
public:
	string& Mcoding(string& len)override
	{
		Cstr = len;
		format(Cstr);
		cout << "Ожидание кодового слова..." << endl;
		cout << "Получено кодовое слово: " << code << endl;
		getKey();
		return (VishnerCoding());
	}
	string& Mdecoding(string& len)override
	{
		Cstr = len;
		format(Cstr);
		cout << "Ожидание кодового слова..." << endl;
		cout << "Получено кодовое слово: " << code << endl;
		getKey();
		return (VishnerDecoding());
	}
	string& getKey()
	{
		int size = code.size();
		key = Cstr;
		for (size_t k = 0; k < Cstr.size(); k++) {//делаем ключ
			key[k] = code[k % size];
		}
		return key;
	}
	void setCode(string& in)override
	{
		code = in;
	}
	
};

class Enigma : public cripto
{
	
protected:
	string& EnigmaCodingAndDecoding();
public:
	string& Mcoding(string& len)override
	{
		Cstr = len;
		format(Cstr);
		return (EnigmaCodingAndDecoding());
	}
	string& Mdecoding(string& len)override
	{
		Cstr = len;
		format(Cstr);
		return (EnigmaCodingAndDecoding());
	}

};


class myCod : public cripto
{
	
protected:
	string key;
	string& MyCoding();
	string& MyDecoding();
public:
	string& Mcoding(string& len)override
	{
		Cstr = len;
		format(Cstr);
		return (MyCoding());
	}
	string& Mdecoding(string& len)override
	{
		Cstr = len;
		format(Cstr);
		return (MyDecoding());
	}
	void setCode(string& in)override
	{
		key = in;
	}
};


bool formatname(string& len);
