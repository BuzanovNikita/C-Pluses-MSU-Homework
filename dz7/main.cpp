#include<iostream>

class Exception{
    const std::string mes;
    const std::string name;
    int n;
public:
    void print()const{
        std::cerr << "Exception: " << mes << " in team " << name;
        if((mes == "Wrong number") || (mes == "Double number")){
            std::cerr << " Error number: " << n;
        }
        std::cerr << std::endl;
    }
    Exception(std::string const& mes_, std::string const& name_, int n_):mes(mes_), name(name_), n(n_){};
};

bool is_in_team(int n, int num, int* arr){
    for(int i=0; i<num; ++i){
        if(arr[i] == n) return true;
    }
    return false;
}

void throw_ex(int n, int num, int* arr, const std::string team_name){
        if(num >= 11) throw Exception ("Too many players", team_name, n);
        if(is_in_team(n, num, arr)) throw Exception ("Double number", team_name, n);
        if(n <= 0) throw Exception ("Wrong number", team_name, n);
}

void del(int (&arr)[11], int& sz, int n){
    int i;
    for(i=0; i<sz; ++i) if(arr[i] == n) break;
    while(i < sz-1) {
        arr[i] = arr[i+1];
        ++i;
    }
    --sz;
}

class Player{
    static int num_zenit, num_cska;
    static int zenit[11], cska[11];
    std::string team_name;
    int n;
public:
    Player(const std::string team_name_, int n_);
    ~Player();
    void Print()const;
    static void Print_teams();

};
int Player::num_cska = 0;
int Player::num_zenit = 0;
int Player::zenit[11] = {0,0,0,0,0,0,0,0,0,0,0};
int Player::cska[11] = {0,0,0,0,0,0,0,0,0,0,0};


//Constructors
Player::Player(const std::string team_name_, int n_){
    team_name = team_name_;
    n = n_;
    if(team_name == "CSKA"){
        throw_ex(n, num_cska, cska, team_name);
        cska[num_cska] = n;
        ++num_cska;
    }
    else if(team_name == "Zenit"){
        throw_ex(n, num_zenit, zenit, team_name);
        zenit[num_zenit] = n;
        ++num_zenit;
    }
    else throw Exception ("Wrong name", team_name, 0);
}
Player::~Player(){
    if(team_name == "CSKA") del(cska, num_cska, n);
    else del(zenit, num_zenit, n);
}
//Functions
void Player::Print()const{
    std::cout << team_name << ' ' << n << std::endl;
}

void Player::Print_teams(){
    if(num_zenit > 0){
        std::cout << "Zenit: " << zenit[0];
        for(int i=1; i<num_zenit; ++i)
        std::cout << ' ' << zenit[i];
        std::cout << std::endl;
    }
    if(num_cska > 0){
        std::cout << "CSKA: " << cska[0];
        for(int i=1; i<num_cska; ++i)
        std::cout << ' ' << cska[i];
        std::cout << std::endl;
    }
}

int main(){
    try{
        test_players();
    }
    catch(const Exception& ex) {
        ex.print();
    }

    return 0;
}