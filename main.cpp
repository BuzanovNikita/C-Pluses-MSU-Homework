#include <iostream>
using namespace std;

class BitString{
private:
    unsigned int f, s;
public:

    BitString( unsigned int f, unsigned int s ): f(f), s(s) {};
    BitString( unsigned int s ): f(0), s(s) {};
    BitString(): f(0), s(0) {};

    unsigned int get_f() const { return f; }
    unsigned int get_s() const { return s; }

    void Print();
    void ShiftLeft( unsigned long long offset );
    void ShiftRight( unsigned long long offset );

    void AND( const BitString& b ){ f = f & b.get_f(); s = s & b.get_s(); }
    void OR( const BitString& b ){ f = f | b.get_f(); s = s | b.get_s(); }
    void XOR( const BitString& b ){ f = f ^ b.get_f(); s = s ^ b.get_s(); }
    void NOT(){ f = ~f; s = ~s; };

};

void BitString::ShiftLeft(unsigned long long offset) {
    unsigned int masks;
    if( offset >= 64 ){
        f = 0;
        s = 0;
    }
    else{
        while( offset ){
            masks = (1 << 31) & s;
            f = (f << 1) | (masks >> 31);
            s = s << 1;
            offset--;
        }
    }
}

void BitString::ShiftRight(unsigned long long offset) {
    unsigned int maskf;
    if ( offset >= 64 ){
        f = 0;
        s = 0;
    }
    else{
        while( offset ){
            maskf = 1 & f;
            f = f >> 1;
            s = (s >> 1) | (maskf << 31);
            offset--;
        }
    }
}

void BitString::Print() {
    unsigned long long tmp = f;
    tmp = (tmp << 32) + s;
    cout << tmp << endl;
}

/*int main() {

    BitString b1(127,255);
    b1.Print();
    b1.ShiftLeft(3);
    b1.Print();
    BitString b2(511,1025), b3(2045);
    b2.Print();
    b1.AND(b2);
    b1.Print();
    b3.Print();
    b1.OR(b3);
    b1.Print();
    b2.Print();
    b2.XOR(b1);
    b2.Print();
    b3.NOT();
    b3.Print();



    return 0;
}*/