/*
    Old Service 
        Intemediate Adapter which converts the interface of the Old Service
        to the interface expected by the client
    New Service
*/

#include <bits/stdc++.h>
using namespace std;

interface newService{
    void processPayment(double amount);
};

class OldService{
    public:
        void makePayment(string paise){
            cout<<"Payment of "<<paise<<" made using Old Service"<<endl;
        }
};

class OldAdapter : public newService{
    private:
        OldService oldService;
    public:
        OldAdapter(OldService service){
            this->oldService = service;
        }
        void processPayment(double amount){
            string paise = to_string(amount);
            oldService.makePayment(paise);
        }
};



int main(){
    OldService oldService;
    newService* adapter = new OldAdapter(oldService);
    adapter->processPayment(100.50);
    return 0;
}