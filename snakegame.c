
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


int dir; // ������ ����
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
//    gotoxy(x[length - 1], y[length - 1], "  "); //���� �������� ���� 
//    for (i = length - 1; i > 0; i--) { //������ǥ�� ��ĭ�� �ű� 
//        x[i] = x[i - 1];
//        y[i] = y[i - 1];
//    }
//
//
//    gotoxy( x[0], y[0], "��"); //�Ӹ��� �ִ����� �������� ��ħ 
//    if (dir == LEFT) --x[0]; //���⿡ ���� ���ο� �Ӹ���ǥ(x[0],y[0])���� ���� 
//    if (dir == RIGHT) ++x[0];
//    if (dir == UP) --y[0];
//    if (dir == DOWN) ++y[0];
//    gotoxy( x[i], y[i], ">>"); //���ο� �Ӹ���ǥ���� �Ӹ��� �׸� 
//
//}

void reset() {

    dir = LEFT; // ���� �ʱ�ȭ  
    speed = 100; // �ӵ� �ʱ�ȭ 
    length = 10; //�� ���� �ʱ�ȭ 
    score = 0; //���� �ʱ�ȭ

    for (int i = 0; i < length; i++) { //�� ���밪 �Է� 
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
