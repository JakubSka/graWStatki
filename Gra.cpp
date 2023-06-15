
#include "Gra.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>

using namespace std;
int Gra::how_many_hits_made_player = 0;
int Gra::how_many_hits_made_computer = 0;

Gra::Gra()
{
    srand(time(NULL));

    char wybor;

    while (true) {
        cout << "Jak chcesz grać [1 - PvPC, 2 - PCvPC, 3 - PvP]?" << endl;
        wybor = _getch();
        if (wybor == '1') {
            while (true) {
                cout << "Czy chcesz widziec statki przeciwnika [1 tak - 0 nie)?" << endl;
                wybor = _getch();
                if (wybor == '1') {
                    is_board_visible = true;
                    break;
                }
                else if (wybor == '0') {
                    is_board_visible = false;
                    break;
                }
            }
            system("cls");
            while (true) {
                cout << "Czy ustawic statki automatycznie statki [1 tak - 0 nie)?" << endl;
                wybor = _getch();
                if (wybor == '1') {
                    Gra::set_player_ships_on_board_auto(pPlayerBoard, pPlayerShipFragments);
                    cout << "Tutaj jest plansza gracza" << endl;
                    pPlayerBoard->print_board(is_board_visible);
                    break;
                }
                else if (wybor == '0') {
                    Gra::set_player_ships_on_board(pPlayerBoard, pPlayerShipFragments);
                    break;
                }
            }

            Gra::set_enemy_ships_on_board(pEnemyBoard, pEnemyShipFragments);

            Gra::game_loop(pEnemyBoard, pEnemyShipFragments, pPlayerBoard, pPlayerShipFragments);

            cout << "Game Over!" << endl;
            break;
        }if (wybor == '2') {
            is_board_visible = true;

            system("cls");
            Gra::set_player_ships_on_board_auto(pPlayerBoard, pPlayerShipFragments);
            cout << "Tutaj jest plansza gracza" << endl;
            pPlayerBoard->print_board(is_board_visible);

            Gra::set_enemy_ships_on_board(pEnemyBoard, pEnemyShipFragments);

            Gra::game_loop_PC(pEnemyBoard, pEnemyShipFragments, pPlayerBoard, pPlayerShipFragments);

            cout << "Game Over!" << endl;
            break;
        }

        
        if (wybor == '3') {
        
            while (true) {
            
                cout << "Czy chcesz widziec statki przeciwnika [1 tak - 0 nie)?" << endl;

                wybor = _getch();
                if (wybor == '1') {

                    is_board_visible = true;

                    break;
                }
                else if (wybor == '0') {
                    is_board_visible = false;
                    break;
                }
            }
            while (true) {
                cout << "Czy ustawic statki automatycznie statki [1 tak - 0 nie)?" << endl;
                
                wybor = _getch();
             
                if (wybor == '1') {
                    Gra::set_player_ships_on_board_auto(pPlayerBoard, pPlayerShipFragments);
                
                    cout << "Tutaj jest plansza gracza" << endl;
                    pPlayerBoard->print_board(is_board_visible);
                    break;
                }
                else if (wybor == '0') {
                    Gra::set_player_ships_on_board(pPlayerBoard, pPlayerShipFragments);
                    break;
                }
            }

            while (true) {
                cout << "Czy chcesz widziec statki przeciwnika [1 tak - 0 nie)?" << endl;
                wybor = _getch();
                if (wybor == '1') {
                    is_board_visible = true;
                    break;
                }
                else if (wybor == '0') {
                    is_board_visible = false;
                    break;
                }
            }

            while (true) {
                cout << "Czy ustawic statki automatycznie statki [1 tak - 0 nie)?" << endl;
                wybor = _getch();
                if (wybor == '1') {
                    Gra::set_player_ships_on_board_auto(pEnemyBoard, pEnemyShipFragments);
                    cout << "Tutaj jest plansza gracza" << endl;
                    pEnemyBoard->print_board(is_board_visible);
                    break;
                }
                else if (wybor == '0') {
                    Gra::set_player_ships_on_board(pEnemyBoard, pEnemyShipFragments);
                    break;
                }
            }

            Gra::game_loop_pp(pEnemyBoard, pEnemyShipFragments, pPlayerBoard, pPlayerShipFragments);

            cout << "Game Over!" << endl;
            break;
        }
    }
}

void Gra::print_ships_data(Statek* pEnemyShipFragments, int how_many_fragments) {
    for (int i = 0; i < how_many_fragments; i++) {
        pEnemyShipFragments[i].print_data();
    }
}

void Gra::game_loop(Plansza* pEnemyBoard, Statek* pEnemyShipFragments, Plansza* pPlayerBoard, Statek* pPlayerShipFragments) {

    while (true) {

        player_shooting(pEnemyBoard, pEnemyShipFragments);
        cout << "Ile uderzen zrobil gracz" << how_many_hits_made_player << endl;
        if (how_many_hits_made_player == how_many_fragments) {
            system("cls");
            cout << "Gracz jest zwycięzcą!" << endl;
            break;
        }

        cout << "________________________" << endl << endl;
        computer_shooting(pPlayerBoard, pPlayerShipFragments);
        cout << "Ile uderzen zrobil komputer" << how_many_hits_made_computer << endl;
        if (how_many_hits_made_computer == how_many_fragments) {
            system("cls");
            cout << "COMPUTER IS WINNER!" << endl;
            break;
        }
    }
}

