#include<bits/stdc++.h>
using namespace std;

class INotifier{
    public:
        virtual void send(string message) = 0;
};

class EmailNotifier : public INotifier{
    public:
        void send(string message){
            cout<<"Email sent: "<<message<<endl;
        }
};

class SMSNotifier : public INotifier{
    public:
        void send(string message){
            cout<<"SMS sent: "<<message<<endl;
        }
};

// Factory class to create notifiers -> factory pattern (only create objects, no family of objects)
class NotifierFactory{
    public:
        static INotifier* createNotifier(string type){
            if(type == "email"){
                return new EmailNotifier();
            }else if(type == "sms"){
                return new SMSNotifier();
            }else{
                return nullptr;
            }
        }
};

int main(){
    INotifier* emailNotifier = NotifierFactory::createNotifier("email");
    emailNotifier->send("Hello from Email!");

    INotifier* smsNotifier = NotifierFactory::createNotifier("sms");
    smsNotifier->send("Hello from SMS!");

    delete emailNotifier;
    delete smsNotifier;
}