/*
    Singleton:
        Logger
        Database Connection Establisher
        Thread pool manager
        Configuration manager
    Constructor of a class is private: any times you call from main it's only single memory
*/

#include <bits/stdc++.h>
using namespace std;

class SingletonBaseClass{
    private:
        static SingletonBaseClass* singletonBaseClass_;
        SingletonBaseClass(){ // constuctor private ensures only one obj is created in whole code
            cout << "Singleton Created" << endl;
        }
    public:
        static SingletonBaseClass* getClassInstance(){
            if(singletonBaseClass_ == nullptr){
                singletonBaseClass_ = new SingletonBaseClass();
            }
            return singletonBaseClass_; 
        }
        void showMessage(){
            cout << "Hello from singletonBaseClass_ class" << endl;
        }
};

SingletonBaseClass* SingletonBaseClass::singletonBaseClass_ = nullptr;

int main(){
    SingletonBaseClass* s1 = SingletonBaseClass::getClassInstance();
    SingletonBaseClass* s2 = SingletonBaseClass::getClassInstance();

    s1->showMessage();

    cout << (s1 == s2 ? "True" : "False" ) << endl;

    return 0;
}