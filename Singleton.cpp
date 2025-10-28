#include <iostream>

class Singleton{
    //Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator =(const Singleton& an) = delete;
public:
    static Singleton* getInstance(){
        static Singleton ins;
        return &ins;
    }
private:
    Singleton(){}
    //Singleton ins_;
};