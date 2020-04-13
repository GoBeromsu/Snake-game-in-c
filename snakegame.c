
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


int dir; // 움직일 방향
int key;
int length;
int speed;
int score;
int life;
int x[100], y[100];


void gotoxy(int x, int y, const char* s) { 
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}

//void move(int dir) {
//    int i;
//
//    gotoxy(x[length - 1], y[length - 1], "  "); //몸통 마지막을 지움 
//    for (i = length - 1; i > 0; i--) { //몸통좌표를 한칸씩 옮김 
//        x[i] = x[i - 1];
//        y[i] = y[i - 1];
//    }
//
//
//    gotoxy( x[0], y[0], "ㅇ"); //머리가 있던곳을 몸통으로 고침 
//    if (dir == LEFT) --x[0]; //방향에 따라 새로운 머리좌표(x[0],y[0])값을 변경 
//    if (dir == RIGHT) ++x[0];
//    if (dir == UP) --y[0];
//    if (dir == DOWN) ++y[0];
//    gotoxy( x[i], y[i], ">>"); //새로운 머리좌표값에 머리를 그림 
//
//}

void reset() {

    dir = LEFT; // 방향 초기화  
    speed = 100; // 속도 초기화 
    length = 10; //뱀 길이 초기화 
    score = 0; //점수 초기화

    for (int i = 0; i < length; i++) { //뱀 몸통값 입력 
        x[i] =i;
        y[i] = 1;

        printf("%d",x[i]);
        printf("%d\n",y[i]);
		gotoxy(x[i],  y[i], "o");
    }

    gotoxy(10+ x[0],y[0], ">>");

}

int main() {
    

    reset();
}
