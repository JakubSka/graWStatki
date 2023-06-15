


class Statek {
public:
    Statek();
    void set_parameters(int id, int x, int y, int length_of_ship, int damage, int plane);
    void print_data();
    virtual ~Statek();

    int get_id();
    void set_id(int id);
    int get_x();
    void set_x(int x);
    int get_y();
    void set_y(int y);
    int get_length();
    void set_length(int length);
    int get_damage();
    void set_damage(int damage);
    void increase_damage();

    int get_plane();
    void set_plane(int plane);

protected:
private:
    int id;
    int x;
    int y;
    int length;
    int damage;
    int plane;
};


