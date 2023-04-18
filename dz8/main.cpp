#include <iostream>
#include <vector>

class matrix{
    int row, column;
    std::vector<int> arr;

    void insert_row(std::vector<int>::iterator it);
    void insert_column(std::vector<int>::iterator it);
public:
    void print()const;
    void irb(int num);
    void ira(int num);
    void icb(int num);
    void ica(int num);
    void dc(int num);
    void dr(int num);
    void sr(int first_row, int sec_row);
    void sc(int first_column, int sec_column);
    void t();
    friend void parser(int const& argc, char** const argv);
};

//Functions matrix

void matrix::print()const{
    auto it = arr.begin();
    for(int i=0; i<row*column; ++i){
        if(i % column) std::cout << ' ';
        std::cout << *it;
        if((i+1) % column == 0){
            std::cout << std::endl;
        }
        ++it;
    }
}


void matrix::t(){
    std::vector<int> arr_tmp;
    auto it = arr.begin();
    for(int i=0; i<column; ++i){
        for(int j=0; j<row; ++j){
            arr_tmp.push_back(*(it + j * column + i));
        }
    }
    arr = arr_tmp;
    std::swap(row, column);
}

void matrix::dr(int num){
    if((num <= 0) || (num > row)) return;
    auto it=arr.begin() + (num - 1) * column;
    for(int i=0; i<column; ++i){
        it = arr.erase(it);
    }
    --row;
}

void matrix::dc(int num){
    if((num <=0) || (num > column)) return;
    std::vector<int>::iterator it = arr.begin() + num - 1;
    for(int i=0; i<row; ++i){
        arr.erase(it);
        it += column - 1;
    }
    --column;
}

void matrix::sr(int first_row, int sec_row){
    if((first_row <= 0) || (first_row > row) || (sec_row <= 0) || (sec_row > row)) return;
    auto it_f=arr.begin() + (first_row - 1) * column;
    auto it_s=arr.begin() + (sec_row - 1) * column;
    int value_f, value_s;
    for(int i=0; i<column; ++i){
        value_f = *it_f;
        value_s = *it_s;
        it_f = arr.erase(it_f);
        it_f = arr.insert(it_f, value_s);
        it_s = arr.erase(it_s);
        it_s = arr.insert(it_s, value_f);
        ++it_f;
        ++it_s;
    }
}

void matrix::sc(int first_column, int sec_column){
    if((first_column <= 0) || (first_column > row) || (sec_column <= 0) || (sec_column > column)) return;
    auto it_f=arr.begin() + (first_column - 1);
    auto it_s=arr.begin() + (sec_column - 1);
    int value_f, value_s;
    for(int i=0; i<row; ++i){
        value_f = *it_f;
        value_s = *it_s;
        it_f = arr.erase(it_f);
        it_f = arr.insert(it_f, value_s);
        it_s = arr.erase(it_s);
        it_s = arr.insert(it_s, value_f);
        it_f += column;
        it_s += column;
    }
}

void matrix::insert_row(std::vector<int>::iterator it){
    int tmp;
    for(int i=0; i<column; ++i){
        std::cin >> tmp;
        it = arr.insert(it, tmp);
        ++it;
    }
    ++row;

}

void matrix::insert_column(std::vector<int>::iterator it){
    int tmp;
    for(int i=0; i<row; ++i){
        std::cin >> tmp;
        it = arr.insert(it, tmp);
        it += column + 1;
    }
    ++column;
}

void matrix::irb(int num){
    if ((num > row) || (num <= 0)) return;
    std::vector<int>::iterator it = arr.begin() + (num-1) * column;
    this->insert_row(it);
}

void matrix::ira(int num){
    if ((num > row) || (num <= 0)) return;
    std::vector<int>::iterator it = arr.begin() + num * column;
    this->insert_row(it);
}

void matrix::icb(int num){
    if ((num > column) || (num <= 0)) return;
    std::vector<int>::iterator it = arr.begin() + num - 1;
    this->insert_column(it);
}

void matrix::ica(int num){
    if ((num > column) || (num <= 0)) return;
    std::vector<int>::iterator it = arr.begin() + num;
    this->insert_column(it);
}

void parser(int const& argc, char** const argv){
    int tmp, first_par, sec_par;
    matrix m;

        
    if((argc <= 1) || (argc > 4)){
        m.print();
        return;//error
    }
    if(argv[1][0] != '-'){
        m.print();
        return;//error
    }

    std::cin >> m.row;
    std::cin >> m.column;
    if ((m.row <= 0) || (m.column <=0)){
        m.print();
        return;//error
    }
    for(int i=0; i<m.row*m.column; ++i){
        std::cin >> tmp;
        m.arr.push_back(tmp);
    }

    if(argc > 2) first_par = atoi(argv[2]);
    if(argc > 3) sec_par = atoi(argv[3]);

    if(argv[1][1] == 'i'){
        if (!(argc == 3)){
                m.print();
                return;//error
        }

        if(argv[1][2] == 'r'){
            if(argv[1][3] == 'b'){
                if(argv[1][4] != '\0'){
                    m.print();
                    return;//error
                }
                m.irb(first_par);
            }
            else if(argv[1][3] == 'a'){
                if(argv[1][4] != '\0'){
                    m.print();
                    return;//error
                }
                m.ira(first_par);
            }
        }
        else if(argv[1][2] == 'c'){
            if(argv[1][3] == 'b'){
                if(argv[1][4] != '\0'){
                    m.print();
                    return;//error
                }
                m.icb(first_par);
            }
            else if(argv[1][3] == 'a'){
                if(argv[1][4] != '\0'){
                    m.print();
                    return;//error
                }
                m.ica(first_par);
            }
        }
        
    }

    if(argv[1][1] == 't'){
        if (!(argc == 2)) {
            m.print();
            return;//error
        }
        if (argv[1][2] != '\0'){
            m.print();
            return;//error
        }
        m.t();
    }

    if(argv[1][1] == 's'){
        if (!(argc == 4)){
            m.print();
            return;//error
        }
        if(argv[1][2] == 'r'){
            if(argv[1][3] != '\0'){
                m.print();
                return;//error
            }
            m.sr(first_par, sec_par);
        }
        else if(argv[1][2] == 'c'){
            if(argv[1][3] != '\0'){
                m.print();
                return;//error
            }
            m.sc(first_par, sec_par);
        }
    }

    if(argv[1][1] == 'd'){
        if (!(argc == 3)){
            m.print();
            return;//error
        }
        if(argv[1][2] == 'c'){
            if(argv[1][3] != '\0'){
                m.print();
                return;//error
            }
            m.dc(first_par);
        }
        else if(argv[1][2] == 'r'){
            if(argv[1][3] != '\0'){
                m.print();
                return;//error
            }
            m.dr(first_par);
        }
    }

    m.print();
}


int main(int argc, char** argv){

    parser(argc, argv);
    return 0;
}