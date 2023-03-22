#include <iostream>
#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#define N 20

class mstring{
    char* arr;
    size_t sz;
    size_t cap;
public:

    //Constructors
    mstring();
    mstring(const char* a);
    mstring(const mstring& another);
    ~mstring(){if(arr != nullptr) delete[] arr;}

    //Functions
    void increase(int n);
    int length() const{return sz;}
    bool isempty() const{return sz==0;}
    void add(char c);
    void add(const char* str);
    void insert(char c, int i);
    void insert(const char* str, int i);
    void del(int i){this->del(i,i);};
    void del(int i, int j);
    int search(const char* str)const;
    void replace(const char* substr, const char* newstr);
    void print()const{std::cout << arr << std::endl;}

    //Operators
    mstring operator=(const mstring& another);
    friend mstring operator+(const mstring& mstr1, const mstring& mstr2);
    mstring operator*(int n)const;
    friend std::ostream& operator<<(std::ostream& os, const mstring& str);
    friend std::istream& operator>>(std::istream& is, mstring& str);
    bool operator>(const mstring& another)const{return (strcmp(this->arr,another.arr) < 0);}
    bool operator<(const mstring& another)const{return (strcmp(this->arr,another.arr) > 0);}
    bool operator>=(const mstring& another)const{return (strcmp(this->arr,another.arr) <= 0);}
    bool operator<=(const mstring& another)const{return (strcmp(this->arr,another.arr) >= 0);}
    bool operator==(const mstring& another)const{return (strcmp(this->arr,another.arr) == 0);}
    char& operator[](int i)const{return this->arr[i];}

};

//Operators
mstring operator*(int n, const mstring& str){
    return str * n;
}
mstring mstring::operator*(int n)const{
    mstring res;
    for(int i=1; i<=n; i++) res.add(this->arr);
    return res;
}
mstring mstring::operator=(const mstring& another){
    if(cap != another.cap){
        delete[] arr;
        cap = another.cap;
        arr = new char[cap];
    }
    sz = another.sz;
    for(size_t i=0; i<sz; ++i){
        arr[i] = another.arr[i];
    }
    arr[sz] = '\0';
    return *this;
}
mstring operator+(const mstring& mstr1, const mstring& mstr2){
    mstring res(mstr1.arr);
    res.add(mstr2.arr);
    return res;
}
std::istream& operator>>(std::istream& is, mstring& str){
    str.sz = 0;
    str.arr[0] = '\0';
    char c = is.get();
    while (c != '\n') {
        str.add(c);
        if (is.eof()) break;
        c = is.get();
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, const mstring& str){
    os << str.arr;
    return os;
}

//Functions
void mstring::replace(const char* substr, const char* newstr){
    if(substr == nullptr || newstr == substr) return;
    int i = this->search(substr);
    int len = strlen(substr);
    if (i == -1) return;
    this->del(i, i+len-1);
    this->insert(newstr, i);
}
int mstring::search(const char* str)const{
    if(str == nullptr) return -1;
    if(sz < strlen(str)) return -1;
    char* substr = strstr(arr, str);
    if (substr == nullptr) return -1;
    return substr - arr;
}
void mstring::del(int i, int j){
    char* substr = new char[sz-j];
    memcpy(substr, &(arr[j+1]), sz-j);
    memcpy(&(arr[i]), substr, sz-j);
    sz -= j-i+1;
    delete[] substr;
}
void mstring::insert(const char* str, int i){
    if (str == nullptr) return;
    size_t len = strlen(str);
    if(cap-1-sz < len) this->increase(len - (cap-1-sz));
    char* substr = new char[sz-i+1];
    memcpy(substr, &(arr[i]), sz-i+1);
    memcpy(&(arr[i]), str, len);
    memcpy(&(arr[i+len]), substr, sz-i+1);
    sz += len;
    arr[sz] = '\0';
    delete[] substr;
}
void mstring::insert(char c, int i){
    char* substr = new char[2];
    substr[0] = c;
    substr[1] = '\0';
    this->insert(substr, i);
    delete[] substr;
}
void mstring::add(char c){
    if (sz >= cap-1) this->increase(N);
    arr[sz] = c;
    arr[sz+1] = '\0';
    sz++;
}
void mstring::add(const char* str){
    if(str == nullptr) return;
    size_t len = strlen(str);
    if (cap-1-sz < len) this->increase(len - (cap-1-sz));
    memcpy(&(arr[sz]), str, len);
    sz += len;
    arr[sz] = '\0';
}
void mstring::increase(int n){
    char* newarr = new char[sz + n];
    if(arr != nullptr){
        memcpy(newarr, arr, sz+1);
        delete[] arr;
    }
    arr = newarr;
    cap += n;
}

//Constructors
mstring ::mstring(const mstring& str){
    if (str.arr == nullptr){
        arr = new char[N];
        sz = 0;
        cap = N;
        arr[0] = '\0';
        return;
    }
    cap = str.cap;
    sz = str.sz;
    arr = new char[sz+1];
    memcpy(arr, str.arr, sz+1);
}
mstring ::mstring(const char* str){
    if (str == nullptr) {
        arr = new char[N];
        sz = 0;
        cap = N;
        arr[0] = '\0';
        return;
    }
    size_t len = strlen(str);
    arr = new char[len + 1];
    cap = len + 1;
    sz = len;
    memcpy(arr, str, len);
    arr[len] = '\0';
}
mstring ::mstring(){
    arr = new char[N];
    sz = 0;
    cap = N;
    arr[0] = '\0';
}

int main() {
    mstring u("world"), v("world"), w(v), z;

    if(u < v) std::cout << 1 <<std::endl;
    if(u > v) std::cout << 2 <<std::endl;
    if(u <= v) std::cout << 3 <<std::endl;
    if(u >= v) std::cout << 4 <<std::endl;
    if(u == v) std::cout << 5 <<std::endl;
    
    std::cout << "w = " << w << std::endl;
    w[10] = '?';
    std::cout << "w = " << w << std::endl;
    //std::cin >> z;
    std::cout << "z = " << z << std::endl;
    return 0;
}