void Gra::player_shooting(Plansza* pEnemyBoard, Statek* pEnemyShipFragments) {


    cout << "Tutaj jest plansza przeciwnika" << endl;
    pEnemyBoard->print_board(is_board_visible);

    cout << "Podaj wspolrzedna x do ostrzalu [1-30]: " << endl;
    int temp_x = Gra::get_cordinates((pEnemyBoard->get_length_of_board()) - 2);

    cout << "Podaj wspolrzedna y do ostrzalu [1-30]: " << endl;
    int temp_y = Gra::get_cordinates((pEnemyBoard->get_length_of_board()) - 2);


    if (pEnemyBoard->get_field(temp_x, temp_y) == '5') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pEnemyShipFragments, how_many_fragments);

        increase_damage(pEnemyShipFragments, pEnemyShipFragments[which_fragment].get_id());

        if (pEnemyShipFragments[which_fragment].get_damage() == pEnemyShipFragments[which_fragment].get_length()) {
            cout << "LODZ ZATOPIONA" << endl;
            exclude_positions(pEnemyBoard, pEnemyShipFragments, which_fragment, pEnemyShipFragments[which_fragment].get_id());

        }
        else
            cout << "TRAFIONA" << endl;

        pEnemyBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_player++;
    }else if (pEnemyBoard->get_field(temp_x, temp_y) == '4') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pEnemyShipFragments, how_many_fragments);

        increase_damage(pEnemyShipFragments, pEnemyShipFragments[which_fragment].get_id());

        if (pEnemyShipFragments[which_fragment].get_damage() == pEnemyShipFragments[which_fragment].get_length()) {
            cout << "LODZ ZATOPIONA" << endl;
            exclude_positions(pEnemyBoard, pEnemyShipFragments, which_fragment, pEnemyShipFragments[which_fragment].get_id());

        }
        else
            cout << "TRAFIONA" << endl;

        pEnemyBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_player++;
    }else if (pEnemyBoard->get_field(temp_x, temp_y) == '3') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pEnemyShipFragments, how_many_fragments);

        increase_damage(pEnemyShipFragments, pEnemyShipFragments[which_fragment].get_id());

        if (pEnemyShipFragments[which_fragment].get_damage() == pEnemyShipFragments[which_fragment].get_length()) {
            cout << "LODZ ZATOPIONA" << endl;
            exclude_positions(pEnemyBoard, pEnemyShipFragments, which_fragment, pEnemyShipFragments[which_fragment].get_id());

        }
        else
            cout << "TRAFIONA" << endl;

        pEnemyBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_player++;
    }else if (pEnemyBoard->get_field(temp_x, temp_y) == '2') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pEnemyShipFragments, how_many_fragments);

        increase_damage(pEnemyShipFragments, pEnemyShipFragments[which_fragment].get_id());

        if (pEnemyShipFragments[which_fragment].get_damage() == pEnemyShipFragments[which_fragment].get_length()) {
            cout << "LODZ ZATOPIONA" << endl;
            exclude_positions(pEnemyBoard, pEnemyShipFragments, which_fragment, pEnemyShipFragments[which_fragment].get_id());

        }
        else
            cout << "TRAFIONA" << endl;

        pEnemyBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_player++;
    }
    else if (pEnemyBoard->get_field(temp_x, temp_y) == 'X' || pEnemyBoard->get_field(temp_x, temp_y) == 'o') {
        cout << "\ttu juz strzelalismy!" << endl;
    }
    else {
        cout << "\tKomunikat: Pudlo!!" << endl;
        pEnemyBoard->set_field(temp_x, temp_y, 'o');
    }
}

