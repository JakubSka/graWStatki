


#include "Plansza.h"
#include "Statek.h"

class Gra {
public:
    Gra();
    virtual ~Gra();

    void game_loop(Plansza* pEnemyBoard, Statek* pEnemyShipFragments, Plansza* pPlayerBoard, Statek* pPlayerShipFragments);

    void player_shooting(Plansza* pEnemyBoard, Statek* pEnemyShipFragments);
    void computer_shooting(Plansza* pPlayerBoard, Statek* pPlayerShipFragments);

    void set_enemy_ships_on_board(Plansza* pEnemyBoard, Statek* pEnemyShipFragments);
    void set_player_ships_on_board(Plansza* pPlayerBoard, Statek* pPlayerShipFragments);
    void set_player_ships_on_board_auto(Plansza* pBoard, Statek* pShipFragmentssss);
    void computer2_shooting(Plansza* pPlayerBoard, Statek* pPlayerShipFragments);
    void game_loop_PC(Plansza* pEnemyBoard, Statek* pEnemyShipFragments, Plansza* pPlayerBoard, Statek* pPlayerShipFragments);
    void game_loop_pp(Plansza* pEnemyBoard, Statek* pEnemyShipFragments, Plansza* pPlayerBoard, Statek* pPlayerShipFragments);

    void print_ships_data(Statek* pEnemyShipFragments, int how_many_fragments);
    short int get_cordinates(int maximum);
    bool isAreaClean(Plansza* pEnemyBoard, int x, int y);
    int detect_which_fragment_was_hited(int x, int y, Statek* pEnemyShipFragments, int how_many_fragments);
    void increase_damage(Statek* pEnemyShipFragments, int id);
    void exclude_positions(Plansza* pEnemyBoard, Statek* pEnemyShipFragments, int which_fragment, int id);
    bool get_plane_from_player(int howBigIsIt);

    void set_board_visibility(int is_board_visible);
    bool get_board_visibility();
    void increment_hits();
    short int get_how_many_hits();



protected:
private:

    static const int how_many_ships = 10;
    static const int how_many_fragments = 20;
    Plansza* pEnemyBoard = new Plansza();
    Plansza* pPlayerBoard = new Plansza();
    Statek* pEnemyShipFragments = new Statek[how_many_fragments];
    Statek* pPlayerShipFragments = new Statek[how_many_fragments];
    bool is_board_visible;

    static int how_many_hits_made_player;
    static int how_many_hits_made_computer;


};



