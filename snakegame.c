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
int food_x, food_y;
int dir; //이동방향 저장 
int key; //입력받은 키 저장 
int life_count = 3;

void gotoxy(int x, int y,const char* s) { 
    COORD pos = { 2*x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}

void life();
void life_screen();
void food();
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
        gotoxy(MAP_X + i, MAP_Y, "■");
    }
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) {
        gotoxy(MAP_X, i, "■");
        gotoxy(MAP_X + MAP_WIDTH - 1, i, "■");
    }
    for (i = 0; i < MAP_WIDTH; i++) {
        gotoxy(MAP_X + i, MAP_Y + MAP_HEIGHT - 1, "■");
    }
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

    food();
    life_screen();
}
void game_over(void) { //게임종료 함수 
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 5, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 6, "|      GAME OVER..     |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 7, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 8, " YOUR SCORE : ");
 
    printf("%d", score);


    Sleep(500);

  
}
void move(int dir) {
    int i;

    if (x[0] == food_x && y[0] == food_y) { //food와 충돌했을 경우 
        score += 10; //점수 증가
        
        food(); //새로운 food 추가 
        length++; //길이증가 
        x[length - 1] = x[length - 2]; //새로만든 몸통에 값 입력 
        y[length - 1] = y[length - 2];
    }

    for (i = 1; i < length; i++) { //자기몸과 충돌했는지 검사 
        if (x[0] == x[i] && y[0] == y[i]) {
            life();
            return;
        }
    }


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
    
    if (x[0] == 0 || x[0] == MAP_WIDTH - 1 || y[0] == 0 || y[0] == MAP_HEIGHT - 1) { //벽과 충돌했을 경우 
        life();
        return;
    }
}



void food(void) {
    int i;

    int food_crush_on = 0;//food가 뱀 몸통좌표에 생길 경우 on 
    int r = 0; //난수 생성에 사동되는 변수 
    gotoxy(MAP_X, MAP_Y + MAP_HEIGHT, " YOUR SCORE: "); //점수표시 
    printf("%d", score);

    while (1) {
        food_crush_on = 0;
        srand((unsigned)time(NULL) + r); //난수표생성 
        food_x = (rand() % (MAP_WIDTH - 2)) + 1;    //난수를 좌표값에 넣음 
        food_y = (rand() % (MAP_HEIGHT - 2)) + 1;

        for (i = 0; i < length; i++) { //food가 뱀 몸통과 겹치는지 확인  
            if (food_x == x[i] && food_y == y[i]) {
                food_crush_on = 1; //겹치면 food_crush_on 를 on 
                r++;
                break;
            }
        }

        if (food_crush_on == 1) continue; //겹쳤을 경우 while문을 다시 시작 

        gotoxy(MAP_X + food_x, MAP_Y + food_y, "♪"); //안겹쳤을 경우 좌표값에 food를 찍고 
        speed -= 3; //속도 증가 
        break;

    }
}

void life() {
    life_count -= 1;
    reset();
    if (life_count == 0) {
        game_over();
    }
}

void life_screen()
{ 
	if(life_count==3)	gotoxy(26,22, "LIFE: ♥♥♥");
	if(life_count==2) 	gotoxy(26,22, "LIFE: ♥♥♡");
	if(life_count==1) 	gotoxy(26,22, "LIFE: ♥♡♡");
}
