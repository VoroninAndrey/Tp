// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<iostream>
#pragma warning(disable: 4996)

#include"cripto.h"
using namespace std;
int main(int arg, char* argv[])
{
    setlocale(LC_ALL, "rus");
    WSAData wsaData;                            //структура, нужная для загрузки библиотеки
    WORD DLLVersion = MAKEWORD(2, 1);           //запрашиваемая версия библиотеки winsock
    if (WSAStartup(DLLVersion, &wsaData) != 0)  // функция для загрузки библиотеки
    {
        cerr << "Error #1" << endl;
        exit(1);
    }
    
    SOCKADDR_IN addr;                           //структура, хранящая адрес 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");//задаем адрес структуре sin_addr
    addr.sin_port = htons(1111);                //порт с поступающими данными
    addr.sin_family = AF_INET;                  //семейство протоколов, AF_INET протокол интернет соединения
    //SOCK_STREAM - протокол устанавливающий соединение
    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);//сокет для прослушивания порта

    bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //привязка адреса к сокету

    listen(sListen, SOMAXCONN); // прослушивание порта, второй параметр- макс количество соединений

    int sizeofaddr = sizeof(addr);
    SOCKET connect;                             //сокет для удержания связи а также для передачи данных
    connect = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

    if (connect == 0)
    {
        cerr << "Error #2" << endl;
    }
    cout << "Client Connected!" << endl; 
   
    
    char str[1000];
    memset(str, '\0', 1000);
    char in_method[30];
    int wsError;
    string s;
    while (1)
    {
        recv(connect, in_method, sizeof(in_method), NULL);
        int method = atoi(in_method);
        if (method == 9)break;
       
        
        switch (method)
        {
        case 0: //кодирование методом цезаря
        {
            recv(connect, str, sizeof(str), NULL);
            cripto* C = new Ceasar();
            int shift = 0;
            char intShift[10];
            recv(connect, intShift, sizeof(intShift), NULL);
            shift = atoi(intShift);
            C->setShift(shift);
            s = string(str);
            s = C->Mcoding(s);
            strcpy(str, s.c_str());
            send(connect, str, sizeof(str), NULL);
            delete C;
            break;
        }
        case 1:     //кодирование методом виженера
        {
            recv(connect, str, sizeof(str), NULL);
            cripto* C = new Vishner();

            char Shift[100];
            memset(Shift, '\0', 100);
            recv(connect, Shift, sizeof(Shift), NULL);
            string code = Shift;
            C->setCode(code);
            s = string(str);
            s = C->Mcoding(s);
            strcpy(str, s.c_str());
            send(connect, str, sizeof(str), NULL);
            break;
        }
        case 2:     //кодирование  методом энигма
        {
            recv(connect, str, sizeof(str), NULL);
            cripto* C = new Enigma();
            s = str;
            s = C->Mcoding(s);
            strcpy(str, s.c_str());
            send(connect, str, sizeof(str), NULL);
            break;
        }
        case 3:     //кодирование моим методом 
        {
            recv(connect, str, sizeof(str), NULL);
            cripto* C = new myCod();

            char Shift[1000];
            memset(Shift, '\0', 1000);
            recv(connect, Shift, sizeof(Shift), NULL);
            string code = Shift;
            C->setCode(code);
            s = string(str);
            s = C->Mcoding(s);
            strcpy(str, s.c_str());
            send(connect, str, sizeof(str), NULL);
            break;
        }
        case 4: //декодирование методом цезаря
        {
            recv(connect, str, sizeof(str), NULL);
            cripto* C = new Ceasar();
            int shift = 0;
            char intShift[10]; memset(intShift, '\0', 10);
            recv(connect, intShift, sizeof(intShift), NULL);
            shift = atoi(intShift);
            C->setShift(shift);
            s = string(str);
            s = C->Mdecoding(s);
            strcpy(str, s.c_str());
            send(connect, str, sizeof(str), NULL);
            break;
        }
        case 5:     //декодирование методом виженера
        {
            recv(connect, str, sizeof(str), NULL);
            cripto* C = new Vishner();

            char Shift[100]; memset(Shift, '\0', 100);
            recv(connect, Shift, sizeof(Shift), NULL);
            string code = string(Shift);
            C->setCode(code);
            s = string(str);
            s = C->Mdecoding(s);
            strcpy(str, s.c_str());
            send(connect, str, sizeof(str), NULL);
            break;
        }
        case 6:     // декодирование методом энигма
        {
            recv(connect, str, sizeof(str), NULL);
            cripto* C = new Enigma();
            s = string(str);
            s = C->Mdecoding(s);
            strcpy(str, s.c_str());
            send(connect, str, sizeof(str), NULL);
            break;
        }
        case 7:     // декодирование моим методом 
        {
            recv(connect, str, sizeof(str), NULL);
            cripto* C = new myCod();

            char Shift[1000]; memset(Shift, '\0', 1000);
            recv(connect, Shift, sizeof(Shift), NULL);
            string code = string(Shift);
            C->setCode(code);
            s = string(str);
            s = C->Mdecoding(s);
            strcpy(str, s.c_str());
            send(connect, str, sizeof(str), NULL);
            break;
        }
        default:
        {
            cout << "Error: ошибочный ввод" << endl;

        }

        }
        method = -1;
    }
    closesocket(connect);
    WSACleanup();
    return 0;
}