void Gra::computer_shooting(Plansza* pPlayerBoard, Statek* pPlayerShipFragments) {

    int temp_x, temp_y;

    while (true) {
        temp_x = rand() % 30 + 1;
        temp_y = rand() % 30 + 1;
        if (pPlayerBoard->get_field(temp_x, temp_y) == '*')
            break;
        if (pPlayerBoard->get_field(temp_x, temp_y) == '5')
            break;
        if (pPlayerBoard->get_field(temp_x, temp_y) == '4')
            break;
        if (pPlayerBoard->get_field(temp_x, temp_y) == '3')
            break;
        if (pPlayerBoard->get_field(temp_x, temp_y) == '2')
            break;
    }

    cout << "Komputer wylosowal wspolrzedna x: " << temp_x << endl;
    cout << "Komputer wylosowal wspolrzedna y: " << temp_y << endl;


    if (pPlayerBoard->get_field(temp_x, temp_y) == '5') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pPlayerShipFragments, how_many_fragments);

        increase_damage(pPlayerShipFragments, pPlayerShipFragments[which_fragment].get_id());

        if (pPlayerShipFragments[which_fragment].get_damage() == pPlayerShipFragments[which_fragment].get_length()) {
            cout << "KOMPUTER ZATOPIL LODZ GRACZA!!" << endl;
            exclude_positions(pPlayerBoard, pPlayerShipFragments, which_fragment, pPlayerShipFragments[which_fragment].get_id());

        }
        else
            cout << "KOMPUTER TRAFIL ALE LODZ PLYNIE!!" << endl;

        pPlayerBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_computer++;
    } else if (pPlayerBoard->get_field(temp_x, temp_y) == '4') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pPlayerShipFragments, how_many_fragments);

        increase_damage(pPlayerShipFragments, pPlayerShipFragments[which_fragment].get_id());

        if (pPlayerShipFragments[which_fragment].get_damage() == pPlayerShipFragments[which_fragment].get_length()) {
            cout << "KOMPUTER ZATOPIL LODZ GRACZA!!" << endl;
            exclude_positions(pPlayerBoard, pPlayerShipFragments, which_fragment, pPlayerShipFragments[which_fragment].get_id());

        }
        else
            cout << "KOMPUTER TRAFIL ALE LODZ PLYNIE!!" << endl;

        pPlayerBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_computer++;
    }else if (pPlayerBoard->get_field(temp_x, temp_y) == '3') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pPlayerShipFragments, how_many_fragments);

        increase_damage(pPlayerShipFragments, pPlayerShipFragments[which_fragment].get_id());

        if (pPlayerShipFragments[which_fragment].get_damage() == pPlayerShipFragments[which_fragment].get_length()) {
            cout << "KOMPUTER ZATOPIL LODZ GRACZA!!" << endl;
            exclude_positions(pPlayerBoard, pPlayerShipFragments, which_fragment, pPlayerShipFragments[which_fragment].get_id());

        }
        else
            cout << "KOMPUTER TRAFIL ALE LODZ PLYNIE!!" << endl;

        pPlayerBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_computer++;
    }else if (pPlayerBoard->get_field(temp_x, temp_y) == '2') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pPlayerShipFragments, how_many_fragments);

        increase_damage(pPlayerShipFragments, pPlayerShipFragments[which_fragment].get_id());

        if (pPlayerShipFragments[which_fragment].get_damage() == pPlayerShipFragments[which_fragment].get_length()) {
            cout << "KOMPUTER ZATOPIL LODZ GRACZA!!" << endl;
            exclude_positions(pPlayerBoard, pPlayerShipFragments, which_fragment, pPlayerShipFragments[which_fragment].get_id());

        }
        else
            cout << "KOMPUTER TRAFIL ALE LODZ PLYNIE!!" << endl;

        pPlayerBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_computer++;
    }
    else {
        cout << "\tKOMPUTER Pudluje!!" << endl;
        pPlayerBoard->set_field(temp_x, temp_y, 'o');
    }
    cout << "Komputer widzi cos takiego po strzale: " << endl;
    pPlayerBoard->print_board(1);
}

void Gra::exclude_positions(Plansza* pEnemyBoard, Statek* pEnemyShipFragments, int which_fragment, int id) {

    int starting_x, starting_y;
    int orientation = pEnemyShipFragments[which_fragment].get_plane();

    for (int i = 0; i < how_many_fragments; i++) {
        if (pEnemyShipFragments[i].get_id() == id) {
            starting_x = pEnemyShipFragments[i].get_x();
            starting_y = pEnemyShipFragments[i].get_y();
            break;
        }
    }

    if (orientation) {
        for (int i = 0; i < (2 + pEnemyShipFragments[which_fragment].get_length()); i++) {
            pEnemyBoard->set_field((starting_x - 1), (starting_y - 1 + i), 'o');
            pEnemyBoard->set_field((starting_x + 1), (starting_y - 1 + i), 'o');
            pEnemyBoard->set_field((starting_x), (starting_y - 1), 'o');
            pEnemyBoard->set_field((starting_x), (starting_y + (pEnemyShipFragments[which_fragment].get_length())), 'o');
        }
    }
    else {
        for (int i = 0; i < (2 + pEnemyShipFragments[which_fragment].get_length()); i++) {
            pEnemyBoard->set_field((starting_x - 1 + i), (starting_y - 1), 'o');
            pEnemyBoard->set_field((starting_x - 1), (starting_y), 'o');
            pEnemyBoard->set_field((starting_x + (pEnemyShipFragments[which_fragment].get_length())), (starting_y), 'o');
            pEnemyBoard->set_field((starting_x - 1 + i), (starting_y + 1), 'o');
        }
    }
}

void Gra::increase_damage(Statek* pEnemyShipFragments, int id) {

    for (int i = 0; i < how_many_fragments; i++) {
        if (pEnemyShipFragments[i].get_id() == id) {
            pEnemyShipFragments[i].increase_damage();
        }
    }
}

