//
// Created by Lewis-N on 2021/5/13.
//

#include "console.h"
#include "game.h"
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <windows.h>/*��Ҫʹ��coord��handle*/
#include <ctime>
#include <conio.h>

using namespace std;

void setpos(short x, short y) {//���ù��λ�ã����ڴ�ӡ��
    COORD pos = { x,y };
    HANDLE position = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(position, pos);
    return;
}

void setcolor(char color) {//���ô�ӡ��ɫ�����ڴ�ӡ��ͬ��ɫ��ʳ��
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color, color);
    return;
}


bool cmp(struct data s1, struct data s2) {
    return s1.score >= s2.score;
}

void savescore(int score1) {
    struct data* s = (struct data*)malloc(sizeof(struct data));//������malloc��Ϊ��������һ����д��һ�����ṹ��
    s->score = score1;
    time_t t;
    struct tm* ti;
    time(&t);
    ti = localtime(&t);
    FILE* p = fopen("data.txt", "ab");
    if (p == NULL) {
        p = fopen("data.txt", "wb");
    }
    s->year = ti->tm_year;
    s->month = ti->tm_mon;
    s->day = ti->tm_mday;
    s->hour = ti->tm_hour;
    s->min = ti->tm_min;
    s->sec = ti->tm_sec;
    fwrite(s, sizeof(struct data), 1, p);
    fclose(p);
    free(s);
    return;
}

int menu() {
    printmap();
    printconsolehelp();
    setpos(col / 2 - 5, row / 2 - 2);
    std::cout << "[ ]��ʼ��Ϸ" << std::endl;
    setpos(col / 2 - 5, row / 2 - 1);
    std::cout << "[ ]�鿴���а�" << std::endl;
    setpos(col / 2 - 5, row / 2);
    std::cout << "[ ]�˳�" << std::endl;
    return select();
}


int showranklist() {
    int flag = 0;//0��ʾѡ��1��ʾ�ж�
    struct data s[maxlen];
    struct data* ptr = s;
    int i = 0;
    FILE* p = fopen("data.txt", "rb");
    if (p == NULL) {
        system("cls");
        setpos(40, 7);
        std::cout << "�޷���ѯ����¼����Ӧ���ǵ�һ���û�,��������˳� ";
        system("pause");
        return 0;
    }
    else {
        while (!feof(p)) {
            fread(ptr + i, sizeof(struct data), 1, p);
            i++;
        }
        sort(ptr, ptr + i, cmp);
    }
    system("cls");
    setpos(52, 3);
    cout << "���а�";
    for (int j = 0; j < i - 1; j++) {
        setpos(40, j * 2 + 7);
        cout << "[ ]" << s[j].score << "\t";
        cout << s[j].year + 1900 << "/" << setw(2) << setfill('0') << s[j].month + 1 << "/" << setw(2) << setfill('0') << s[j].day << "\t";
        cout << setw(2) << setfill('0') << s[j].hour << ":" << setw(2) << setfill('0') << s[j].min << ":" << setw(2) << setfill('0') << s[j].sec << endl;
    }
    fclose(p);
    printrankhelp();
    int y = 2 * (i - 1) + 7;
    setpos(40, y);
    cout << "[ ]ɾ��ȫ����¼";
    setpos(48, y + 4);
    cout << "[ ]��";
    setpos(48, y + 6);
    cout << "[ ]��";
    setpos(48, y + 8);
    int choice;
    int sure;
    char op;
    while (true) {
        if (flag == 0) {
            choice = selecttarget(i);
            flag = 1;
        }
        if (flag == 1) {
            sure = selectchoice(y + 2);
            if (sure == -1) {
                setpos(41, 5 + 2 * choice);
                cout << " ";
                flag = 0;
            }
            else if (sure == 2) {
                return 0;
            }
            else if (sure == 1) {
                if (choice == i) {
                    remove("data.txt");//ɾ����¼
                    return 0;
                }
                else return s[choice - 1].score;
            }
        }
    }
}

char selectfail() {
    printconsolehelp();
    int x = col / 2 - 4;
    int y = row / 2 + 1;
    int choice = 0;
    char op;
    while (true) {
        int choice1 = choice;
        op = getch();
        if (op == ' ') {
            break;
        }
        if (op >= 65 && op <= 90) {
            op ^= 32;
        }
        switch (op) {
        case'w':
            choice--;
            break;
        case's':
            choice++;
            break;
        }
        if (choice > 2) {
            choice = 1;
        }
        if (choice <= 0) {
            choice = 2;
        }
        setpos(x, y + choice1);
        cout << " ";
        setpos(x, y + choice);
        cout << "*";
    }
    return choice == 1 ? 'y' : 'n';
}

int select() {
    int x = col / 2 - 4;
    int y = row / 2 - 3;
    int choice = 0;
    char op;
    while (true) {
        int choice1 = choice;
        op = getch();
        if (op == ' ') {
            break;
        }
        if (op >= 65 && op <= 90) {
            op ^= 32;
        }
        switch (op) {
        case'w':
            choice--;
            break;
        case's':
            choice++;
            break;
        }
        if (choice > 3) {
            choice = 1;
        }
        if (choice <= 0) {
            choice = 3;
        }
        setpos(x, y + choice1);
        cout << " ";
        setpos(x, y + choice);
        cout << "*";
    }
    return choice;
}

void printconsolehelp() {
    setpos(col + 10, 5);
    cout << "Help" << endl;
    setpos(col + 10, 6);
    cout << "ʹ��w,s����ѡ��";
    setpos(0, row + 1);
    setpos(col + 10, 7);
    cout << "�ո����ȷ��";
    return;
}


void printrankhelp() {
    setpos(10, 3);
    cout << "Help";
    setpos(5, 4);
    cout << "w,a����ѡ��";
    setpos(5, 5);
    cout << "ѡ�����Ŀ��";
    setpos(5, 6);
    cout << "tab��ѡ�����ȷ�Ͽ������ת";
    setpos(5, 7);
    cout << "�ո�ȷ��";
    return;
}

int selecttarget(int max) {
    int choice = 0;
    int x = 41;
    int y = 5;
    char op;
    while (true) {
        int choice1 = choice;
        op = getch();
        if (op == ' ' || op == 9) {//tab��Ӧ��asciiΪ9
            break;
        }
        if (op >= 65 && op <= 90) {
            op ^= 32;
        }
        switch (op) {
        case'w':
            choice--;
            break;
        case's':
            choice++;
            break;
        }
        if (choice > max) {
            choice = 1;
        }
        if (choice <= 0) {
            choice = max;
        }
        setpos(x, y + 2 * choice1);
        cout << " ";
        setpos(x, y + 2 * choice);
        cout << "*";
    }
    return choice;
}

int selectchoice(int y) {
    int choice = 0;
    int x = 49;
    char op;
    while (true) {
        int choice1 = choice;
        op = getch();
        if (op == 9) {
            return -1;//-1����ֵ��ʾ����״̬
        }
        if (op == ' ') {
            break;
        }
        if (op >= 65 && op <= 90) {
            op ^= 32;
        }
        switch (op) {
        case'w':
            choice--;
            break;
        case's':
            choice++;
            break;
        }
        if (choice > 2) {
            choice = 1;
        }
        if (choice <= 0) {
            choice = 2;
        }
        setpos(x, y + 2 * choice1);
        cout << " ";
        setpos(x, y + 2 * choice);
        cout << "*";
    }
    return choice == 1 ? 1 : 2;
}