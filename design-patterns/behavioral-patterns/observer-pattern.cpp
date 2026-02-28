/*
    When X changes and it change XYZ also. this has to be used
*/

#include <bits/stdc++.h>
using namespace std;

class Observer{
    public:
        virtual void update() = 0;
};

class Stock{
    private:
        vector<Observer*>Observers;
        int price;
    public:
        void addObserver(Observer* observer){
            Observers.push_back(observer);
        }
        void setPrice(int price){
            this->price = price;
            notifyAllObservers();
        }
        void notifyAllObservers(){
            for(auto observer : Observers){
                observer->update();
            }
        }       
};   

class MobileObserver : public Observer{
    public:
        void update(){
            cout<<"Mobile Observer Updated"<<endl;
        }
};

class LaptopObserver : public Observer{
    public:
        void update(){
            cout<<"Laptop Observer Updated"<<endl;
        }
};

int main(){

    Stock tesla;
    MobileObserver MobileObserver;
    LaptopObserver LaptopObserver;

    tesla.addObserver(&MobileObserver);
    tesla.addObserver(&LaptopObserver);

    /*
        When X changes and it change XYZ also. this has to be used
    */
    tesla.setPrice(100);

    return 0;
}