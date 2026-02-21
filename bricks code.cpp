#include <iostream>
#include <conio.h>
#include <windows.h>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Point { int x, y; };

const int width = 20, height = 20;
queue<Point> snake;
int fruitX, fruitY, score;
enum Direction { LEFT, RIGHT, UP, DOWN } dir;
bool gameOver;

void gotoXY(int x, int y) {
    COORD c = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
bool isOnSnake(int x, int y) {
    queue<Point> q = snake;
    while (!q.empty()) {
        if (q.front().x == x && q.front().y == y) return true;
        q.pop();
    }
    return false;
}

void generateFruit() {
    do {
        fruitX = rand() % width;
        fruitY = rand() % height;
    } while (isOnSnake(fruitX, fruitY));
}

void Setup() {
    gameOver = false;
    dir = RIGHT;
    score = 0;
    while (!snake.empty()) snake.pop();
    snake.push({width/2, height/2});
    generateFruit();
}

void Draw() {
    gotoXY(0,0);
    for(int i=0;i<width+2;i++) cout<<"#"; cout<<endl;
    for(int y=0;y<height;y++) {
        for(int x=0;x<width;x++) {
            if(x==0) cout<<"#";
            bool printed = false;
            queue<Point> q = snake;
            int len = q.size();
            for(int k=0;k<len;k++){
                Point p = q.front(); q.pop();
                if(p.x==x && p.y==y){
                    cout<<(k==len-1?"O":"o");
                    printed = true;
                    break;
                }
            }
            if(fruitX==x && fruitY==y){ cout<<"*"; printed=true; }
            if(!printed) cout<<" ";
            if(x==width-1) cout<<"#";
        }
        cout<<endl;
    }
    for(int i=0;i<width+2;i++) cout<<"#"; cout<<endl;
    cout<<"Score: "<<score<<endl;
    cout<<"Controls: Arrow Keys | X = Exit"<<endl;
}

void Input() {
    if(_kbhit()){
        int ch=_getch();
        if(ch==0||ch==224) ch=_getch();
        if(ch==72 && dir!=DOWN) dir=UP;
        else if(ch==80 && dir!=UP) dir=DOWN;
        else if(ch==75 && dir!=RIGHT) dir=LEFT;
        else if(ch==77 && dir!=LEFT) dir=RIGHT;
        else if(ch=='x'||ch=='X') gameOver=true;
    }
}

void Logic() {
    Point head = snake.back();
    if(dir==LEFT) head.x--;
    else if(dir==RIGHT) head.x++;
    else if(dir==UP) head.y--;
    else if(dir==DOWN) head.y++;

    if(head.x<0||head.x>=width||head.y<0||head.y>=height||isOnSnake(head.x, head.y)){
        gameOver=true;
        return;
    }
    snake.push(head);
    if(head.x==fruitX && head.y==fruitY){
        score+=10;
        generateFruit();
    } else snake.pop();
}

void WaitForStart() {
    system("cls");
    gotoXY(0,0);
    cout<<"                                                                                                                    "<<endl;
    cout<<"                                            ======================"<<endl;
    cout<<"                                                  SNAKE GAME   "<<endl;
    cout<<"                                            ======================"<<endl<<endl;
    cout<<"                                              Press 'S' to Start"<<endl;
    cout<<"                                              Arrow Keys to Move"<<endl;
    while(true){
        if(_kbhit()){
            char ch=_getch();
            if(ch=='s'||ch=='S') break;
        }
    }
}

int main() {
    srand(time(0));

    WaitForStart();  
    system("cls");   
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    system("cls");
    cout<<"GAME OVER!"<<endl;
    cout<<"Final Score: "<<score<<endl;
    return 0;
}

