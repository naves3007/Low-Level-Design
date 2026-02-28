/*
    Singleton -> Flags, Configs, Logs.
    Once process starts -> Singly maintained
    Synomous of making a global variable
        -> Global process, accessible from anywhere in the code
*/

#include <bits/stdc++.h>
using namespace std;

class Instance(){
    private:
        static Instance* instance;
        Instance(){} // Private constructor to prevent instantiation

    public:
        static Instance* getInstance(){
            if(instance == nullptr){
                instance = new Instance();
            }
            return instance;
        }
}
Instance* Instance::instance = nullptr; // Initialize static member

int main(){

    return 0;
}