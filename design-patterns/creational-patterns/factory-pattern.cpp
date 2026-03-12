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

// You delegate object creation to a factory method or class.
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
    INotifier* notifier = NotifierFactory::createNotifier("email"); // factory will decide which class to instantiate based on the input
    notifier->send("Hello from Email!");

    notifier = NotifierFactory::createNotifier("sms");
    notifier->send("Hello from SMS!");

    delete notifier;
}