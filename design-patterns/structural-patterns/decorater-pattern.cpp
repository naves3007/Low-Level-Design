#include <bits/stdc++.h>
using namespace std;

class coffeeCost {
public:
  virtual double getCost() = 0;
  virtual ~coffeeCost() = default;
};

class simpleCoffee : public coffeeCost {
public:
  double getCost() override { return 5.0; }
};

class coffeeDecorator : public coffeeCost {
protected: // 🔥 changed
  coffeeCost *coffee;

public:
  coffeeDecorator(coffeeCost *c) : coffee(c) {}
};

class milkDecorator : public coffeeDecorator {
public:
  milkDecorator(coffeeCost *c) : coffeeDecorator(c) {}

  double getCost() override {
    return coffee->getCost() + 1.0; // ✅ FIXED
  }
};

class sugarDecorator : public coffeeDecorator {
public:
  sugarDecorator(coffeeCost *c) : coffeeDecorator(c) {}

  double getCost() override {
    return coffee->getCost() + 0.5; // ✅ FIXED
  }
};

class whippedCreamDecorator : public coffeeDecorator {
public:
  whippedCreamDecorator(coffeeCost *c) : coffeeDecorator(c) {}

  double getCost() override {
    return coffee->getCost() + 1.5; // ✅ FIXED
  }
};

int main() {
  coffeeCost *myCoffee = new simpleCoffee();
  myCoffee = new milkDecorator(myCoffee);
  myCoffee = new sugarDecorator(myCoffee);
  myCoffee = new whippedCreamDecorator(myCoffee);

  cout << "Total Cost of Coffee: $" << myCoffee->getCost() << endl;

  return 0;
}