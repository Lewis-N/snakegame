//
// Created by Lewis-N on 2021/5/13.
//

#include "console.h"
#include "game.h"
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <windows.h>/*需要使用coord，handle*/
#include <ctime>
#include <conio.h>

using namespace std;

void setpos(short x, short y) {//设置光标位置，用于打印蛇
    COORD pos = { x,y };
    HANDLE position = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(position, pos);
    return;
}

void setcolor(char color) {//设置打印颜色，用于打印不同颜色的食物
    HANDLE Color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Color, color);
    return;
}


bool cmp(struct data s1,struct data s2) {
    return s1.score >= s2.score;
}

void savescore(int score1) {
    struct data *s=(struct data*)malloc(sizeof(struct data));//这里用malloc是为了下面能一次性写入一整个结构体
    s->score = score1;
    setpos(col / 2 - 10, row / 2);
    cout << "请输入用户名:";
    cin >> s->username;
    time_t t;
    struct tm* ti;
    time(&t);
    ti = localtime(&t);
    FILE* p = fopen(filename, "ab");
    if (p == NULL) {
        p = fopen(filename, "wb");
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
    system("cls");
    printmap();
    return;
}

int menu() {
    printmap();
    printconsolehelp();
    setpos(col / 2 - 5, row / 2 - 2);
    cout << "[ ]开始游戏" << endl;
    setpos(col / 2 - 5, row / 2 - 1);
    cout << "[ ]查看排行榜" << endl;
    setpos(col / 2 - 5, row / 2);
    cout << "[ ]设置" << endl;
    setpos(col / 2 - 5, row / 2+1);
    cout << "[ ]退出" << endl;
    return select();
}


int showranklist() {
    int flag = 0;//0表示选择，1表示判断
    struct data s[maxlen];
    struct data* ptr = s;
    int i = 0;
    FILE* p = fopen(filename, "rb");
    if (p == NULL) {
        system("cls");
        setpos(40, 7);
        cout << "无法查询到记录，您应该是第一个用户,按任意键退出 ";
        setpos(40, 8);
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
    cout << "排行榜";
    for (int j = 0; j < i - 1; j++) {
        setpos(40, j * 2 + 7);
        cout << "[ ]" <<s[j].username<<"\t"<< s[j].score << "\t";
        cout << s[j].year + 1900 <<"/"<< setw(2) << setfill('0') << s[j].month + 1 << "/" << setw(2) << setfill('0') << s[j].day << "\t";
        cout << setw(2) << setfill('0') << s[j].hour << ":" << setw(2) << setfill('0') << s[j].min << ":" << setw(2) << setfill('0') << s[j].sec << endl;
    }
    fclose(p);
    printrankhelp();
    int y = 2 * (i - 1) + 7;
    setpos(40, y);
    cout << "[ ]删除全部记录";
    setpos(48, y + 4);
    cout << "[ ]是";
    setpos(48, y + 6);
    cout << "[ ]否";
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
                    remove(filename);//删除记录
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
    int y = row / 2+1;
    int choice = 0;
    char op;
    while (true) {
        int choice1 = choice;
        op = getch();
        if (op == ' '&&choice!=0) {
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
        if (op == ' '&&choice!=0) {
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
        if (choice > 4) {
            choice = 1;
        }
        if (choice <= 0) {
            choice = 4;
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
    cout << "使用w,s进行选择";
    setpos(0, row + 1);
    setpos(col + 10, 7);
    cout << "空格进行确定";
    return;
}


void printrankhelp() {
    setpos(10, 3);
    cout << "Help";
    setpos(5, 4);
    cout<<"w,s进行选择"; 
    setpos(5, 5);
    cout << "选择你的目标";
    setpos(5, 6);
    cout << "空格确认"; 
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
        if ((op == ' '||op==9)&&choice!=0) {//tab对应的ascii为9
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
        setpos(x, y + 2*choice1);
        cout << " ";
        setpos(x, y + 2*choice);
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
            return -1;//-1特殊值表示特殊状态
        }
        if (op == ' '&&choice!=0) {
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
    return choice==1?1:2;
}

config settings() {
    system("cls");
    settingshelp();
    setpos(52, 3);
    cout << "设置";
    setpos(32, 7);
    cout << "自动加速";
    setpos(50, 7);
    cout << "[ ]是"<<"    "<<"[ ]否";
    setpos(32, 9);
    cout << "墙体碰撞";
    setpos(50, 9);
    cout << "[ ]是" << "    " << "[ ]否";
    setpos(32, 11);
    cout << "保存并返回";
    setpos(50, 11);
    cout << "[ ]是" << "    " << "[ ]否";
    int c1= choicesetting(7);
    int c2= choicesetting(9);
    int c3= choicesetting(11);
    if (c3 == 1) {
        struct config s=configini(c1, c2);
        saveconfig(s);
        return s;
    }
    else {
        return readconfig();
    }
}

int choicesetting(int y) {
    int choice = 0;
    int x = 51;
    char op;
    while (true) {
        int choice1 = choice;
        op = getch();
        if (op == ' '&&choice!=0) {
            break;
        }
        if (op >= 65 && op <= 90) {
            op ^= 32;
        }
        switch (op) {
        case'a':
            choice--;
            break;
        case'd':
            choice++;
            break;
        }
        if (choice > 2) {
            choice = 1;
        }
        if (choice <= 0) {
            choice = 2;
        }
        setpos(x + 9 * (choice1-1), y);
        cout << " ";
        setpos(x + 9 * (choice - 1), y);
        cout << "*";
    }
    return choice;
}

void settingshelp() {
    setpos(15, 3);
    cout << "Help";
    setpos(10, 4);
    cout << "a,d进行选择";
    setpos(10, 5);
    cout << "空格确认";
    return;
}

config configini(int choice1,int choice2) {
    config s;
    switch (choice1) {
    case 1:
        s.acc = true;
        break;
    case 2:
        s.acc = false;
        break;
    }
    switch (choice2) {
    case 1:
        s.wall = true;
        break;
    case 2:
        s.wall = false;
        break;
    }
    return s;
}

config readconfig() {
    FILE* p = fopen(configfile, "rb");
    if (p == NULL) {
        return configini();
    }
    else {
        config s;
        fread(&s, sizeof(struct config), 1, p);
        return s;
    }
}

void saveconfig(struct config s) {
    FILE* p = fopen(configfile, "wb");
    fwrite(&s, sizeof(struct config), 1, p);
    return;
}