#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ESC 27

#define MAP_X 3
#define MAP_Y 2
#define MAP_WIDTH 30
#define MAP_HEIGHT 20

int x[100], y[100]; //x,y 좌표값을 저장 총 100개 

int length; //몸길이를 기억 
int speed; //게임 속도 
int score; //점수 저장  --reset함수에 의해 초기화됨

int dir; //이동방향 저장 
int key; //입력받은 키 저장 

void gotoxy(int x, int y,const char* s) { 
    COORD pos = { 2*x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}


void reset(void); //게임을 초기화 
void draw_map();
void move(int dir); //뱀머리를 이동 


int main() {
    reset();

    while (1) {
        if (_kbhit()) do { key = _getch(); } while (key == 224); //키 입력받음
        Sleep(speed);

        switch (key) { //입력받은 키를 파악하고 실행  
        case LEFT:
        case RIGHT:
        case UP:
        case DOWN:
            if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) ||
                (dir == DOWN && key != UP))//180회전이동을 방지하기 위해 필요. 
                dir = key;
            key = 0; // 키값을 저장하는 함수를 reset 
            break;
       
        }
        move(dir);

       
    }
}


void draw_map(void) { 
    int i;
    for (i = 0; i < MAP_WIDTH; i++) {
        gotoxy(i, 0, "*");
        gotoxy(i, MAP_HEIGHT, "*");
    }
    for (i = 0 ; i < MAP_HEIGHT; i++) {
        gotoxy(0,i, "*");
        gotoxy(MAP_WIDTH,i, "*");
    }
\
}

void reset(void) {
    int i;
    system("cls");

    while (_kbhit()) _getch(); 
    draw_map();
    dir = LEFT; 
    speed = 100; 
    length = 5;
    score = 0; 
    for (i = 0; i < length; i++) { 
        x[i] = MAP_WIDTH / 2 + i;
        y[i] = MAP_HEIGHT / 2;
        gotoxy(MAP_X + x[i], MAP_Y + y[i], "o");
    }
    gotoxy(MAP_X + x[0], MAP_Y + y[0], "e");  


}

void move(int dir) {
    int i;

    gotoxy(MAP_X + x[length - 1], MAP_Y + y[length - 1], "  "); 
    for (i = length - 1; i > 0; i--) { 
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    gotoxy(MAP_X + x[0], MAP_Y + y[0], "o"); 
    if (dir == LEFT) --x[0]; 
    if (dir == RIGHT) ++x[0];
    if (dir == UP) --y[0];
    if (dir == DOWN) ++y[0];
    gotoxy(MAP_X + x[i], MAP_Y + y[i], "e"); 
}




