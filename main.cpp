//
// Created by Lewis-N on 2021/5/12.
//

//@����ͷ��*�������壬#��ʾʳ�=��|��ʾǽ

#include <iostream>
#include "game.h"
#include "console.h"
using namespace std;

int main() {
    int target = 0;
    int choice = menu();
    while (choice != 3) {
        if (choice == 1) {
            system("cls");
            snake* head = init();
            gamestart(head, target);
        }
        else if (choice == 2) {
            target = showranklist();
        }
        choice = menu();
    }
    system("cls");
    printmap();
    setpos(col / 2, row / 2);
    cout << "�ټ�";
    return 0;
}
