/*
    When you have many logic, encapsulate them in different child class. and choose them during run-time. 
*/

#include<bits/stdc++.h>
using namespace std;

class BasePaymentClass{
    public:
        virtual void pay(int amount) = 0;
        virtual ~BasePaymentClass() = default;
};
class UpiPaymentClass : public BasePaymentClass{
    public:
        void pay(int amount) override {
            cout << "Paying by UPI: " << amount << endl; 
        }
};
class PayPalPaymentClass : public BasePaymentClass{
    public:
        void pay(int amount) override {
            cout << "Paying by PayPal: " << amount << endl; 
        }
};
class CardPaymentClass : public BasePaymentClass{
    public:
        void pay(int amount) override {
            cout << "Paying by Card: " << amount << endl; 
        }
};

// Context class: which creates objects of BasePaymentClass to calls on run time
class ContextPaymentClass{
    private:
        BasePaymentClass* basePaymentClass; // create as pointers
    public:
        // ContextPaymentClass(BasePaymentClass* s){
        //     basePaymentClass = s;
        // }
        ContextPaymentClass(BasePaymentClass* s) : basePaymentClass(s) {} // above comments lines are just the same 
                                                                          // but here initialisation happens first itself
        void setStrategy(BasePaymentClass* s){
            basePaymentClass = s;
        }                
        void makePayment(int amount){
            basePaymentClass->pay(amount); // use arrows as you create pointers
        }                                            
};

int main(){
    UpiPaymentClass upiPaymentClass;
    PayPalPaymentClass payPalPaymentClass;
    CardPaymentClass cardPaymentClass;
    ContextPaymentClass contextPaymentClass(&upiPaymentClass);
    
    contextPaymentClass.setStrategy(&upiPaymentClass);
    contextPaymentClass.makePayment(100);

    contextPaymentClass.setStrategy(&payPalPaymentClass);
    contextPaymentClass.makePayment(200);
    
    return 0;
}

