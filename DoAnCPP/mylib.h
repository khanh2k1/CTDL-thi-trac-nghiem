#pragma once
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>

#define Left 75
#define Right 77
#define Up 72
#define Down 80
#define f1 112
#define f2 113
#define tab 9
#define Enter 13
#define Space 32
#define Backspace 8
#define Esc 27
#define ctrl 12
//const int WHITE=15;
#define PASSWORD "abcdef"
//const int WHITE=15;
#define KEY_NONE	-1
#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15
    
HANDLE hConsoleOutput;
HANDLE hConsoleInput;
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}
int inputKey()
{
    if (_kbhit()) // nhan tu ban phim
    {
        int key = _getch();

        if (key == 224)
        {
            key = _getch();
            return key + 1000;
        }

        return key;
    }
    else
    {
        return KEY_NONE;
    }
    return KEY_NONE;
}
char* Pwd() {
    char S[40]; int i = 0;
    while ((S[i] = _getch()) != Enter)
    {
        printf("%c", '*'); i++;
    }
    S[i] = '\0';
    return S;
}
int CheckPwd() {
    int dem = 0;
    for (dem = 1; dem <= 3; dem++)
    {
        printf("Password :");
        if (strcmp(Pwd(), PASSWORD) == 0)   return 1;
        else printf("\nPassword sai. Hay nhap lai\n");
    }
    return 0;
}
void gotoxy(float x, float y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
int wherex(void)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}
int wherey(void)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void ClearConsoleToColors(int ForgC, int BackC) // doi mau console
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    //This is used to get the handle to current output buffer.

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //This is used to reset the carat/cursor to the top left.

    COORD coord = { 0, 0 };
    //This is a return value indicating how many characterss were written
      //   It is not used but we need to capture this since it will be
        //   written anyway (passing NULL causes an access violation).

    DWORD count;

    //This is a structure containing all the console info
// It is used here to find the size of the console.

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //Now the current color will be set by this handle

    SetConsoleTextAttribute(hStdOut, wColor);

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //This fills the buffer with a given character (in this case 32=space).
        FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        //This will set our cursor position for the next print statement
        SetConsoleCursorPosition(hStdOut, coord);
    }
    return;
}
void TextColor(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void SetTeColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0; wAttributes |= color;
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void Nocursortype() // an con tro chuot
    {
        CONSOLE_CURSOR_INFO Info;
        Info.bVisible = FALSE;
        Info.dwSize = 20;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
    }
void Cursortype() // an con tro chuot
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = TRUE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void setColor(WORD color)
{
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void textcolor(int x)
{
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, x);
}

// Ham thay doi kich co man hinh console.
void resizeConsole(SHORT width, SHORT height)
{
	/*HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);*/

	COORD crd = { width, height };
	SMALL_RECT rec = { 0, 0, width - 1, height - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hConsoleOutput, TRUE, &rec);
	SetConsoleScreenBufferSize(hConsoleOutput, crd);
}

// Ham xoa man hinh khong bi dut(lag).

// Ham thay doi mau nen hien thi.
void setBackgroundColor(WORD color)
{
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4; // Dich trai 3 bit de phu hop voi mau nen
	wAttributes &= 0xff0f; // Cai 0 cho 1 bit chu nhay va 3 bit mau nen
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

// Ham an hien con tro.
void Cursor(BOOL bVisible, DWORD dwSize)
{
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	ConsoleCursorInfo.bVisible = bVisible;
	ConsoleCursorInfo.dwSize = dwSize; // Phan tram bao trum o cua con tro chuot
	SetConsoleCursorInfo(hConsoleOutput, &ConsoleCursorInfo);
}


