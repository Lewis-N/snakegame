//
// Created by Lewis-N on 2021/5/12.
//

//@表蛇头，*表蛇身体，#表示食物，=和|表示墙

#include <iostream>
#include "game.h"
#include "console.h"
using namespace std;

int main() {
    int target=0;
    struct config s = readconfig();
    int choice = menu();
    while (choice != 4) {
        if (choice == 1) {
            system("cls");
            snake* head = init();
            gamestart(head,target,s);
        }
        else if (choice == 2) {
            target=showranklist();
        }
        else if (choice == 3) {
            s=settings();
        }
        choice = menu();
    }
    system("cls");
    printmap();
    setpos(col / 2, row / 2);
    cout << "再见";
    return 0;
}