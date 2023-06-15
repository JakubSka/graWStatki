

#include "Statek.h"

#include <iostream>
using namespace std;

Statek::Statek()
{
    set_parameters(0, 0, 0, 0, 0, 0);
}

Statek::~Statek()
{
}

void Statek::print_data() {
    cout << "id" << id << "  "
        << "x" << x << "  "
        << "y" << y << "  "
        << "length" << length << "  "
        << "damage" << damage << "  "
        << "plane" << plane << endl;
}

void Statek::set_parameters(int id, int x, int y, int length_of_ship, int damage, int plane) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->length = length_of_ship;
    this->damage = damage;
    this->plane = plane;

}

void Statek::increase_damage() {
    damage++;
}

int Statek::get_id() {
    return id;
}

void Statek::set_id(int id) {
    this->id = id;
}

int Statek::get_x() {
    return x;
}

void Statek::set_x(int x) {
    this->x = x;
}

int Statek::get_y() {
    return y;
}

void Statek::set_y(int y) {
    this->y = y;
}

int Statek::get_length() {
    return length;
}

void Statek::set_length(int length) {
    this->length = length;
}

int Statek::get_damage() {
    return damage;
}

void Statek::set_damage(int damage) {
    this->damage = damage;
}

int Statek::get_plane() {
    return plane;
}

void Statek::set_plane(int plane) {
    this->plane = plane;
}

