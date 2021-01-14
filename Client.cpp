#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<iostream>
#include<cstdlib>
#include<SDL.h>
#include<SDL_ttf.h>
#include<ctime>
#include<sstream>
#pragma warning(disable: 4996)
#include<cstdio>
#include<Windows.h>
#include<string>

using namespace std;
//================================================ глобалы ==============================================

SDL_Surface* screen_surface = NULL;
SDL_Window* window = NULL;
SDL_Surface* text = NULL;

 char* composition;
 Sint32 cursor;
 Sint32 selection_len;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool done = false;      //флаг завершения работы
bool mode = false;      //флаг режима

SDL_Event event;
SDL_Surface* menu;
SDL_Rect bg_menu;
TTF_Font* font;

string namef;           //имя файла
FILE* fin;           //входной файл
FILE* fout;           //выходной файл
char s[1000]; char c = 0;
char res[1000];

SDL_Rect ishift_pos;            //позиция поля смещения
SDL_Surface* IShift;

SDL_Rect string_pos;            //строка с полем вводимой строки, то есть ее позиция
SDL_Surface* IString;           //строка с полем видимой строки, аля стикер

SDL_Rect cCesarButton_pos;      //параметры кнопки К.Ш.Цезаря
SDL_Surface* cCesarButton;      //

SDL_Rect cVishnerButton_pos;    //Параметры кнопки К.Ш.Виженера
SDL_Surface* cVishnerButton;    //

SDL_Rect cEnigmaButton_pos;     //Параметры кнопки К.Ш. Энигмы
SDL_Surface* cEnigmaButton;     //

SDL_Rect cMyButton_pos;         //Параметры кнопки К.Ш.Моим
SDL_Surface* cMyButton;         //

SDL_Rect dCesarButton_pos;      //параметры кнопки К.Ш.Цезаря
SDL_Surface* dCesarButton;      //

SDL_Rect dVishnerButton_pos;    //Параметры кнопки К.Ш.Виженера
SDL_Surface* dVishnerButton;    //

SDL_Rect dEnigmaButton_pos;     //Параметры кнопки К.Ш. Энигмы
SDL_Surface* dEnigmaButton;     //

SDL_Rect dMyButton_pos;         //Параметры кнопки К.Ш.Моим
SDL_Surface* dMyButton;         //

SDL_Rect GetResButton_pos;         //Параметры кнопки К.Ш.Моим
SDL_Surface* GetResButton;         //

SDL_Rect ExitBtn_pos;         //Параметры кнопки К.Ш.Моим
SDL_Surface* ExitBtn;         //

SDL_Rect input_file_pos;         //поле входного файла
SDL_Surface* input_file;         //

SDL_Rect output_file_pos;         //поле выходного файла
SDL_Surface* output_file;

SDL_Rect output_pos;         //поле выходного файла
SDL_Surface* output;

string input_shift = "";
string input_string = "";
string output_string = "";
string input_file_str = "";
string output_file_str = "";


SDL_Color Black = { 0,0,0 };
SDL_Color Grey = { 190,190,190 };
SDL_Color White = { 255,255,255 };
// =========================================== функции ==================================================
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
int len_s(char* str)
{
    unsigned int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}