int Gra::detect_which_fragment_was_hited(int x, int y, Statek* pEnemyShipFragments, int how_many_fragments) {
    int i = 0;
    for (i = 0; i < how_many_fragments; i++) {
        if ((pEnemyShipFragments[i].get_x() == x) &&
            (pEnemyShipFragments[i].get_y() == y))
            break;
    }
    return i;
}

void Gra::set_enemy_ships_on_board(Plansza* pEnemyBoard, Statek* pEnemyShipFragmentssss) {


    int temp_x, temp_y;
    bool plane;
    int quantity_of_ships = 0;
    int how_many_ships_builded = 0;
    int position_of_ships_framgents_table = 0;
    cout << " Podaj ilosc nastepjuacych masztowcow 5,4,3,2: ";
    int maszt5, maszt4, maszt3, maszt2;
    cin >> maszt5;
    cin >> maszt4;
    cin >> maszt3;
    cin >> maszt2;
    for (int i = 0; i < maszt5; i++) {
        plane = int(rand() % 2);
        if (plane) {
            temp_x = rand() % 30 + 1;
            temp_y = rand() % 26 + 1;
            for (int i = 0; i < 5; i++, position_of_ships_framgents_table++) {
                pEnemyBoard->set_field(temp_x, temp_y + i, '5');
                pEnemyShipFragments[position_of_ships_framgents_table].
                    set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, 4, 0, plane);
            }
        }
        else {
            temp_x = rand() % 26 + 1;
            temp_y = rand() % 30 + 1;
            for (int i = 0; i < 5; i++, position_of_ships_framgents_table++) {
                pEnemyBoard->set_field(temp_x + i, temp_y, '5');
                pEnemyShipFragments[position_of_ships_framgents_table].
                    set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, 4, 0, plane);
            }
        }
        how_many_ships_builded++;
    }

    while (quantity_of_ships < maszt4) {
        while (true) {
            while (true) {
                temp_x = rand() % 27 + 1;
                temp_y = rand() % 27 + 1;
                if (isAreaClean(pEnemyBoard, temp_x, temp_y)) break;
            }

            if (isAreaClean(pEnemyBoard, temp_x + 2, temp_y)) {
                for (int i = 0; i < 4; i++, position_of_ships_framgents_table++) {
                    pEnemyBoard->set_field(temp_x + i, temp_y, '4');
                    pEnemyShipFragments[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, 3, 0, 0);
                }
                break;
            }
            else if (isAreaClean(pEnemyBoard, temp_x, temp_y + 2)) {
                for (int i = 0; i < 4; i++, position_of_ships_framgents_table++) {
                    pEnemyBoard->set_field(temp_x, temp_y + i, '4');
                    pEnemyShipFragments[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, 3, 0, 1);
                }
                break;
            }
        }
        quantity_of_ships++;
        how_many_ships_builded++;
    }

    quantity_of_ships = 0;

    while (quantity_of_ships < maszt3) {
        while (true) {
            while (true) {
                temp_x = rand() % 28 + 1;
                temp_y = rand() % 28 + 1;
                if (isAreaClean(pEnemyBoard, temp_x, temp_y)) break;
            }


            if (isAreaClean(pEnemyBoard, temp_x + 1, temp_y)) {
                for (int i = 0; i < 3; i++, position_of_ships_framgents_table++) {
                    pEnemyBoard->set_field(temp_x + i, temp_y, '3');
                    pEnemyShipFragments[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, 2, 0, 0);
                }
                break;
            }
            else if (isAreaClean(pEnemyBoard, temp_x, temp_y + 1)) {
                for (int i = 0; i < 3; i++, position_of_ships_framgents_table++) {
                    pEnemyBoard->set_field(temp_x, temp_y + i, '3');
                    pEnemyShipFragments[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, 2, 0, 1);
                }
                break;
            }
        }
        quantity_of_ships++;
        how_many_ships_builded++;
    }

    quantity_of_ships = 0;

    while (quantity_of_ships < maszt2) {
        while (true) {
            while (true) {
                temp_x = rand() % 29 + 1;
                temp_y = rand() % 29 + 1;
                if (isAreaClean(pEnemyBoard, temp_x, temp_y)) break;
            }


            if (isAreaClean(pEnemyBoard, temp_x + 1, temp_y)) {
                for (int i = 0; i < 2; i++, position_of_ships_framgents_table++) {
                    pEnemyBoard->set_field(temp_x + i, temp_y, '2');
                    pEnemyShipFragments[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, 2, 0, 0);
                }
                break;
            }
            else if (isAreaClean(pEnemyBoard, temp_x, temp_y + 1)) {
                for (int i = 0; i < 2; i++, position_of_ships_framgents_table++) {
                    pEnemyBoard->set_field(temp_x, temp_y + i, '2');
                    pEnemyShipFragments[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, 2, 0, 1);
                }
                break;
            }
        }
        quantity_of_ships++;
        how_many_ships_builded++;
    }
}

