#include <bits/stdc++.h>
using namespace std;

class oldPaymentService {
public:
  void makePayment(string paise) {
    cout << "Payment of " << paise << " made using Old Service" << endl;
  }
};

class newPaymentService {
public:
  virtual void newMakePayment(string double_) = 0;
};

class paymentAdapter : public newPaymentService {
private:
  oldPaymentService *oldService;

public:
  paymentAdapter(oldPaymentService *service) { this->oldService = service; }
  void newMakePayment(string double_) override {
    string paise = double_; // Convert to paise by appending '0'
    oldService->makePayment(paise);
  }
};

int main() {
  oldPaymentService *oldService = new oldPaymentService();
  paymentAdapter *adapter = new paymentAdapter(oldService);
  adapter->newMakePayment("10.5");
  return 0;
}