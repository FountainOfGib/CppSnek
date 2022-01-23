#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <conio.h>
#include <time.h>
#include <queue>
#include <tuple>
#include <type_traits>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x,y,fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
queue<tuple<int,int>> segments;
int nSegments = 1;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

bool isSeg(int _i, int _j, int _xs[], int _ys[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (_i == _ys[i] && _j ==_xs[i])
        {
            return true;
        }
    }
    return false;
}

void Draw()
{
    system("cls");

    queue<tuple<int,int>> segCopy (segments);
    int segmentXs [segments.size()];
    int segmentYs [segments.size()];
    int i = 0;
    while (!segCopy.empty()) {
        segmentXs[i] = get<0>(segCopy.front());
        segmentYs[i] = get<1>(segCopy.front());
        i++;
        segCopy.pop();
    }

    for (int i = 0; i < width+3; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height+1; i++)
    {
        for (int j = 0; j < width+2; j++)
        {
            if (j==0)
            {
                cout << "#";
            }
            if (i==y && j==x)
            {
                cout << "O";
            }else if (i==fruitY && j==fruitX)
            {
                cout << "@";
            }else if (isSeg(i, j, segmentXs, segmentYs, nSegments))
            {
                cout << "o";
            }else
            {
                cout << " ";
            }

            if (j == width)
            {
                cout << "#";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width +3; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'w':
                dir = UP;
                break;

            case 'a':
                dir = LEFT;
                break;

            case 's':
                dir = DOWN;
                break;

            case 'd':
                dir = RIGHT;
                break;

            case 27:
                gameOver = true;
                break;
        }
    }
}

void logic()
{
    segments.push(tuple<int,int>(x,y));
    if (segments.size() > nSegments)
    {
        segments.pop();
    }

    switch (dir)
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
    }
    if (x < 0 || y < 0 || x > width || y > height)
    {
        gameOver = true;
    }
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        nSegments++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main()
{
    srand(time(nullptr));
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        logic();
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    Draw();
    cout << "GAME OVER!" << endl;
    system("pause");
    return 0;
}
