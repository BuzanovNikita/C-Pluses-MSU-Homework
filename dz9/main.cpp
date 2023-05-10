#include <iostream>
#include <string>

class Lex{
    std::string lex;
    enum {CREATE_TABLE, INSERT_INTO, END} cur_command;
public:
    void get_lex();
    bool analyzer();
    void print(){std::cout << lex;}
    void CREATE();
    void INSERT();
    void S();
};

void Lex::S(){
    get_lex();
    if(lex == "CREATE") CREATE();
    else if(lex == "INSERT") INSERT();
    else if(lex == "END") cur_command = END;
    else throw;
}

void Lex::CREATE(){
    get_lex();
    if(lex == "TABLE"){
        cur_command = CREATE_TABLE;
    }
    else throw;
}

void Lex::INSERT(){
    get_lex();
    if(lex == "INTO") cur_command = INSERT_INTO;
    else throw;
}

void Lex::get_lex(){
    std::cin >> lex;
}

bool Lex::analyzer(){
    try{
        get_lex();
        S();
    }
    catch(...){

    }
    return true;
}

class SQL_interp{


public:
    void get_query();


};

//Metods with comand
void SQL_interp::get_query(){

}


int main(){
    Lex l;
    l.get_lex();
    l.print();

    return 0;
}