bool init(void)
{
    //включение SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        return 0;
    }
    window = SDL_CreateWindow("MyApp", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (window == NULL) {
        return 0;
    }
    screen_surface = SDL_GetWindowSurface(window);
    if (TTF_Init() == -1) return 0;

    return 1;
}
void load(void)
{
    memset(res, '\0', 1000);
    memset(s, '\0', 1000);
    menu = SDL_LoadBMP("menup.bmp");
    SDL_BlitSurface(menu, NULL, screen_surface, &bg_menu);
    SDL_UpdateWindowSurface(window);
   
    //поле ввода смещение
    ishift_pos.w = 435;
    ishift_pos.h = 31;
    ishift_pos.x = 185;
    ishift_pos.y = 64;
    //прямоугольник кноки КШ Цезаря
    cCesarButton_pos.w = 141;
    cCesarButton_pos.h = 33;
    cCesarButton_pos.x = 25;
    cCesarButton_pos.y = 35;
    //прямоугольник кноки КШ Виженера
    cVishnerButton_pos.w = 141;
    cVishnerButton_pos.h = 33;
    cVishnerButton_pos.x = 25;
    cVishnerButton_pos.y = 79;

    //прямоугольник кноки КШ Энигмы
    cEnigmaButton_pos.w = 141;
    cEnigmaButton_pos.h = 33;
    cEnigmaButton_pos.x = 25;
    cEnigmaButton_pos.y = 124;

    //прямоугольник кноки КШ Моим
    cMyButton_pos.w = 141;
    cMyButton_pos.h = 33;
    cMyButton_pos.x = 25;
    cMyButton_pos.y = 174;

    //прямоугольник кноки ДШ Цезаря
    dCesarButton_pos.w = 141;
    dCesarButton_pos.h = 33;
    dCesarButton_pos.x = 25;
    dCesarButton_pos.y = 222;
    //прямоугольник кноки ДШ Виженера
    dVishnerButton_pos.w = 141;
    dVishnerButton_pos.h = 33;
    dVishnerButton_pos.x = 25;
    dVishnerButton_pos.y = 270;

    //прямоугольник кноки ДШ Энигмы
    dEnigmaButton_pos.w = 141;
    dEnigmaButton_pos.h = 33;
    dEnigmaButton_pos.x = 25;
    dEnigmaButton_pos.y = 314;

    //прямоугольник кноки ДШ Моим
    dMyButton_pos.w = 141;
    dMyButton_pos.h = 33;
    dMyButton_pos.x = 25;
    dMyButton_pos.y = 359;

    //прямоугольник кноки получить результат
    GetResButton_pos.w = 236;
    GetResButton_pos.h = 38;
    GetResButton_pos.x = 256;
    GetResButton_pos.y = 220;

    //прямоугольник кноки вывода
    output_pos.w = 436;
    output_pos.h = 31;
    output_pos.x = 190;
    output_pos.y = 370;

    //прямоугольник кноки выхода
    ExitBtn_pos.w = 141;
    ExitBtn_pos.h = 33;
    ExitBtn_pos.x = 25;
    ExitBtn_pos.y = 409;

    //позиция меню
    bg_menu.w = SCREEN_WIDTH;
    bg_menu.h = SCREEN_HEIGHT;
    bg_menu.x = 0;
    bg_menu.y = 0;

    //позиция поля ввода кодируемой строки
    string_pos.w = 434;
    string_pos.h = 31;
    string_pos.x = 184;
    string_pos.y = 162;


    font = TTF_OpenFont("ArialRegular.ttf", 18);
    
    // инициализация поля ввода смещения или кода
    IShift = TTF_RenderText_Solid(font, input_shift.c_str(), Black);
    SDL_SetClipRect(IShift, &ishift_pos);
    SDL_BlitSurface(IShift, NULL, screen_surface, &ishift_pos);
  
    // инициализация поля ввода кодируемой строки
    IString = TTF_RenderText_Solid(font, input_string.c_str(), Black);
    SDL_SetClipRect(IString, &string_pos);
    SDL_BlitSurface(IString, NULL, screen_surface, &string_pos);

    // кнопка кодирования шифром цезаря
    cCesarButton = TTF_RenderText_Solid(font, "E.C.Cesar", Black);
    SDL_SetClipRect(cCesarButton, &cCesarButton_pos);
    SDL_BlitSurface(cCesarButton, NULL, screen_surface, &cCesarButton_pos);

    //кнопка кодирования шифром виженера
    cVishnerButton = TTF_RenderText_Solid(font, "E.C.Visner", Black);
    SDL_SetClipRect(cVishnerButton, &cVishnerButton_pos);
    SDL_BlitSurface(cVishnerButton, NULL, screen_surface, &cVishnerButton_pos);

    //кнопка кодирования шифром энигмы
    cEnigmaButton = TTF_RenderText_Solid(font, "E.C.Enigma", Black);
    SDL_SetClipRect(cEnigmaButton, &cEnigmaButton_pos);
    SDL_BlitSurface(cEnigmaButton, NULL, screen_surface, &cEnigmaButton_pos);

    //кнопка декодирования моим шифром
    cMyButton = TTF_RenderText_Solid(font, "E.C.MyCoding", Black);
    SDL_SetClipRect(cMyButton, &cMyButton_pos);
    SDL_BlitSurface(cMyButton, NULL, screen_surface, &cMyButton_pos);

    //кнопка декодирования шифром цезаря
    dCesarButton = TTF_RenderText_Solid(font, "D.C.Cesar", Black);
    SDL_SetClipRect(dCesarButton, &dCesarButton_pos);
    SDL_BlitSurface(dCesarButton, NULL, screen_surface, &dCesarButton_pos);

    //кнопка декодирования шифром виженера
    dVishnerButton = TTF_RenderText_Solid(font, "D.C.Visner", Black);
    SDL_SetClipRect(dVishnerButton, &dVishnerButton_pos);
    SDL_BlitSurface(dVishnerButton, NULL, screen_surface, &dVishnerButton_pos);

    //кнопка декодирования шифром кодирования
    dEnigmaButton = TTF_RenderText_Solid(font, "D.C.Enigma", Black);
    SDL_SetClipRect(dEnigmaButton, &dEnigmaButton_pos);
    SDL_BlitSurface(dEnigmaButton, NULL, screen_surface, &dEnigmaButton_pos);

    //кнопка декодирования моим кодом
    dMyButton = TTF_RenderText_Solid(font, "D.C.MyCoding", Black);
    SDL_SetClipRect(dMyButton, &dMyButton_pos);
    SDL_BlitSurface(dMyButton, NULL, screen_surface, &dMyButton_pos);

    ExitBtn = TTF_RenderText_Solid(font, "Exit", Black);
    SDL_SetClipRect(ExitBtn, &ExitBtn_pos);
    SDL_BlitSurface(ExitBtn, NULL, screen_surface, &ExitBtn_pos);

    SDL_UpdateWindowSurface(window);

}
void loadFilemode(void)
{
    memset(res, '\0', 1000);
    memset(s, '\0', 1000);
    menu = SDL_LoadBMP("menuf.bmp");
    SDL_BlitSurface(menu, NULL, screen_surface, &bg_menu);
    SDL_UpdateWindowSurface(window);

    //поле ввода смещение
    ishift_pos.w = 435;
    ishift_pos.h = 31;
    ishift_pos.x = 185;
    ishift_pos.y = 64;
    //прямоугольник кноки КШ Цезаря
    cCesarButton_pos.w = 141;
    cCesarButton_pos.h = 33;
    cCesarButton_pos.x = 25;
    cCesarButton_pos.y = 35;
    //прямоугольник кноки КШ Виженера
    cVishnerButton_pos.w = 141;
    cVishnerButton_pos.h = 33;
    cVishnerButton_pos.x = 25;
    cVishnerButton_pos.y = 79;

    //прямоугольник кноки КШ Энигмы
    cEnigmaButton_pos.w = 141;
    cEnigmaButton_pos.h = 33;
    cEnigmaButton_pos.x = 25;
    cEnigmaButton_pos.y = 124;

    //прямоугольник кноки КШ Моим
    cMyButton_pos.w = 141;
    cMyButton_pos.h = 33;
    cMyButton_pos.x = 25;
    cMyButton_pos.y = 174;

    //прямоугольник кноки ДШ Цезаря
    dCesarButton_pos.w = 141;
    dCesarButton_pos.h = 33;
    dCesarButton_pos.x = 25;
    dCesarButton_pos.y = 222;
    //прямоугольник кноки ДШ Виженера
    dVishnerButton_pos.w = 141;
    dVishnerButton_pos.h = 33;
    dVishnerButton_pos.x = 25;
    dVishnerButton_pos.y = 270;

    //прямоугольник кноки ДШ Энигмы
    dEnigmaButton_pos.w = 141;
    dEnigmaButton_pos.h = 33;
    dEnigmaButton_pos.x = 25;
    dEnigmaButton_pos.y = 314;

    //прямоугольник кноки ДШ Моим
    dMyButton_pos.w = 141;
    dMyButton_pos.h = 33;
    dMyButton_pos.x = 25;
    dMyButton_pos.y = 359;

    //прямоугольник кноки получить результат
    GetResButton_pos.w = 236;
    GetResButton_pos.h = 38;
    GetResButton_pos.x = 256;
    GetResButton_pos.y = 220;

    //прямоугольник кноки вывода
    output_pos.w = 436;
    output_pos.h = 31;
    output_pos.x = 190;
    output_pos.y = 370;

    //прямоугольник кноки выхода
    ExitBtn_pos.w = 141;
    ExitBtn_pos.h = 33;
    ExitBtn_pos.x = 25;
    ExitBtn_pos.y = 409;

    //позиция меню
    bg_menu.w = SCREEN_WIDTH;
    bg_menu.h = SCREEN_HEIGHT;
    bg_menu.x = 0;
    bg_menu.y = 0;

    //позиция поля ввода входного файла
    input_file_pos.w = 170;
    input_file_pos.h = 28;
    input_file_pos.x = 187;
    input_file_pos.y = 160;

    //позиция поля ввода выходного файла
    output_file_pos.w = 198;
    output_file_pos.h = 29;
    output_file_pos.x = 383;
    output_file_pos.y = 160;

    font = TTF_OpenFont("ArialRegular.ttf", 18);

    // инициализация поля ввода смещения или кода
    IShift = TTF_RenderText_Solid(font, input_shift.c_str(), Black);
    SDL_SetClipRect(IShift, &ishift_pos);
    SDL_BlitSurface(IShift, NULL, screen_surface, &ishift_pos);

    // инициализация поля ввода кодируемой строки
    IString = TTF_RenderText_Solid(font, input_string.c_str(), Black);
    SDL_SetClipRect(IString, &string_pos);
    SDL_BlitSurface(IString, NULL, screen_surface, &string_pos);

    // кнопка кодирования шифром цезаря
    cCesarButton = TTF_RenderText_Solid(font, "E.C.Cesar", Black);
    SDL_SetClipRect(cCesarButton, &cCesarButton_pos);
    SDL_BlitSurface(cCesarButton, NULL, screen_surface, &cCesarButton_pos);

    //кнопка кодирования шифром виженера
    cVishnerButton = TTF_RenderText_Solid(font, "E.C.Visner", Black);
    SDL_SetClipRect(cVishnerButton, &cVishnerButton_pos);
    SDL_BlitSurface(cVishnerButton, NULL, screen_surface, &cVishnerButton_pos);

    //кнопка кодирования шифром энигмы
    cEnigmaButton = TTF_RenderText_Solid(font, "E.C.Enigma", Black);
    SDL_SetClipRect(cEnigmaButton, &cEnigmaButton_pos);
    SDL_BlitSurface(cEnigmaButton, NULL, screen_surface, &cEnigmaButton_pos);

    //кнопка декодирования моим шифром
    cMyButton = TTF_RenderText_Solid(font, "E.C.MyCoding", Black);
    SDL_SetClipRect(cMyButton, &cMyButton_pos);
    SDL_BlitSurface(cMyButton, NULL, screen_surface, &cMyButton_pos);

    //кнопка декодирования шифром цезаря
    dCesarButton = TTF_RenderText_Solid(font, "D.C.Cesar", Black);
    SDL_SetClipRect(dCesarButton, &dCesarButton_pos);
    SDL_BlitSurface(dCesarButton, NULL, screen_surface, &dCesarButton_pos);

    //кнопка декодирования шифром виженера
    dVishnerButton = TTF_RenderText_Solid(font, "D.C.Visner", Black);
    SDL_SetClipRect(dVishnerButton, &dVishnerButton_pos);
    SDL_BlitSurface(dVishnerButton, NULL, screen_surface, &dVishnerButton_pos);

    //кнопка декодирования шифром кодирования
    dEnigmaButton = TTF_RenderText_Solid(font, "D.C.Enigma", Black);
    SDL_SetClipRect(dEnigmaButton, &dEnigmaButton_pos);
    SDL_BlitSurface(dEnigmaButton, NULL, screen_surface, &dEnigmaButton_pos);

    //кнопка декодирования моим кодом
    dMyButton = TTF_RenderText_Solid(font, "D.C.MyCoding", Black);
    SDL_SetClipRect(dMyButton, &dMyButton_pos);
    SDL_BlitSurface(dMyButton, NULL, screen_surface, &dMyButton_pos);

    ExitBtn = TTF_RenderText_Solid(font, "Exit", Black);
    SDL_SetClipRect(ExitBtn, &ExitBtn_pos);
    SDL_BlitSurface(ExitBtn, NULL, screen_surface, &ExitBtn_pos);

    SDL_UpdateWindowSurface(window);

}
bool change_stream(void)
{
    SDL_Window* change_menu = SDL_CreateWindow("Change Node,bro", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 421, 79,
        SDL_WINDOW_SHOWN);
    if (change_menu == NULL) {
        exit(1);
    }
    SDL_Rect menu_pos;
    menu_pos.w = 421;
    menu_pos.h = 79;
    menu_pos.x = 0;
    menu_pos.y = 0;
    SDL_Surface* scr = SDL_GetWindowSurface(change_menu);
    SDL_Surface* scr_menu = SDL_LoadBMP("changeStream.bmp");
    SDL_BlitSurface(scr_menu, NULL, scr, &menu_pos);
    SDL_UpdateWindowSurface(change_menu);
    bool done_c = false;
    bool mode = false;
    while (!done_c)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
            case SDL_QUIT:
                /* Quit */
                done_c = true;
                break;
           
            case SDL_MOUSEBUTTONDOWN:
            {
                if (event.button.x < 364 && event.button.y < 66 && event.button.x > 212 && event.button.y > 44) //режим мода работы с кансолью
                {
                    
                    done_c = true;
                }
                else if (event.button.x < 103 && event.button.y < 64 && event.button.x > 13 && event.button.y > 43)//режим работы с файлами
                {
                    mode = true;
                    done_c = true;
                }
                break;
            }
            }
        }

    }


    SDL_FreeSurface(scr);
    SDL_FreeSurface(scr_menu);
    SDL_DestroyWindow(change_menu);
    return mode;

}
void update(void)
{
    
    SDL_BlitSurface(menu, NULL, screen_surface, &bg_menu);
    // инициализация поля ввода смещения или кода
    IShift = TTF_RenderText_Solid(font, input_shift.c_str(), Black);
    SDL_SetClipRect(IShift, &ishift_pos);
    SDL_BlitSurface(IShift, NULL, screen_surface, &ishift_pos);

    // инициализация поля ввода кодируемой строки
    IString = TTF_RenderText_Solid(font, input_string.c_str(), Black);
    SDL_SetClipRect(IString, &string_pos);
    SDL_BlitSurface(IString, NULL, screen_surface, &string_pos);

    // кнопка кодирования шифром цезаря
    cCesarButton = TTF_RenderText_Solid(font, "E.C.Cesar", Black);
    SDL_SetClipRect(cCesarButton, &cCesarButton_pos);
    SDL_BlitSurface(cCesarButton, NULL, screen_surface, &cCesarButton_pos);

    //кнопка кодирования шифром виженера
    cVishnerButton = TTF_RenderText_Solid(font, "E.C.Visner", Black);
    SDL_SetClipRect(cVishnerButton, &cVishnerButton_pos);
    SDL_BlitSurface(cVishnerButton, NULL, screen_surface, &cVishnerButton_pos);

    //кнопка кодирования шифром энигмы
    cEnigmaButton = TTF_RenderText_Solid(font, "E.C.Enigma", Black);
    SDL_SetClipRect(cEnigmaButton, &cEnigmaButton_pos);
    SDL_BlitSurface(cEnigmaButton, NULL, screen_surface, &cEnigmaButton_pos);

    //кнопка декодирования моим шифром
    cMyButton = TTF_RenderText_Solid(font, "E.C.MyCoding", Black);
    SDL_SetClipRect(cMyButton, &cMyButton_pos);
    SDL_BlitSurface(cMyButton, NULL, screen_surface, &cMyButton_pos);

    //кнопка декодирования шифром цезаря
    dCesarButton = TTF_RenderText_Solid(font, "D.C.Cesar", Black);
    SDL_SetClipRect(dCesarButton, &dCesarButton_pos);
    SDL_BlitSurface(dCesarButton, NULL, screen_surface, &dCesarButton_pos);

    //кнопка декодирования шифром виженера
    dVishnerButton = TTF_RenderText_Solid(font, "D.C.Visner", Black);
    SDL_SetClipRect(dVishnerButton, &dVishnerButton_pos);
    SDL_BlitSurface(dVishnerButton, NULL, screen_surface, &dVishnerButton_pos);

    //кнопка декодирования шифром кодирования
    dEnigmaButton = TTF_RenderText_Solid(font, "D.C.Enigma", Black);
    SDL_SetClipRect(dEnigmaButton, &dEnigmaButton_pos);
    SDL_BlitSurface(dEnigmaButton, NULL, screen_surface, &dEnigmaButton_pos);

    //кнопка декодирования моим кодом
    dMyButton = TTF_RenderText_Solid(font, "D.C.MyCoding", Black);
    SDL_SetClipRect(dMyButton, &dMyButton_pos);
    SDL_BlitSurface(dMyButton, NULL, screen_surface, &dMyButton_pos);

    ExitBtn = TTF_RenderText_Solid(font, "Exit", Black);
    SDL_SetClipRect(ExitBtn, &ExitBtn_pos);
    SDL_BlitSurface(ExitBtn, NULL, screen_surface, &ExitBtn_pos);

    output = TTF_RenderText_Solid(font, res, Black);
    SDL_SetClipRect(output, &output_pos);
    SDL_BlitSurface(output, NULL, screen_surface, &output_pos);

    SDL_UpdateWindowSurface(window);

}
void updateFilemode(void)
{

    SDL_BlitSurface(menu, NULL, screen_surface, &bg_menu);
    // инициализация поля ввода смещения или кода
    IShift = TTF_RenderText_Solid(font, input_shift.c_str(), Black);
    SDL_SetClipRect(IShift, &ishift_pos);
    SDL_BlitSurface(IShift, NULL, screen_surface, &ishift_pos);

    // инициализация поля ввода входного файла
    input_file = TTF_RenderText_Solid(font, input_file_str.c_str(), Black);
    SDL_SetClipRect(input_file, &input_file_pos);
    SDL_BlitSurface(input_file, NULL, screen_surface, &input_file_pos);

    // инициализация поля ввода выходного файла
    output_file = TTF_RenderText_Solid(font, output_file_str.c_str(), Black);
    SDL_SetClipRect(output_file, &output_file_pos);
    SDL_BlitSurface(output_file, NULL, screen_surface, &output_file_pos);

    // кнопка кодирования шифром цезаря
    cCesarButton = TTF_RenderText_Solid(font, "E.C.Cesar", Black);
    SDL_SetClipRect(cCesarButton, &cCesarButton_pos);
    SDL_BlitSurface(cCesarButton, NULL, screen_surface, &cCesarButton_pos);

    //кнопка кодирования шифром виженера
    cVishnerButton = TTF_RenderText_Solid(font, "E.C.Visner", Black);
    SDL_SetClipRect(cVishnerButton, &cVishnerButton_pos);
    SDL_BlitSurface(cVishnerButton, NULL, screen_surface, &cVishnerButton_pos);

    //кнопка кодирования шифром энигмы
    cEnigmaButton = TTF_RenderText_Solid(font, "E.C.Enigma", Black);
    SDL_SetClipRect(cEnigmaButton, &cEnigmaButton_pos);
    SDL_BlitSurface(cEnigmaButton, NULL, screen_surface, &cEnigmaButton_pos);

    //кнопка декодирования моим шифром
    cMyButton = TTF_RenderText_Solid(font, "E.C.MyCoding", Black);
    SDL_SetClipRect(cMyButton, &cMyButton_pos);
    SDL_BlitSurface(cMyButton, NULL, screen_surface, &cMyButton_pos);

    //кнопка декодирования шифром цезаря
    dCesarButton = TTF_RenderText_Solid(font, "D.C.Cesar", Black);
    SDL_SetClipRect(dCesarButton, &dCesarButton_pos);
    SDL_BlitSurface(dCesarButton, NULL, screen_surface, &dCesarButton_pos);

    //кнопка декодирования шифром виженера
    dVishnerButton = TTF_RenderText_Solid(font, "D.C.Visner", Black);
    SDL_SetClipRect(dVishnerButton, &dVishnerButton_pos);
    SDL_BlitSurface(dVishnerButton, NULL, screen_surface, &dVishnerButton_pos);

    //кнопка декодирования шифром кодирования
    dEnigmaButton = TTF_RenderText_Solid(font, "D.C.Enigma", Black);
    SDL_SetClipRect(dEnigmaButton, &dEnigmaButton_pos);
    SDL_BlitSurface(dEnigmaButton, NULL, screen_surface, &dEnigmaButton_pos);

    //кнопка декодирования моим кодом
    dMyButton = TTF_RenderText_Solid(font, "D.C.MyCoding", Black);
    SDL_SetClipRect(dMyButton, &dMyButton_pos);
    SDL_BlitSurface(dMyButton, NULL, screen_surface, &dMyButton_pos);

    ExitBtn = TTF_RenderText_Solid(font, "Exit", Black);
    SDL_SetClipRect(ExitBtn, &ExitBtn_pos);
    SDL_BlitSurface(ExitBtn, NULL, screen_surface, &ExitBtn_pos);

    output = TTF_RenderText_Solid(font, output_string.c_str(), Black);
    SDL_SetClipRect(output, &output_pos);
    SDL_BlitSurface(output, NULL, screen_surface, &output_pos);

    SDL_UpdateWindowSurface(window);

}
bool quit(void)
{
    SDL_Delay(2000);
    SDL_FreeSurface(IShift);
    SDL_FreeSurface(IString);
    SDL_FreeSurface(cCesarButton);
    SDL_FreeSurface(cVishnerButton);
    SDL_FreeSurface(cEnigmaButton);
    SDL_FreeSurface(cMyButton);
    SDL_FreeSurface(dCesarButton);
    SDL_FreeSurface(dVishnerButton);
    SDL_FreeSurface(dEnigmaButton);
    SDL_FreeSurface(dMyButton);
    SDL_FreeSurface(GetResButton);
    SDL_FreeSurface(ExitBtn);
    SDL_FreeSurface(output);
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    return 0;
}
// =========================================== реализация функций =======================================

