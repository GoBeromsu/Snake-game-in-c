#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 32
#define ESC 27

#define MAP_X 3
#define MAP_Y 2
#define MAP_WIDTH 30
#define MAP_HEIGHT 20

int x[100], y[100]; //x,y Ï¢åÌëúÍ∞íÏùÑ ?Ä??Ï¥?100Í∞?

int length; //Î™∏Í∏∏?¥Î? Í∏∞Ïñµ 
int speed; //Í≤åÏûÑ ?çÎèÑ 
int score; //?êÏàò ?Ä?? --reset?®Ïàò???òÌï¥ Ï¥àÍ∏∞?îÎê®
int food_x, food_y;
int dir; //?¥ÎèôÎ∞©Ìñ• ?Ä??
int key; //?ÖÎ†•Î∞õÏ? ???Ä??
int life_count = 3;
int last_score = 0;

void gotoxy(int x, int y, const char* s) {
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}

void life();
void food();
void reset(void); 
void draw_map();
void move(int dir); 
void pasue();

int main() {
    reset();

    while (1) {
        if (_kbhit()) do { key = _getch(); } while (key == 224); 
        Sleep(speed);

        switch (key) {  
        case LEFT:
        case RIGHT:
        case UP:
        case DOWN:
            if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) ||
                (dir == DOWN && key != UP))
                dir = key;
            key = 0;
            break;
        case PAUSE: pause(); break;
        case ESC: system("cls"); exit(0);  

        }
        move(dir);
        if (life_count < 0) {
            system("cls");
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 7, "+----------------------+");
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 8, "|      Developer       |");
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 9, "|    Beomsu, Hye Won   |");
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 10,"+----------------------+");
            draw_map();

            system("pause");
            life_count = 3;
            reset();
        }

    }
}


void draw_map(void) {
    int i;
    for (i = 0; i < MAP_WIDTH; i++) {
        gotoxy(MAP_X + i, MAP_Y, "*");
    }
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) {
        gotoxy(MAP_X, i, "*");
        gotoxy(MAP_X + MAP_WIDTH - 1, i, "*");
    }
    for (i = 0; i < MAP_WIDTH; i++) {
        gotoxy(MAP_X + i, MAP_Y + MAP_HEIGHT - 1, "*");
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
    gotoxy(MAP_X + 22, MAP_Y + MAP_HEIGHT, "YOUR LIFE: ");
    printf("%d", life_count);
}
void game_over(void) { //Í≤åÏûÑÏ¢ÖÎ£å ?®Ïàò 
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 7, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 8, "|      GAME OVER..     |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 9, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 5, MAP_Y + 10, " TOTAL  SCORE  :  ");

    printf("%d", last_score);


    Sleep(2000);
    life_count--;

}
void move(int dir) {
    int i;

    if (x[0] == food_x && y[0] == food_y) { 
        score += 10; 

        food(); 
        length++; 
        x[length - 1] = x[length - 2]; 
        y[length - 1] = y[length - 2];
    }

    for (i = 1; i < length; i++) { 
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

    if (x[0] == 0 || x[0] == MAP_WIDTH - 1 || y[0] == 0 || y[0] == MAP_HEIGHT - 1) { 
        life();
        return;
    }
}



void food(void) {
    int i;

    int food_crush_on = 0;
    int r = 0; 
    gotoxy(MAP_X, MAP_Y + MAP_HEIGHT, " YOUR SCORE: "); 
    printf("%d", score);

    while (1) {
        food_crush_on = 0;
        srand((unsigned)time(NULL) + r); 
        food_x = (rand() % (MAP_WIDTH - 2)) + 1; 
        food_y = (rand() % (MAP_HEIGHT - 2)) + 1;

        for (i = 0; i < length; i++) {
            if (food_x == x[i] && food_y == y[i]) {
                food_crush_on = 1; 
                r++;
                break;
            }
        }

        if (food_crush_on == 1) continue; 

        gotoxy(MAP_X + food_x, MAP_Y + food_y, "¢‹");
            speed -= 3;
        break;

    }
}

void life() {
    life_count -= 1;
    last_score += score;
    gotoxy(MAP_X + 22, MAP_Y + MAP_HEIGHT, "YOUR LIFE: ");
    printf("%d", life_count);
    reset();
    if (life_count == 0) {
        game_over();
    }
    else if (life_count < -2) {

    }
}


void pause(void) {
    while (1) {
        if (key == PAUSE) {

            gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y - 1, "* PAUSE : PRESS ANY KEY TO RESUME *");
            Sleep(500);
        }
        else {
            draw_map();
            return;
        }
        if (_kbhit()) {
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y - 1, "                                    ");

            do {
                key = _getch();
            } while (key == 224);
        }

    }
}
