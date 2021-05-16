//
// Created by Lewis-N on 2021/5/12.
//

#include"game.h"
#include<iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <string>
#include <windows.h>
#include "console.h"

const int scoreup = 10;/*ÿ���ڵ�10��*/


const int def = 300;/*Ĭ���Ѷ�*/


using std::cin;
using std::cout;
using std::endl;

snake* init() {
    snake* head = (snake*)malloc(sizeof(snake));
    head->x = col / 2;
    head->y = (row / 2) - 1;
    head->op = 'w';
    snake* node, * node1, * end;
    node = (snake*)malloc(sizeof(snake));
    node1 = (snake*)malloc(sizeof(snake));
    end = (snake*)malloc(sizeof(snake));
    head->next = node;
    node->next = node1;
    node1->next = end;
    end->next = NULL;
    node->x = head->x;
    node->y = (head->y) + 1;
    node1->x = node->x;
    node1->y = node->y + 1;
    end->x = node1->x;
    end->y = (node1->y) + 1;
    return head;
}

void move(snake* head, char op, int count) {
    snake* ptr = head->next;
    if (ptr->next != NULL) {
        move(ptr, op, count + 1);/*�ݹ���ʵ���ҵ���β�ڵ�*/
    }
    ptr->x = head->x;
    ptr->y = head->y;
    if (count == 0) {/*0��ʾͷ�ڵ�*/
        switch (op) {
        case 'w':
            head->y--;
            break;
        case'a':
            head->x--;
            break;
        case'd':
            head->x++;
            break;
        case's':
            head->y++;
            break;
        }
        head->op = op;
    }

}

void printmap() {
    system("cls");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == 0 || i == row - 1) {
                cout << "=";
            }
            else if (j == 0 || j == col - 1) {
                cout << "|";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }

    return;
}

void cleanhelp() {
    setpos(col + 10, 5);
    cout << "Help" << endl;
    setpos(col + 10, 6);
    cout << "                                                                   ";
    setpos(0, row + 1);
    setpos(col + 10, 7);
    cout << "                                                                   ";
    setpos(col + 10, 8);
    cout << "                                                                   ";
    setpos(col + 10, 9);
    cout << "                                                                   ";
    return;
}

void printhelp() {
    setpos(col + 10, 5);
    cout << "Help" << endl;
    setpos(col + 10, 6);
    cout << "ʹ��w,a,s,d�����ߵ��ƶ�";
    setpos(0, row + 1);
    setpos(col + 10, 7);
    cout << "ʹ��+/-�ı��ٶ�,�÷������ٶ��йأ��ո���ͣ/�ָ���Ϸ";
    setpos(col + 10, 8);
    cout << "��ɫʳ��������ɣ�����˫���ӷ�";
    setpos(col + 10, 9);
    cout << "��ͣʱ����q���˳���������Ϸ";
    return;
}

void printsnake(snake* head, int diff) {
    snake* ptr = head;
    while (ptr->next != NULL) {
        if (ptr == head) {
            setpos(ptr->x, ptr->y);
            cout << "@";
            ptr = ptr->next;
        }
        else {
            setpos(ptr->x, ptr->y);
            cout << "*";
            ptr = ptr->next;
        }
    }
    setpos(ptr->x, ptr->y);
    cout << " ";
    setpos(0, 0);
    Sleep(accelerate(diff));
    return;
}

food generatefood(snake* head) {
    srand((unsigned)time(NULL));/*ˢ���������*/
    snake* ptr = head;
    food f;
    do {
        f.x = rand() % col;
        f.y = rand() % row;
    } while (f.x == 0 || f.y == 0 || f.x == col - 1 || f.y == row - 1);
    while (ptr != NULL) {
        if (f.x == ptr->x && f.y == ptr->y) {
            do {
                f.x = rand() % col;
                f.y = rand() % row;
            } while (f.x == 0 || f.y == 0 || f.x == col - 1 || f.y == row - 1);
            ptr = head;
        }
        else {
            ptr = ptr->next;
        }
    }
    int flag = rand() % 6;
    if (flag == 0) {
        f.quality = 'y';
        setpos(f.x, f.y);
        setcolor(6);
        cout << "#";
        setcolor(7);
    }
    else {
        f.quality = 'n';
        setpos(f.x, f.y);
        setcolor(7);
        cout << "#";
    }
    return f;
}



