//
// Created by Lewis-N on 2021/5/12.
//

#ifndef _GAME_H_
#define _GAME_H_

const int sleept = 20;/*���ˢ��ʱ����*/

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

void move(snake* head, char op, int count);

void printmap();/*��ӡ��ͼ*/

void cleanhelp();

void printhelp();/*��ӡ����*/

void printsnake(snake* head, int diff);/*��ӡ�ߵ�����*/

food generatefood(snake* head);/*����ʳ��*/

void gamestart(snake*, int);

bool eat(snake*, food);/*�Ƿ�Ե�*/

bool Isfail(snake*);/*��ʤ��*/

void printfail(snake*, int);/*��ӡʧ�ܽ���*/

void quitgame(snake*);/*������Ϸ*/

void addsnake(snake* head);/*����������*/

int accelerate(int diff); /*����*/

int pausegame();/*��ͣ��Ϸ*/

void autoacc(int, int&);/*�Զ�����*/

#endif
