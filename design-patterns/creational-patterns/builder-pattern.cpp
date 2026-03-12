#include <bits/stdc++.h>
using namespace std;

class primaryService {
private:
  string name;
  string email;
  string mobileNumber;
  string address;

public:
  primaryService(string name, string email, string mobileNumber,
                 string address) {
    this->name = name;
    this->email = email;
    this->mobileNumber = mobileNumber;
    this->address = address;
  }
  void display() {
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Mobile Number: " << mobileNumber << endl;
    cout << "Address: " << address << endl;
  }
  class primaryServiceBuilder {
  private:
    string name_;
    string email_;
    string mobileNumber_;
    string address_;

  public:
    primaryServiceBuilder &setName(string name) {
      this->name_ = name;
      return *this;
    }
    primaryServiceBuilder &setEmail(string email) {
      this->email_ = email;
      return *this;
    }
    primaryServiceBuilder &setMobileNumber(string mobileNumber) {
      this->mobileNumber_ = mobileNumber;
      return *this;
    }
    primaryServiceBuilder &setAddress(string address) {
      this->address_ = address;
      return *this;
    }
    primaryService build() {
      return primaryService(name_, email_, mobileNumber_, address_);
    }
  };
};

int main() {
  primaryService::primaryServiceBuilder builder; // class::member primaryService::primaryServiceBuilder
  primaryService service = builder.setName("John Doe")
                               .setEmail("temp@gmail.com")
                               .setMobileNumber("1234567890")
                              //  .setAddress("123 Main St")
                               .build();
  service.display();
  return 0;
}