bool eat(snake* head, food f) {
    if (head->x == f.x && head->y == f.y) {
        return true;
    }
    else
        return false;
}

void gamestart(snake* head, int target) {
    int score = 0;
    int diff = 0;/*Ĭ���Ѷ�*/
    printmap();
    printhelp();
    setpos(col + 10, 10);
    cout << "��ǰ�÷�:" << score;
    if (target) {
        setpos(col + 10, 11);
        cout << "Ŀ�����:" << target;
    }
    HANDLE fd = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cinfo;
    cinfo.bVisible = 0;
    cinfo.dwSize = 1;/*���ؿ���̨���*/
    char op1;
    food f, hf;
    bool flag = false;
    bool start = false;
    f = generatefood(head);
    while (!Isfail(head)) {
        if (!start) {
            op1 = head->op;
            start = true;
        }
        printsnake(head, diff);
        if (kbhit()) {
            op1 = getch();
            if (op1 >= 65 && op1 <= 90) {
                op1 ^= 32;
            }
            if (op1 == ' ') {
                if (pausegame() == 1) {
                    if (score > 0) {
                        savescore(score);
                    }
                    return;
                }
            }
            if (op1 == '+' || op1 == '-') {
                if (op1 == '+') {
                    diff++;
                    op1 = head->op;
                }
                else if (op1 == '-') {
                    diff--;
                    op1 = head->op;
                }
            }
        }
        if ((op1 == 'w' && head->op == 's') || (op1 == 's' && head->op == 'w') || (op1 == 'a' && head->op == 'd') || op1 == 'd' && head->op == 'a') {/*�Ƿ�����Ĵ���*/
            op1 = head->op;
        }
        else if (op1 == 'w' || op1 == 'a' || op1 == 's' || op1 == 'd') {
            move(head, op1, 0);
        }
        else {
            op1 = head->op;
        }
        if (eat(head, f)) {
            setpos(f.x, f.y);
            cout << " ";
            addsnake(head);
            if (f.quality == 'y') { score += 2 * diff * scoreup; }
            else { score += diff * scoreup; }
            f = generatefood(head);
            setpos(col + 10, 10);
            cout << "��ǰ�÷�:" << score;
        }
        autoacc(score, diff);
    }
    if (score) {
        savescore(score);
    }
    printfail(head, target);
    return;
}

void quitgame(snake* head) {
    snake* ptr = head->next;
    while (ptr->next != NULL) {
        free(head);
        head = ptr;
        ptr = ptr->next;
    }
    free(ptr);
    system("cls");
    return;
}

bool Isfail(snake* head) {
    snake* ptr = head->next;
    if (head->x == 0 || head->x == col - 1 || head->y == 0 || head->y == row - 1) {
        return true;
    }
    while (ptr->next != NULL) {
        if (ptr->x == head->x && ptr->y == head->y) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

void addsnake(snake* head) {
    snake* ptr = head->next;
    while (ptr->next != NULL) {/*��λ��β*/
        ptr = ptr->next;
    }
    snake* newsnake = (snake*)malloc(sizeof(snake));
    ptr->next = newsnake;
    newsnake->next = NULL;
    return;/*newsnake����move�б�����*/
}

int accelerate(int diff) {
    return def - diff * 25 > 0 ? def - diff * 25 : 10;
}

int pausegame() {
    setpos(0, 0);
    while (true)
    {
        if (getch() == ' ')
            return 0;
        else if (getch() == 'q' || getch() == 'Q')
            return 1;
    }
}

void printfail(snake* head, int target) {
    cleanhelp();
    setpos(col / 2 - 10, row / 2);
    cout << "��ʧ����,�Ƿ�����һ��";
    setpos(col / 2 - 5, row / 2 + 2);
    cout << "[ ]����һ��";
    setpos(col / 2 - 5, row / 2 + 3);
    cout << "[ ]���˲���";
    char op = selectfail();
    if (op == 'y') {
        quitgame(head);
        head = init();
        gamestart(head, target);
    }
    else if (op == 'n') {
        quitgame(head);
    }
}

void autoacc(int score, int& diff) {
    if (score >= 5 * diff * scoreup) {
        diff++;
    }
}