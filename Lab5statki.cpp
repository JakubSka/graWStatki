
#include <iostream>
#include <sstream>
#include "Gra.h"

using namespace std;

class Menu {
public:
    Menu() {
        printMenu();
    }
    void printMenu();
    void about();

};

int main()
{
    Menu menu;
}

void Menu::printMenu() {
    int option = 0;
    do {
        system("cls");
        cout << "Menu: " << endl;
        cout << "\t 1. Game " << endl << "\t 2. Quit" << endl;
        cin >> option;

        switch (option)
        {
        case 1:
        {
            system("cls");
            Gra gra;
            break;
        }
        case 2:
        {
            system("cls");
            cout << endl << "\t****Option 3 [Quit]" << endl;
            break;
        }
        default:
        {
            cout << "\tError, try again!" << endl;
            system("cls");
            break;
        }
        break;
        }
        break;
    } while (option != 3);
}

