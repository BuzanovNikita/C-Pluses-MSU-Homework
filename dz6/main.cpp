#include<iostream>
#include<cstring>

#define N 10

template<typename T>
int is_in(T* arr, size_t size, T elem){
    if(arr == nullptr) return -1;
    for(int i=0; (size_t)i < size; i++){
        if(arr[i] == elem) return i;
    }
    return -1;
}
template<typename T>
void my_memcpy(T* dest, T* src, size_t size){
    for(size_t i=0; i<size; ++i){
        dest[i] = src[i];
    }
}


template<typename T>
class Set{
    T* arr_;
    size_t size_;
    size_t cap_;
public:
    Set();
    Set(T* arr, size_t size);
    Set(const Set&);
    ~Set(){if(arr_ != nullptr) delete[] arr_;}
    void add(T elem);
    void add(T* new_arr, size_t new_size);
    void increase(size_t n);
    void del(T elem);
    bool in(T elem)const{return is_in(arr_, size_, elem) >= 0;}
    void print()const;
    size_t min_index()const;

    template<typename U>
    friend const Set<U> operator+(Set<U> first, const Set<U>& second);
    template<typename U>
    friend const Set<U> operator*(const Set<U>& first, const Set<U>& second);
    const Set& operator=(const Set& another);
};

//Constructors
template<typename T>
Set<T>::Set(){
    arr_ = nullptr;
    cap_ = size_ = 0;
}
template<typename T>
Set<T>::Set(T* arr, size_t size){
    size_t j=0;
    cap_ = size;
    arr_ = new T[size];
    for(size_t i=0; i<size; i++){
        if(is_in(arr_, j, arr[i]) == -1) {
            arr_[j] = arr[i]; 
            j++;
        }
    }
    size_ = j;
}
template<typename T>
Set<T>::Set(const Set<T>& another){\
    if(another.size_ == 0){
        size_ = cap_ = 0;
        arr_ = nullptr;
    }
    cap_ = size_ = another.size_;
    arr_ = new T[size_];
    my_memcpy(arr_, another.arr_, size_);
}

//Functions
template<typename T>
void Set<T>::add(T elem){
    if(is_in(arr_, size_, elem) == -1){
        if(cap_ == size_) this->increase(N);
        arr_[size_] = elem;
        size_++;
    } 
}
template<typename T>
void Set<T>::add(T* new_arr, size_t new_size){
    if(new_arr == nullptr) return; 
    if(cap_ - size_ < new_size) this->increase(new_size - (cap_-size_));
    for(size_t i=0; i<new_size; i++) this->add(new_arr[i]);
}
template<typename T>
void Set<T>::increase(size_t n){
    if(arr_ == nullptr){
        arr_ = new T[n];
        return;
    } 
    T* tmp_arr = new T[size_];
    my_memcpy(tmp_arr, arr_, size_);
    delete[] arr_;
    arr_ = new T[size_ + n];
    my_memcpy(arr_, tmp_arr, size_);
    cap_ += n;
}
template<typename T>
void Set<T>::del(T elem){
    if(size_ == 0) return;
    int j;
    if((j = is_in(arr_, size_, elem)) >= 0){
        j = (size_t) j;
        T tmp_arr[size_ - j -1];
        my_memcpy(tmp_arr, &arr_[j+1], size_ - j -1);
        my_memcpy(&arr_[j], tmp_arr, size_ - j -1);
        size_--;
    }
}
template<typename T>
size_t Set<T>::min_index()const{
    size_t res=0;
    T min = arr_[0];
    for(size_t i=1; i<size_; ++i){
        if(arr_[i] < min){
            min = arr_[i];
            res = i;
        }
    }
    return res;
}

template<typename T>
void Set<T>::print()const{
    if(size_ == 0) return;
    Set tmp = *this;
    T min = tmp.arr_[tmp.min_index()];
    std::cout << min;
    tmp.del(min);
    for(size_t i=1; i<size_; i++){
        min = tmp.arr_[tmp.min_index()];
        std::cout << ' ' << min;
        tmp.del(min);
    }
    std::cout <<std::endl;
}

//Operators
template<typename T>
const Set<T> operator+(Set<T> first, const Set<T>& second){
    if(first.size_ == 0) return second;
    if(second.size_ == 0) return first;
    first.add(second.arr_, second.size_);
    return first;
}
template<typename T>
const Set<T> operator*(const Set<T>& first, const Set<T>& second){
    Set<T> res;
    if((first.size_ == 0) || (second.size_ == 0)){
        return res;
    }
    for(size_t i=0; i<first.size_; i++){
        if(is_in(second.arr_, second.size_, first.arr_[i]) >= 0){
            res.add(first.arr_[i]);
        }
    }
    return res;
}
template<typename T>
const Set<T>& Set<T>::operator=(const Set<T>& another){
    if(this == &another) return *this;
    if(another.size_ == 0){
        size_ = cap_ = 0;
        arr_ = nullptr;
    }
    cap_ = size_ = another.size_;
    arr_ = new T[size_];
    my_memcpy(arr_, another.arr_, size_);
    return *this;
}

/*int main(){
        int a[] = { 1,2,3,4,5 };
        int b[] = { 8,7,6};
        int c[] = {6};
        Set <int> s1(a,5),s2,s3,s4,s5(b, 3);
        std::cout << "s1 = ";
        s1.print();
        std::cout << "s2 = ";
        s2.print();
        std::cout << "s5 = ";
        s5.print();
        s1.add(6);
        s1.add(1);
        std::cout << "s1 = ";
        s1.print();
        s1.del(1);
        s1.del(6);
        std::cout << "s1 = ";
        s1.print();
        s2 = (s5 + s1) * s2;
        std::cout << "s2 = ";
        s2.print();
        
        return 0;
}*/