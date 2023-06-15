

#include "Plansza.h"

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>

using namespace std;

Plansza::Plansza()
{
    plansza = new char* [dlugoscPlanszy];
    for (int i = 0; i < dlugoscPlanszy; i++) {
        plansza[i] = new char[dlugoscPlanszy];
    }
    initialization(plansza, dlugoscPlanszy);
}

Plansza::~Plansza()
{
    for (int i = 0; i < dlugoscPlanszy; i++)
        delete[] plansza[i];
    delete[] plansza;
    plansza = NULL;
}

void Plansza::initialization(char** plansza, const int length_of_board) {

    for (int i = 0; i < length_of_board; i++) {
        for (int j = 0; j < length_of_board; j++) {
            plansza[i][j] = '*';
        }
    }
}

void Plansza::print_board(bool visibility) {

    for (int i = -1; i < 30; i++) {
        cout.width(4);
        cout << i + 1;
        for (int j = 0; j < 30; j++) {
            if (i != -1) {
                cout.width(3);
                cout << plansza[i][j];
            }
            else {
                cout.width(3);
                cout << j + 1;
            }
        }
        cout << "\n";

    }
}

char Plansza::get_field(int x, int y) {

    return plansza[y][x];
}

void Plansza::set_field(int x, int y, char field) {
    plansza[y][x] = field;
}

const int Plansza::get_length_of_board() {
    return dlugoscPlanszy;
}
