//
// Created by Lewis-N on 2021/5/13.
//

#ifndef CONSOLE_H
#define CONSOLE_H
const int row = 23;
const int col = 51;

const int maxlen = 1000;

const int maxsize = 100;

#define filename "data.txt"
#define configfile "config.txt"

typedef struct config {
    bool acc;
    bool wall;
}config;

typedef struct data{
    int score;
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    char username[maxsize];
}data;


void setpos(short x, short y);

void savescore(int score);

bool cmp(struct data s1, struct data s2);

int menu();

char selectfail();

int select();

int showranklist();

void setcolor(char color);

void printconsolehelp();

void printrankhelp();

int selecttarget(int max);

int selectchoice(int posy);

config settings();

int choicesetting(int y);

config configini(int choice1 = 0, int choice2 = 0);

config readconfig();

void settingshelp();

void saveconfig(config);

#endif