#include <iostream>

enum figure_names{
    Queen,
    King,
    Knight,
    Rook,
    Bishop
};

class cage{
    char c;
    int i;
public:
    char get_c()const{return c;}
    int get_i()const{return i;}
    void set(char new_c, int new_i){
        c = new_c;
        i = new_i;
    }
    void print()const{
        std:: cout << c << i;
    }
};

//Проверка движения по диагоналям и параллелям, а также движения в рамках доски
bool move_in_field(const cage& cur_cage, const cage& des_cage){
    if(cur_cage.get_i() > 8 || cur_cage.get_i() <= 0) return false;
    if(des_cage.get_i() > 8 || des_cage.get_i() <= 0) return false;
    if(cur_cage.get_c() < 'a' || cur_cage.get_c() > 'h') return false;
    if(des_cage.get_c() < 'a' || des_cage.get_c() > 'h') return false;
    return true;
}
bool move_diag(const cage& cur_cage, const cage& des_cage) {
    if (((int) cur_cage.get_c() + cur_cage.get_i() == (int) des_cage.get_c() + des_cage.get_i()) ||
        ((int) cur_cage.get_c() - cur_cage.get_i() == (int) des_cage.get_c() - des_cage.get_i()))
        return true;
    else return false;
}
bool move_paral(const cage& cur_cage, const cage& des_cage){
    if ((cur_cage.get_i() == des_cage.get_i()) || (cur_cage.get_c() == des_cage.get_c())) return true;
    else return false;
}

//Figures
class Figure{
public:
    virtual bool move(const cage& cur_cage, const cage& des_cage)const = 0;
};

class f_King:public Figure{
public:
    bool move(const cage& cur_cage, const cage& des_cage)const override{
        if((abs(cur_cage.get_i() - des_cage.get_i()) <= 1 && abs(cur_cage.get_c() - des_cage.get_c()) <= 1) &&
        move_in_field(cur_cage, des_cage))return true;
        else return false;
    }
};

class f_Rook:public Figure{
public:
    bool move(const cage& cur_cage, const cage& des_cage)const override{
        return move_paral(cur_cage, des_cage) && move_in_field(cur_cage, des_cage);
    }
};

class f_Bishop:public Figure{
public:
    bool move(const cage& cur_cage, const cage& des_cage)const override{
        return move_diag(cur_cage, des_cage) && move_in_field(cur_cage, des_cage);
    }
};

class f_Queen:public Figure{
public:
    bool move(const cage& cur_cage, const cage& des_cage)const override{
        return (move_paral(cur_cage, des_cage) || move_diag(cur_cage,des_cage)) && move_in_field(cur_cage, des_cage);
    }
};

class f_Knight:public Figure{
public:
    bool move(const cage& cur_cage, const cage& des_cage)const override{
        return ((!(move_paral(cur_cage, des_cage) || move_diag(cur_cage,des_cage)) &&
                (abs(cur_cage.get_c()-des_cage.get_c()) + abs(cur_cage.get_i()-des_cage.get_i()) == 3)) ||
                       (cur_cage.get_i() == des_cage.get_i() && cur_cage.get_c() == des_cage.get_c()) ) &&
                            move_in_field(cur_cage, des_cage);
    }
};

//ChessChecker
class ChessChecker{
    figure_names name;
    cage cur_cage;
    cage des_cage;
public:
    Figure* figures[5];
    void input();
    void check();
};

//ChessChecker's Functions
void ChessChecker::input(){
    char c;
    int i;
    std::cin >> c;
    switch(c)
    {
        case 'Q':
            name = Queen;
        break;
        case 'K':
            name = King;
        break;
        case 'R':
            name = Rook;
        break;
        case 'N':
            name = Knight;
        break;
        case 'B':
            name = Bishop;
        break;
        default:
            std::cerr << "Wrong Input\n";
    };
    std::cin >> c;
    std::cin >> i;
    cur_cage.set(c, i);
    std::cin >> c;
    std::cin >> i;
    des_cage.set(c, i);
}
void ChessChecker::check(){
    if (figures[name]->move(cur_cage, des_cage)) std::cout << "YES\n";
    else std::cout << "NO\n";
}

int main() {
    ChessChecker A;

    A.figures[King] = new f_King;
    A.figures[Rook] = new f_Rook;
    A.figures[Bishop] = new f_Bishop;
    A.figures[Queen] = new f_Queen;
    A.figures[Knight] = new f_Knight;

    A.input();
    A.check();

    return 0;
}