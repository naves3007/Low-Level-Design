#include <bits/stdc++.h>
using namespace std;

class Factory {
public:
  virtual void createButton() = 0;
  virtual void createCheckbox() = 0;
};

class LightThemeFactory : public Factory {
  void createButton() { cout << "Returns a Light Button" << endl; }
  void createCheckbox() { cout << "Returns a Light Checkbox" << endl; }
};

class DarkThemeFactory : public Factory {
  void createButton() { cout << "Returns a Dark Button" << endl; }
  void createCheckbox() { cout << "Returns a Dark Checkbox" << endl; }
};

int main() {
  bool darkMode = true; // This could be determined at runtime
  Factory *factory;
  if (darkMode) {
    factory = new DarkThemeFactory();
  } else {
    factory = new LightThemeFactory();
  }
  factory->createButton();
  factory->createCheckbox();

  delete factory;
  return 0;
}