/*
CLass -> Has Bunch of Parameteres -> Constructor -> Object Creation Use Builder Pattern
*/

#include <bits/stdc++.h>
using namespace std;


class User{
    private:
        string name;
        string email;
        string phone;

    public
        User(string name, string email, string phone){
            this->name = name;
            this->email = email;
            this->phone = phone;
        }

        void display() const{
            cout<<"Name: "<<name<<endl;
            cout<<"Email: "<<email<<endl;
            cout<<"Phone: "<<phone<<endl;
        }
    
    class Builder(){
        private:
            string _name;
            string _email;
            string _phone;
        
        public:
            Builder& setName(string name){
                _name = name;
                return *this;
            }

            Builder& setEmail(string email){
                _email = email;
                return *this;
            }

            Builder& setPhone(string phone){
                _phone = phone;
                return *this;
            }

            User build() const{
                return User(_name, _email, _phone);
            }
    }
};

int main(){
    User user = User::Builder()
        .setName("John Doe")
        .setEmail("temp@gmai.com")
        .setPhone("1234567890")
        .build(); // add only things you want using builder class and call build.
}


