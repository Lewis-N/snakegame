//
// Created by Lewis-N on 2021/5/12.
//

#ifndef _GAME_H_
#define _GAME_H_


typedef struct Linklist {
    int x;
    int y;
    char op;
    struct Linklist* next;
}snake;

typedef struct food {
    int x;
    int y;
    char quality;
}food;

snake* init();

void move(snake* head,char op,int count,bool);

void printmap();/*打印地图*/

void cleanhelp();

void printhelp(struct config);/*打印帮助*/

void printsnake(snake* head, int diff);/*打印蛇的身体*/

food generatefood(snake* head);/*生成食物*/

void gamestart(snake*,int,struct config s);

bool eat(snake*, food);/*是否吃到*/

bool Isfail(snake*);/*判胜是否吃到自己*/

bool hitwall(snake*, bool);/*判断是否撞墙*/

void printfail(snake*,int,struct config s);/*打印失败界面*/

void quitgame(snake*);/*结束游戏*/

void addsnake(snake* head);/*增长蛇身体*/

int accelerate(int diff); /*变速*/

int pausegame();/*暂停游戏*/

void autoacc(int, int&,bool);/*自动加速*/

void specialmove(int& x, int& y);

bool specialjudeg(snake*,bool);

#endif