void Gra::set_player_ships_on_board(Plansza* pPlayerBoard, Statek* pPlayerShipFragments) {

    int temp_x, temp_y;
    bool plane;
    int quantity_of_ships = 0;
    int how_many_ships_builded = 0;
    int position_of_ships_framgents_table = 0;
    int size_of_currently_builded_ship;
    cout << "ile chcesz wybudowac statkow 5 masztowych?";
    int num;
    cin >> num;

    for (int i = 0; i < num; i++) {

        size_of_currently_builded_ship = 5;

        plane = get_plane_from_player(size_of_currently_builded_ship);

        cout << "Podaj wspolrzedna x do ustawienia statku: " << endl;
        temp_x = Gra::get_cordinates(plane ? 30 : 26);

        cout << "Podaj wspolrzedna y do ustawienia statku : " << endl;
        temp_y = Gra::get_cordinates(plane ? 26 : 30);

        if (plane) {
            for (int i = 0; i < size_of_currently_builded_ship; i++, position_of_ships_framgents_table++) {
                pPlayerBoard->set_field(temp_x, temp_y + i, '5');
                pPlayerShipFragments[position_of_ships_framgents_table].
                    set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, size_of_currently_builded_ship, 0, plane);
            }
        }
        else {
            for (int i = 0; i < size_of_currently_builded_ship; i++, position_of_ships_framgents_table++) {
                pPlayerBoard->set_field(temp_x + i, temp_y, '5');
                pPlayerShipFragments[position_of_ships_framgents_table].
                    set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, size_of_currently_builded_ship, 0, plane);
            }
        }
        how_many_ships_builded++;
        pPlayerBoard->print_board(1);
    }
    cout << "ile chcesz wybudowac statkow 4 masztowych?";
 
    cin >> num;

    

        size_of_currently_builded_ship = 4;
        while (quantity_of_ships < num) {
            while (true) {
                while (true) {
                    plane = get_plane_from_player(size_of_currently_builded_ship);
                    cout << "Podaj wspolrzedna x do ustawienia statku: " << endl;
                    temp_x = Gra::get_cordinates(plane ? 30 : 27);
                    cout << "Podaj wspolrzedna y do ustawienia statku : " << endl;
                    temp_y = Gra::get_cordinates(plane ? 27 : 30);

                    if ((isAreaClean(pPlayerBoard, temp_x, temp_y)) && (isAreaClean(pPlayerBoard, (plane ? temp_x : (temp_x + 2)), (plane ? (temp_y + 2) : temp_y))))
                        break;
                }

                if (!plane) {
                    for (int i = 0; i < size_of_currently_builded_ship; i++, position_of_ships_framgents_table++) {
                        pPlayerBoard->set_field(temp_x + i, temp_y, '4');
                        pEnemyShipFragments[position_of_ships_framgents_table].
                            set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, size_of_currently_builded_ship, 0, 0);
                    }
                    break;
                }
                else {
                    for (int i = 0; i < size_of_currently_builded_ship; i++, position_of_ships_framgents_table++) {
                        pPlayerBoard->set_field(temp_x, temp_y + i, '4');
                        pEnemyShipFragments[position_of_ships_framgents_table].
                            set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, size_of_currently_builded_ship, 0, 1);
                    }
                    break;
                }
            }
            quantity_of_ships++;
            how_many_ships_builded++;
            pPlayerBoard->print_board(1);
        }

        quantity_of_ships = 0;
    
    cout << "ile chcesz wybudowac statkow 3 masztowych?";
 
    cin >> num;

    
        size_of_currently_builded_ship = 3;
        while (quantity_of_ships < num) {
            while (true) {
                while (true) {
                    plane = get_plane_from_player(size_of_currently_builded_ship);
                    cout << "Podaj wspolrzedna x do ustawienia statku: " << endl;
                    temp_x = Gra::get_cordinates(plane ? 30 : 28);
                    cout << "Podaj wspolrzedna y do ustawienia statku : " << endl;
                    temp_y = Gra::get_cordinates(plane ? 28 : 30);

                    if ((isAreaClean(pPlayerBoard, temp_x, temp_y)) && (isAreaClean(pPlayerBoard, (plane ? temp_x : (temp_x + 1)), (plane ? (temp_y + 1) : temp_y))))
                        break;
                }

                if (!plane) {
                    for (int i = 0; i < size_of_currently_builded_ship; i++, position_of_ships_framgents_table++) {
                        pPlayerBoard->set_field(temp_x + i, temp_y, '3');
                        pEnemyShipFragments[position_of_ships_framgents_table].
                            set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, size_of_currently_builded_ship, 0, 0);
                    }
                    break;
                }
                else {
                    for (int i = 0; i < size_of_currently_builded_ship; i++, position_of_ships_framgents_table++) {
                        pPlayerBoard->set_field(temp_x, temp_y + i, '3');
                        pEnemyShipFragments[position_of_ships_framgents_table].
                            set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, size_of_currently_builded_ship, 0, 1);
                    }
                    break;
                }
            }
            quantity_of_ships++;
            how_many_ships_builded++;
            pPlayerBoard->print_board(1);
        }

        quantity_of_ships = 0;
    
    cout << "ile chcesz wybudowac statkow 2 masztowych?";
   
    cin >> num;

    
        size_of_currently_builded_ship = 2;
        while (quantity_of_ships < num) {
            while (true) {
                while (true) {
                    plane = get_plane_from_player(size_of_currently_builded_ship);
                    cout << "Podaj wspolrzedna x do ustawienia statku: " << endl;
                    temp_x = Gra::get_cordinates(plane ? 30 : 29);
                    cout << "Podaj wspolrzedna y do ustawienia statku : " << endl;
                    temp_y = Gra::get_cordinates(plane ? 29 : 30);

                    if ((isAreaClean(pPlayerBoard, temp_x, temp_y)) && (isAreaClean(pPlayerBoard, (plane ? temp_x : (temp_x + 1)), (plane ? (temp_y + 1) : temp_y))))
                        break;
                }

                if (!plane) {
                    for (int i = 0; i < size_of_currently_builded_ship; i++, position_of_ships_framgents_table++) {
                        pPlayerBoard->set_field(temp_x + i, temp_y, '2');
                        pEnemyShipFragments[position_of_ships_framgents_table].
                            set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, size_of_currently_builded_ship, 0, 0);
                    }
                    break;
                }
                else {
                    for (int i = 0; i < size_of_currently_builded_ship; i++, position_of_ships_framgents_table++) {
                        pPlayerBoard->set_field(temp_x, temp_y + i, '2');
                        pEnemyShipFragments[position_of_ships_framgents_table].
                            set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, size_of_currently_builded_ship, 0, 1);
                    }
                    break;
                }
            }
            quantity_of_ships++;
            how_many_ships_builded++;
            pPlayerBoard->print_board(1);
        
    }
    system("cls");
    cout << "Koniec funkcji ustaw plansze przeciwnika  WCISNIJ DOWOLNY KLAWISZ!!!" << endl << endl;
    _getch();
}

