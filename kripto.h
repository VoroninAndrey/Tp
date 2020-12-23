#pragma once
#include <iostream>
bool formatname(string &len);
class cripto //класс направлен на объединение всех методов по кодированию и декодированию 
{
protected:
	string zesar;// рабочая строка для кодинга-декодинга
	bool format(string& len);// функция, удаляющая  лишнее из строки (пробелы, //запятые и пр.)

	long mod26(long a);// циклический сдвиг
	int li(char l);//возвращает код от 0 до 25
	int indexof(char* array, int find);
	cripto() { zesar = "0"; }
public:
	virtual string& MethodOfCoding(string& len) = 0; // абстрактные методы кодирования и декодирования переопределяемый в классах- наследниках
	virtual string& MethodOfDecoding(string& len) = 0;
	//здесь реализован паттерн Шаблонный метод
	void coding(istream& in, ostream& out, bool iflag, bool oflag);// общие методы для каждого класса наследника
	void decoding(istream& in, ostream& out, bool iflag, bool oflag);

};
// класс непосредственно обеспечивающий кодирование и декодирование строки шифром Цезаря
class Ceasar : public cripto 
{
	int shift = 0;
	string& CaesarCodAndDec(int shift);

public:
	Ceasar() { zesar = "0";	
	}
	string& MethodOfCoding(string& len)override;//переделать исключения
	string& MethodOfDecoding(string& len)override;
	

};

// класс непосредственно обеспечивающий кодирование и декодирование строки шифром Виженера
class Vishner : public cripto
{
	string key;
	string code;

protected:
	string& VishnerCoding();
	string& VishnerDecoding();
public:
	Vishner() { zesar = "0";
	code = "0";
	key = "0";
	}
	string& MethodOfCoding(string& len)override;

	string& MethodOfDecoding(string& len)override;
	string& getKey();

};
// класс непосредственно обеспечивающий кодирование и декодирование строки шифром Энигма
class Enigma : public cripto
{
	string code;

protected:
	string& EnigmaCodingAndDecoding();
public:
	Enigma() { zesar = "0"; }
	string& MethodOfCoding(string& len)override;
	string& MethodOfDecoding(string& len)override;
	

};
