

class Plansza {
public:
    Plansza();
    virtual ~Plansza();

    void initialization(char** boardArray, const int length_of_board);
    void print_board(bool visibility);
    char get_field(int x, int y);
    void set_field(int x, int y, char field);
    const int get_length_of_board();

protected:
private:
    char** plansza;
    const int dlugoscPlanszy = 32;
};


