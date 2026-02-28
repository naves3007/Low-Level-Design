/*
    when multiple strategy can be bought to same idea
*/

#include<bits/stdc++.h>
using namespace std;

class Base{
    public:
        virtual void send() = 0;
};
class CardSend : public Base{
    public:
        void send(){
            cout<<"Card Send"<<endl;
        }
};
class UpiSend : public Base{
    public:
        void send(){
            cout<<"Upi Send"<<endl;
        }
};

class BaseStrategy{
    private:
        Base* base;
    public:
        BaseStrategy(Base* base){
            this->base = base;  
        }
        void send(){
            base->send();
        }
};

int main(){
    // Just create BaseStrategy object and pass the strategy you want to use as a parameter
    BaseStrategy* strategy = new BaseStrategy(new CardSend());
    strategy->send();
    strategy = new BaseStrategy(new UpiSend());
    strategy->send();
}

