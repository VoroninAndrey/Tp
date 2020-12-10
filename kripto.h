#pragma once
#include <iostream>
bool formatname(string &len);
class cripto //класс направлен на объединение всех методов по кодированию и декодированию 
{
protected:
	string zesar;
	bool format(string& len);

	long mod26(long a);
	int li(char l);
	int indexof(char* array, int find);
	cripto() { zesar = "0"; }
public:
	virtual string& MethodOfCoding(string& len) = 0;
	virtual string& MethodOfDecoding(string& len) = 0;
	//здесь реализован паттерн Шаблонный метод
	void coding(istream& in, ostream& out, bool iflag, bool oflag);
	void decoding(istream& in, ostream& out, bool iflag, bool oflag);

};

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