bool Gra::isAreaClean(Plansza* pEnemyBoard, int temp_x, int temp_y) {

    if (((pEnemyBoard->get_field(temp_x - 1, temp_y - 1) == '*') || (pEnemyBoard->get_field(temp_x - 1, temp_y - 1) == 'o')) &&
        ((pEnemyBoard->get_field(temp_x, temp_y - 1) == '*') || (pEnemyBoard->get_field(temp_x, temp_y - 1) == 'o')) &&
        
        ((pEnemyBoard->get_field(temp_x + 1, temp_y - 1) == '*') || (pEnemyBoard->get_field(temp_x + 1, temp_y - 1) == 'o')) &&
       
        ((pEnemyBoard->get_field(temp_x - 1, temp_y) == '*') || (pEnemyBoard->get_field(temp_x - 1, temp_y) == 'o')) &&
        
        ((pEnemyBoard->get_field(temp_x, temp_y) == '*') || (pEnemyBoard->get_field(temp_x, temp_y) == 'o')) &&
        ((pEnemyBoard->get_field(temp_x + 1, temp_y) == '*') || (pEnemyBoard->get_field(temp_x + 1, temp_y) == 'o')) &&
        
        ((pEnemyBoard->get_field(temp_x - 1, temp_y + 1) == '*') || (pEnemyBoard->get_field(temp_x - 1, temp_y + 1) == 'o')) &&
        
        ((pEnemyBoard->get_field(temp_x, temp_y + 1) == '*') || (pEnemyBoard->get_field(temp_x, temp_y + 1) == 'o')) &&
        ((pEnemyBoard->get_field(temp_x + 1, temp_y + 1) == '*') || (pEnemyBoard->get_field(temp_x + 1, temp_y + 1) == 'o')))
        return true;
    else return false;
}

bool Gra::get_plane_from_player(int howBigIsIt) {
    char choose;
    while (true) {
        cout << "Podaj plaszczyzne ustawienia " << howBigIsIt << "masztowca (1 - pion, 0 - poziom)" << endl;
        choose = _getch();
        if (choose == '1') {
            return true;
            break;
        }
        else if (choose == '0') {
            return false;
            break;
        }
    }
}

short int Gra::get_cordinates(int maximum) {

    int temp;

    do {
        cin >> temp;
        if (temp<1 || temp>maximum) cout << "Blad, jeszcze raz!" << endl;
        else break;
    } while (true);

    return temp;
}

void Gra::set_board_visibility(int is_board_visible) {
    this->is_board_visible = is_board_visible;
}
bool Gra::get_board_visibility() {
    return is_board_visible;
}

Gra::~Gra()
{
    delete[] pEnemyShipFragments;
    pEnemyShipFragments = NULL;
}

