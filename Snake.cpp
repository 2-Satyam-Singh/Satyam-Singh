#include <bits/stdc++.h>
#include<conio.h>
#include<windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 10;
int x, y, fx, fy, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void set_cosole_size()
{
     HANDLE hOut;
     SMALL_RECT DisplayArea = {0, 0, 0, 0};
     int x = width + 1;
     int y = height+1;
     hOut = GetStdHandle(STD_OUTPUT_HANDLE);
     DisplayArea.Right = x;
     DisplayArea.Bottom = y;
     SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
}

void setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fx = rand() % width;
    fy = rand() % height;
    score = 0;
}
void draw()
{
    system("cls");
    for(int i = 0; i < width + 2; ++i)
        cout << "#";
    cout << endl;
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            if(j == 0)
                cout << "#";
            if(i == y && j == x)
                cout << "O";
            else if(i == fy && j == fx)
                cout << "F";
            else
            {
                bool print = false;
                for(int k = 0; k < nTail; k++){
                    if(tailX[k] == j && tailY[k] == i){
                        cout << "o";
                        print = true;
                    }
                }
                if(!print)
                    cout << " ";
            }
            if(j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
    for(int i = 0; i < width + 2; ++i)
        cout << "#";
    cout << endl;
    cout << "Score : " << score;
}
void input()
{
    if(kbhit()){
        switch(getch()){
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1;i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if(x >= width) x = 0; if(x < 0) x = width - 1;
    if(y >= height) y = 0; if(y < 0) y = height - 1;
    for(int i = 0; i < nTail; ++i)
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;
    if(x == fx && y == fy){
        score += 10;
        fx = rand() % width;
        fy = rand() % height;
        nTail++;
    }
}

int main(){
    //set_cosole_size();
    setup();
    while(!gameOver){
        draw();
        input();
        logic();
    }
}
