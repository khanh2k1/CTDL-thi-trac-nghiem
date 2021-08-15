#pragma once
#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_none	-1

//--------------------------------------------------------

#include <windows.h>

//--------------------------------------------------------

int inputKey();

//-------------------------Screen-------------------------
void clrscr();

//screen: goto [x,y]
void gotoXY(int column, int line);

//screen: get [x]
int whereX();

//screen: get [y]
int whereY();

void TextColor(int color);
//end----------------------Screen----------------------end