void Gra::set_player_ships_on_board_auto(Plansza* pBoard, Statek* pShipFragmentssss) {


    int temp_x, temp_y;
    bool plane;
    int quantity_of_ships = 0;
    int how_many_ships_builded = 0;
    int position_of_ships_framgents_table = 0;
    cout << " Podaj ilosc nastepjuacych masztowcow 5,4,3,2: ";
    int maszt5, maszt4, maszt3, maszt2;
    cin >> maszt5;
    cin >> maszt4;
    cin >> maszt3;
    cin >> maszt2;

    for (int i = 0; i < maszt5; i++) {
        plane = int(rand() % 2);
        if (plane) {
            temp_x = rand() % 30 + 1;
            temp_y = rand() % 26 + 1;
            for (int i = 0; i < 5; i++, position_of_ships_framgents_table++) {
                pBoard->set_field(temp_x, temp_y + i, '5');
                pShipFragmentssss[position_of_ships_framgents_table].
                    set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, 4, 0, plane);
            }
        }
        else {
            temp_x = rand() % 26 + 1;
            temp_y = rand() % 30 + 1;
            for (int i = 0; i < 5; i++, position_of_ships_framgents_table++) {
                pBoard->set_field(temp_x + i, temp_y, '5');
                pShipFragmentssss[position_of_ships_framgents_table].
                    set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, 4, 0, plane);
            }
        }
        how_many_ships_builded++;
    }
    while (quantity_of_ships < maszt4) {
        while (true) {
            while (true) {
                temp_x = rand() % 27 + 1;
                temp_y = rand() % 27 + 1;
                if (isAreaClean(pBoard, temp_x, temp_y)) break;
            }

            if (isAreaClean(pBoard, temp_x + 2, temp_y)) {
                for (int i = 0; i < 4; i++, position_of_ships_framgents_table++) {
                    pBoard->set_field(temp_x + i, temp_y, '4');
                    pShipFragmentssss[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, 3, 0, 0);
                }
                break;
            }
            else if (isAreaClean(pBoard, temp_x, temp_y + 2)) {
                for (int i = 0; i < 4; i++, position_of_ships_framgents_table++) {
                    pBoard->set_field(temp_x, temp_y + i, '4');
                    pShipFragmentssss[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, 3, 0, 1);
                }
                break;
            }
        }
        quantity_of_ships++;
        how_many_ships_builded++;
    }

    quantity_of_ships = 0;

    while (quantity_of_ships < maszt3) {
        while (true) {
            while (true) {
                temp_x = rand() % 28 + 1;
                temp_y = rand() % 28 + 1;
                if (isAreaClean(pBoard, temp_x, temp_y)) break;
            }


            if (isAreaClean(pBoard, temp_x + 1, temp_y)) {
                for (int i = 0; i < 3; i++, position_of_ships_framgents_table++) {
                    pBoard->set_field(temp_x + i, temp_y, '3');
                    pShipFragmentssss[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, 2, 0, 0);
                }
                break;
            }
            else if (isAreaClean(pBoard, temp_x, temp_y + 1)) {
                for (int i = 0; i < 3; i++, position_of_ships_framgents_table++) {
                    pBoard->set_field(temp_x, temp_y + i, '3');
                    pShipFragmentssss[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, 2, 0, 1);
                }
                break;
            }
        }
        quantity_of_ships++;
        how_many_ships_builded++;
    }

    quantity_of_ships = 0;

    while (quantity_of_ships < maszt2) {
        while (true) {
            while (true) {
                temp_x = rand() % 29 + 1;
                temp_y = rand() % 29 + 1;
                if (isAreaClean(pBoard, temp_x, temp_y)) break;
            }


            if (isAreaClean(pBoard, temp_x + 1, temp_y)) {
                for (int i = 0; i < 2; i++, position_of_ships_framgents_table++) {
                    pBoard->set_field(temp_x + i, temp_y, '2');
                    pShipFragmentssss[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x + i, temp_y, 2, 0, 0);
                }
                break;
            }
            else if (isAreaClean(pBoard, temp_x, temp_y + 1)) {
                for (int i = 0; i < 2; i++, position_of_ships_framgents_table++) {
                    pBoard->set_field(temp_x, temp_y + i, '2');
                    pShipFragmentssss[position_of_ships_framgents_table].
                        set_parameters(1 + how_many_ships_builded, temp_x, temp_y + i, 2, 0, 1);
                }
                break;
            }
        }
        quantity_of_ships++;
        how_many_ships_builded++;
    }
}
void Gra::computer2_shooting(Plansza* pPlayerBoard, Statek* pPlayerShipFragments) {

    int temp_x, temp_y;

    while (true) {
        temp_x = rand() % 30 + 1;
        temp_y = rand() % 30 + 1;
        if (pPlayerBoard->get_field(temp_x, temp_y) == '*')
            break;
        if (pPlayerBoard->get_field(temp_x, temp_y) == '5')
            break;
        if (pPlayerBoard->get_field(temp_x, temp_y) == '4')
            break;
        if (pPlayerBoard->get_field(temp_x, temp_y) ==  '3' )
            break;
        if (pPlayerBoard->get_field(temp_x, temp_y) == '2')
            break;
    }

    cout << "Komputer wylosowal wspolrzedna x: " << temp_x << endl;
    cout << "Komputer wylosowal wspolrzedna y: " << temp_y << endl;


    if (pPlayerBoard->get_field(temp_x, temp_y) == '5') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pPlayerShipFragments, how_many_fragments);

        increase_damage(pPlayerShipFragments, pPlayerShipFragments[which_fragment].get_id());

        if (pPlayerShipFragments[which_fragment].get_damage() == pPlayerShipFragments[which_fragment].get_length()) {
            cout << "KOMPUTER ZATOPIL LODZ GRACZA!!" << endl;
            exclude_positions(pPlayerBoard, pPlayerShipFragments, which_fragment, pPlayerShipFragments[which_fragment].get_id());

        }
        else
            cout << "KOMPUTER TRAFIL" << endl;

        pPlayerBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_computer++;
    }
    else if (pPlayerBoard->get_field(temp_x, temp_y) == '4') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pPlayerShipFragments, how_many_fragments);

        increase_damage(pPlayerShipFragments, pPlayerShipFragments[which_fragment].get_id());

        if (pPlayerShipFragments[which_fragment].get_damage() == pPlayerShipFragments[which_fragment].get_length()) {
            cout << "KOMPUTER ZATOPIL LODZ GRACZA!!" << endl;
            exclude_positions(pPlayerBoard, pPlayerShipFragments, which_fragment, pPlayerShipFragments[which_fragment].get_id());

        }
        else
            cout << "KOMPUTER TRAFIL" << endl;

        pPlayerBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_computer++;
    }
    else if (pPlayerBoard->get_field(temp_x, temp_y) == '3') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pPlayerShipFragments, how_many_fragments);

        increase_damage(pPlayerShipFragments, pPlayerShipFragments[which_fragment].get_id());

        if (pPlayerShipFragments[which_fragment].get_damage() == pPlayerShipFragments[which_fragment].get_length()) {
            cout << "KOMPUTER ZATOPIL LODZ GRACZA!!" << endl;
            exclude_positions(pPlayerBoard, pPlayerShipFragments, which_fragment, pPlayerShipFragments[which_fragment].get_id());

        }
        else
            cout << "KOMPUTER TRAFIL" << endl;

        pPlayerBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_computer++;
    }
    else if (pPlayerBoard->get_field(temp_x, temp_y) == '2') {

        int which_fragment = detect_which_fragment_was_hited(temp_x, temp_y, pPlayerShipFragments, how_many_fragments);

        increase_damage(pPlayerShipFragments, pPlayerShipFragments[which_fragment].get_id());

        if (pPlayerShipFragments[which_fragment].get_damage() == pPlayerShipFragments[which_fragment].get_length()) {
            cout << "KOMPUTER ZATOPIL LODZ GRACZA!!" << endl;
            exclude_positions(pPlayerBoard, pPlayerShipFragments, which_fragment, pPlayerShipFragments[which_fragment].get_id());

        }
        else
            cout << "KOMPUTER TRAFIL" << endl;

        pPlayerBoard->set_field(temp_x, temp_y, 'X');
        how_many_hits_made_computer++;
    }
    else {
        cout << "\tKOMPUTER Pudluje!!" << endl;
        pPlayerBoard->set_field(temp_x, temp_y, 'o');
    }
    cout << "Komputer widzi cos takiego po strzale: " << endl;
    pPlayerBoard->print_board(1);
}
void Gra::game_loop_PC(Plansza* pEnemyBoard, Statek* pEnemyShipFragments, Plansza* pPlayerBoard, Statek* pPlayerShipFragments) {

    while (true) {

        computer2_shooting(pEnemyBoard, pEnemyShipFragments);
        cout << "Ile uderzen zrobil gracz" << how_many_hits_made_player << endl;
        if (how_many_hits_made_player == how_many_fragments) {
            system("cls");
            cout << "Komputer 1 jest zwycięzcą!" << endl;
            break;
        }

        cout << "________________________" << endl << endl;
        computer_shooting(pPlayerBoard, pPlayerShipFragments);
        cout << "Ile uderzen zrobil komputer" << how_many_hits_made_computer << endl;
        if (how_many_hits_made_computer == how_many_fragments) {
            system("cls");
            cout << "Komputer 2 jest zwycięzcą!" << endl;
            break;
        }
    }
}
void Gra::game_loop_pp(Plansza* pEnemyBoard, Statek* pEnemyShipFragments, Plansza* pPlayerBoard, Statek* pPlayerShipFragments) {

    while (true) {

        player_shooting(pEnemyBoard, pEnemyShipFragments);
        cout << "Ile uderzen zrobil gracz 1: " << how_many_hits_made_player << endl;
        if (how_many_hits_made_player == how_many_fragments) {
            system("cls");
            cout << "Gracz 1 jest zwycięzcą!" << endl;
            break;
        }

        cout << "________________________" << endl << endl;
        player_shooting(pPlayerBoard, pPlayerShipFragments);
        cout << "Ile uderzen zrobil gracz 2: " << how_many_hits_made_computer << endl;
        if (how_many_hits_made_player == how_many_fragments) {
            system("cls");
            cout << "Gracz 2 jest zwycięzcą!" << endl;
            break;
        }

    }
}