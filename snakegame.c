
#include<stdio.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<Windows.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ESC 27


struct pos {
	int x, y;
};

void gotoxy(int x, int y, const char* s) { 
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}


int main() {
    gotoxy(2, 2, "hihi");
}