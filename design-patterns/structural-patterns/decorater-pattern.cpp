/*
    Object Wraps Anoother Object To Provide Additional Functionality
*/

#include <bits/stdc++.h>
using namespace std;

class ISend(){
    public:
        virtual void send() = 0;
};
class EmailSender : public ISend{
    public:
        void send(){
            cout<<"Email Sent"<<endl;
        }
};
class Decorator : public ISend{
    protected:
        EmailSender* sender;
    public:
        Decorator(EmailSender* sender){
            this->sender = sender;
        }
        void send(){
            sender->send();
        }
};
class EmergencyDecorator : public Decorator{
    public:
        EmergencyDecorator(ISend* sender) : Decorator(sender){}
        void send(){
            cout<<"Urgent: ";
            Decorator::send();
        }
};




int main(){
    ISend* emailSender = new EmailSender();
    ISend* emergencyEmailSender = new EmergencyDecorator(emailSender);
    emergencyEmailSender->send();
    return 0;
}