int main(int arg, char* argv[])
{
    setlocale(LC_ALL, "rus");
   
    //========================================= инициализация сокетов и портов =========================
    //включение подключения к сервису
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


    SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);//используется для передачи и принятия данных
    if (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        cerr << "Error: failed connect to server..." << endl;
        return 1;
    }

    init();
   
    mode = change_stream();
    if (mode == false)
    {
        load();
    }
    else
    {
        loadFilemode();
    }
    int flag_input = 0;
    if (mode == false)
    {
        while (!done)
        {
            while (SDL_PollEvent(&event))
            {
                switch (event.type) {
                case SDL_QUIT:
                    /* Quit */
                    done = true;
                    break;
                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_BACKSPACE)
                    {
                        if (input_shift.size() > 0 && flag_input == 1)
                        {
                            input_shift.pop_back();
                            IShift = TTF_RenderText_Solid(font, input_shift.c_str(), Black);
                        }
                        if (input_string.size() > 0 && flag_input == 2)
                        {
                            input_string.pop_back();
                            IString = TTF_RenderText_Solid(font, input_string.c_str(), Black);
                        }
                    }

                    break;
                }
                case SDL_TEXTINPUT:
                {

                    if (flag_input == 1)
                    {
                        input_shift += event.text.text;
                        IShift = TTF_RenderText_Solid(font, input_shift.c_str(), Black);
                        update();
                    }
                    if (flag_input == 2)
                    {
                        input_string += event.text.text;
                        IString = TTF_RenderText_Solid(font, input_string.c_str(), Black);
                        update();
                    }

                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    if (event.button.x < 620 && event.button.y < 95 && event.button.x > 185 && event.button.y > 64)
                    {
                        SDL_StartTextInput();
                        flag_input = 1;
                    }
                    else if (event.button.x < 620 && event.button.y < 193 && event.button.x > 185 && event.button.y > 162)
                    {
                        SDL_StartTextInput();
                        flag_input = 2;
                    }
                    else if (event.button.x > 26 && event.button.y > 35 && event.button.x < 165 && event.button.y < 67)//кодирование шифром цезаря
                    {
                        c = '0';
                    }
                    else if (event.button.x > 26 && event.button.y > 81 && event.button.x < 165 && event.button.y < 112)//кодирование шифром виженера
                    {
                        c = '1';
                    }
                    else if (event.button.x > 26 && event.button.y > 124 && event.button.x < 165 && event.button.y < 157)//кодирование шифром энигмы
                    {
                        c = '2';
                    }
                    else if (event.button.x > 26 && event.button.y > 174 && event.button.x < 165 && event.button.y < 207)//кодирование моим шифром
                    {
                        c = '3';
                    }
                    else if (event.button.x > 26 && event.button.y > 222 && event.button.x < 165 && event.button.y < 254)//декодирование шифром цезаря
                    {
                        c = '4';
                    }
                    else if (event.button.x > 26 && event.button.y > 270 && event.button.x < 165 && event.button.y < 303)//декодирование шифра виженера
                    {
                        c = '5';
                    }
                    else if (event.button.x > 26 && event.button.y > 315 && event.button.x < 165 && event.button.y < 348)//декодирование шифра энигмы
                    {
                        c = '6';
                    }
                    else if (event.button.x > 26 && event.button.y > 360 && event.button.x < 165 && event.button.y < 392)// декодирование моего шифра
                    {
                        c = '7';
                    }
                    else if (event.button.x > 26 && event.button.y > 408 && event.button.x < 165 && event.button.y < 442)//выход
                    {
                        c = '9';
                        send(connection, &c, 1, NULL);
                        done = true;
                    }
                    else if (event.button.x > 257 && event.button.y > 220 && event.button.x < 492 && event.button.y < 258)//получение результата
                    {
                        // проверка на пустую строку со смещением
                        if ((c == '0' || c == '1' || c == '4' || c == '5') && input_shift.empty())
                        {
                            SDL_Window* error = SDL_CreateWindow("Error", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, 400, 30,
                                SDL_WINDOW_SHOWN);
                            SDL_Surface* scr = SDL_GetWindowSurface(error);
                            SDL_Surface* scr_error = SDL_LoadBMP("errShift.bmp");

                            SDL_Rect err_pos;
                            err_pos.x = 0;
                            err_pos.y = 0;
                            err_pos.h = 30;
                            err_pos.w = 400;
                            SDL_SetClipRect(scr_error, &err_pos);
                            SDL_BlitSurface(scr_error, NULL, scr, &err_pos);
                            SDL_UpdateWindowSurface(error);
                            SDL_Delay(1500);
                            SDL_FreeSurface(scr);
                            SDL_FreeSurface(scr_error);
                            SDL_DestroyWindow(error);
                            continue;
                        }
                        //проверка на пустую кодируемую строку
                        if (input_string.empty())
                        {
                            SDL_Window* error = SDL_CreateWindow("Error", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, 400, 30,
                                SDL_WINDOW_SHOWN);
                            SDL_Surface* scr = SDL_GetWindowSurface(error);
                            SDL_Surface* scr_error = SDL_LoadBMP("errString.bmp");

                            SDL_Rect err_pos;
                            err_pos.x = 0;
                            err_pos.y = 0;
                            err_pos.h = 30;
                            err_pos.w = 400;
                            SDL_SetClipRect(scr_error, &err_pos);
                            SDL_BlitSurface(scr_error, NULL, scr, &err_pos);
                            SDL_UpdateWindowSurface(error);
                            SDL_Delay(1500);
                            SDL_FreeSurface(scr);
                            SDL_FreeSurface(scr_error);
                            SDL_DestroyWindow(error);
                            continue;
                        }

                        send(connection, &c, 1, NULL);
                        strcpy(s, input_string.c_str());
                        send(connection, s, sizeof(s), NULL);
                        //в случае если работаем с Виженером или Цезарем, тогда отправляем код/смещение 
                        if (c == '0' || c == '1' || c == '4' || c == '5')
                        {
                            strcpy(s, input_shift.c_str());
                            send(connection, input_shift.c_str(), input_shift.size(), NULL);
                        }
                        //отдельная ситуация- мое шифрование, тогда мы генерируем ключ и только после этого его отправляем
                        if (c == '3')
                        {
                            FILE* fkey = fopen("key.txt", "w");
                            for (unsigned int i = 0; i < len_s(s); i++)
                            {
                                char c = rand() % 26;
                                fputc(c + 'a', fkey);
                            }
                            fputc('\n', fkey);
                            fclose(fkey);
                            fkey = fopen("key.txt", "r");
                            fgets(s, 1000, fkey);
                            fclose(fkey);
                            send(connection, s, sizeof(s), NULL);
                        }
                        if (c == '7')
                        {
                            FILE* fkey = fopen("key.txt", "r");
                            fgets(s, 1000, fkey);
                            fclose(fkey);
                            send(connection, s, sizeof(s), NULL);
                        }
                        recv(connection, res, sizeof(res), NULL);
                        output_string = string(res);


                    }
                    //при нажатии мышкой на кнопку с методом кодирования-декодирования в строку выбора метода (c) заносится цифра метода
                    //после чего как будут заполнены все данные при нажатии получить результат скидывается сначала c, потом кодируемая строка, потом смещение если есть и получается результат
                    //который в поле для вывода выводится
                    else
                    {
                        SDL_StopTextInput();
                        flag_input = 0;
                    }
                    break;
                }
                }
                update();
            }

        }
    }
    else
    {
        while (!done)
        {
            while (SDL_PollEvent(&event))
            {
                switch (event.type) {
                case SDL_QUIT:
                    /* Quit */
                    done = true;
                    break;
                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_BACKSPACE)
                    {
                        if (input_shift.size() > 0 && flag_input == 1)
                        {
                            input_shift.pop_back();
                            IShift = TTF_RenderText_Solid(font, input_shift.c_str(), Black);
                        }
                        if (input_file_str.size() > 0 && flag_input == 2)
                        {
                            input_file_str.pop_back();
                            IString = TTF_RenderText_Solid(font, input_file_str.c_str(), Black);
                        }
                        if (output_file_str.size() > 0 && flag_input == 3)
                        {
                            output_file_str.pop_back();
                            IString = TTF_RenderText_Solid(font, output_file_str.c_str(), Black);
                        }
                    }
                    break;
                }
                case SDL_TEXTINPUT:
                {
                    if (flag_input == 1)
                    {
                        input_shift += event.text.text;
                        IShift = TTF_RenderText_Solid(font, input_shift.c_str(), Black);
                        updateFilemode();
                    }
                    if (flag_input == 2)
                    {
                        input_file_str += event.text.text;
                        IString = TTF_RenderText_Solid(font, input_file_str.c_str(), Black);
                        updateFilemode();
                    }
                    if (flag_input == 3)
                    {
                        output_file_str += event.text.text;
                        IString = TTF_RenderText_Solid(font, output_file_str.c_str(), Black);
                        updateFilemode();
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    if (event.button.x < 620 && event.button.y < 95 && event.button.x > 185 && event.button.y > 64)
                    {
                        SDL_StartTextInput();
                        flag_input = 1;
                        output_string = "";
                    }
                    else if (event.button.x < 357 && event.button.y < 188 && event.button.x > 187 && event.button.y > 160)
                    {
                        SDL_StartTextInput();
                        flag_input = 2;
                        output_string = "";
                    }
                    else if (event.button.x < 581 && event.button.y < 190 && event.button.x > 383 && event.button.y > 161)
                    {
                        SDL_StartTextInput();
                        flag_input = 3;
                        output_string = "";
                    }
                    else if (event.button.x > 26 && event.button.y > 35 && event.button.x < 165 && event.button.y < 67)//кодирование шифром цезаря
                    {
                        c = '0';
                    }
                    else if (event.button.x > 26 && event.button.y > 81 && event.button.x < 165 && event.button.y < 112)//кодирование шифром виженера
                    {
                        c = '1';
                    }
                    else if (event.button.x > 26 && event.button.y > 124 && event.button.x < 165 && event.button.y < 157)//кодирование шифром энигмы
                    {
                        c = '2';
                    }
                    else if (event.button.x > 26 && event.button.y > 174 && event.button.x < 165 && event.button.y < 207)//кодирование моим шифром
                    {
                        c = '3';
                    }
                    else if (event.button.x > 26 && event.button.y > 222 && event.button.x < 165 && event.button.y < 254)//декодирование шифром цезаря
                    {
                        c = '4';
                    }
                    else if (event.button.x > 26 && event.button.y > 270 && event.button.x < 165 && event.button.y < 303)//декодирование шифра виженера
                    {
                        c = '5';
                    }
                    else if (event.button.x > 26 && event.button.y > 315 && event.button.x < 165 && event.button.y < 348)//декодирование шифра энигмы
                    {
                        c = '6';
                    }
                    else if (event.button.x > 26 && event.button.y > 360 && event.button.x < 165 && event.button.y < 392)// декодирование моего шифра
                    {
                        c = '7';
                    }
                    else if (event.button.x > 26 && event.button.y > 408 && event.button.x < 165 && event.button.y < 442)//выход
                    {
                        c = '9';
                        send(connection, &c, 1, NULL);
                        done = true;
                    }
                    else if (event.button.x > 257 && event.button.y > 220 && event.button.x < 492 && event.button.y < 258)//получение результата
                    {

                        fin = fopen(input_file_str.c_str(), "r");
                        if (fin == NULL)
                        {
                            SDL_Window* error = SDL_CreateWindow("Error", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, 400, 30,
                                SDL_WINDOW_SHOWN);
                            SDL_Surface* scr = SDL_GetWindowSurface(error);
                            SDL_Surface* scr_error = SDL_LoadBMP("errInFile.bmp");

                            SDL_Rect err_pos;
                            err_pos.x = 0;
                            err_pos.y = 0;
                            err_pos.h = 30;
                            err_pos.w = 400;
                            SDL_SetClipRect(scr_error, &err_pos);
                            SDL_BlitSurface(scr_error, NULL, scr, &err_pos);
                            SDL_UpdateWindowSurface(error);
                            SDL_Delay(1500);
                            SDL_FreeSurface(scr);
                            SDL_FreeSurface(scr_error);
                            SDL_DestroyWindow(error);
                            continue;
                        }
                        //первичная обработка ошибки формата выходного файла: он не может быть пустым или содержать меньше 4 символов
                        if(output_file_str.empty() || output_file_str.size()<4)
                        {
                            SDL_Window* error = SDL_CreateWindow("Error", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, 400, 30,
                                SDL_WINDOW_SHOWN);
                            SDL_Surface* scr = SDL_GetWindowSurface(error);
                            SDL_Surface* scr_error = SDL_LoadBMP("errOutFile.bmp");

                            SDL_Rect err_pos;
                            err_pos.x = 0;
                            err_pos.y = 0;
                            err_pos.h = 30;
                            err_pos.w = 400;
                            SDL_SetClipRect(scr_error, &err_pos);
                            SDL_BlitSurface(scr_error, NULL, scr, &err_pos);
                            SDL_UpdateWindowSurface(error);
                            SDL_Delay(1500);
                            SDL_FreeSurface(scr);
                            SDL_FreeSurface(scr_error);
                            SDL_DestroyWindow(error);
                            continue;
                        }
                        //обработка ошибки, когда формат не соответствует .txt, .rtx, .doc: проверяются последние 4 символа на соответствие формату
                        string chek_format(output_file_str, output_file_str.size() - 4, output_file_str.size());
                        if (chek_format != ".txt" && chek_format != ".rtx" && chek_format != ".doc")
                        {

                            SDL_Window* error = SDL_CreateWindow("Error", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, 400, 30,
                                SDL_WINDOW_SHOWN);
                            SDL_Surface* scr = SDL_GetWindowSurface(error);
                            SDL_Surface* scr_error = SDL_LoadBMP("errOutFile.bmp");

                            SDL_Rect err_pos;
                            err_pos.x = 0;
                            err_pos.y = 0;
                            err_pos.h = 30;
                            err_pos.w = 400;
                            SDL_SetClipRect(scr_error, &err_pos);
                            SDL_BlitSurface(scr_error, NULL, scr, &err_pos);
                            SDL_UpdateWindowSurface(error);
                            SDL_Delay(1500);
                            SDL_FreeSurface(scr);
                            SDL_FreeSurface(scr_error);
                            SDL_DestroyWindow(error);
                            continue;
                        }
                        fout = fopen(output_file_str.c_str(), "w"); // если название файла прошло все проверки, тогда он уже создается
                        // проверка на пустую строку со смещением
                        if ((c == '0' || c == '1' || c == '4' || c == '5') && input_shift.empty())
                        {
                            SDL_Window* error = SDL_CreateWindow("Error", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, 400, 30,
                                SDL_WINDOW_SHOWN);
                            SDL_Surface* scr = SDL_GetWindowSurface(error);
                            SDL_Surface* scr_error = SDL_LoadBMP("errShift.bmp");

                            SDL_Rect err_pos;
                            err_pos.x = 0;
                            err_pos.y = 0;
                            err_pos.h = 30;
                            err_pos.w = 400;
                            SDL_SetClipRect(scr_error, &err_pos);
                            SDL_BlitSurface(scr_error, NULL, scr, &err_pos);
                            SDL_UpdateWindowSurface(error);
                            SDL_Delay(1500);
                            SDL_FreeSurface(scr);
                            SDL_FreeSurface(scr_error);
                            SDL_DestroyWindow(error);
                            continue;
                        }
                        //Кодирование-Декодирование Цезарем или Виженером
                        if (c == '0' || c == '1' || c == '4' || c == '5')
                        {
                            
                            while (fgets(s, 1000, fin) != NULL)
                            {
                                send(connection, &c, 1, NULL);
                                send(connection, s, sizeof(s), NULL);
                                strcpy(s, input_shift.c_str());
                                send(connection, s, input_shift.size() , NULL);

                                recv(connection, res, sizeof(res), NULL);
                               
                                fputs(res, fout);
                                fputs("\n", fout);
                            }
                            
                        }
                        //Кодирование Энигмой
                        if (c == '2' || c == '6')
                        {

                            while (fgets(s, 1000, fin) != NULL)
                            {
                                send(connection, &c, 1, NULL);
                                send(connection, s, sizeof(s), NULL);
                                
                                recv(connection, res, sizeof(res), NULL);

                                fputs(res, fout);
                                fputs("\n", fout);
                            }
                            
                        }
                        //Кодирование моим кодом
                        if (c == '3')
                        {
                            FILE* fkey = fopen("key.txt", "w");
                            srand(time(NULL));
                            while (fgets(s, 1000, fin) != NULL)
                            {
                                for (unsigned int i = 0; i < len_s(s); i++)
                                {
                                    char c = rand() % 26;
                                    fputc(c + 'a', fkey);
                                }
                                fputc('\n', fkey);
                            }
                            fseek(fin, 0, SEEK_SET);
                            fclose(fkey);
                            fkey = fopen("key.txt", "r");
                            while (fgets(s, 1000, fin) != NULL)
                            {
                                send(connection, &c, 1, NULL);
                                send(connection, s, sizeof(s), NULL);
                                fgets(s, 1000, fkey);
                                send(connection, s, sizeof(s), NULL);
                                recv(connection, res, sizeof(res), NULL);

                                fputs(res, fout);
                                fputs("\n", fout);
                            }
                            fclose(fkey);
                           
                        }
                        //декодирование моим шифром
                        if (c == '7')
                        {
                            FILE* fkey = fopen("key.txt", "r");
                            while (fgets(s, 1000, fin) != NULL)
                            {
                                send(connection, &c, 1, NULL);
                                send(connection, s, sizeof(s), NULL);
                                fgets(s, 1000, fkey);
                                send(connection, s, sizeof(s), NULL);
                                recv(connection, res, sizeof(res), NULL);
                                    fputs(res, fout);
                                    fputs("\n", fout);
                            }
                            fclose(fkey);
                            
                        }
                        fclose(fin);
                        fclose(fout);
                        output_string = "Done.";
                    }
                    else
                    {
                        SDL_StopTextInput();
                        flag_input = 0;
                    }
                    break;
                }
                }
                updateFilemode();
            }

        }
     }
    quit();
    closesocket(connection);
    WSACleanup();
    
    return 0;
}
