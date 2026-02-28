#include<bits/stdc++.h>
using namespace std;

interface Factory{
    virtual Button createButton() = 0;
    virtual Checkbox createCheckbox() = 0;
}

class LightThemeFactory : public Factory{
    Button createButton(){
        return new LightButton();
    }
    Checkbox createCheckbox(){
        return new LightCheckbox();
    }
}

class DarkThemeFactory : public Factory{
    Button createButton(){
        return new DarkButton();
    }
    Checkbox createCheckbox(){
        return new DarkCheckbox();
    }
}

int main(){
    bool darkMode = true; // This could be determined at runtime
    Factory* factory = darkMode ? new DarkThemeFactory() : new LightThemeFactory();
    Button* button = factory->createButton();
    Checkbox* checkbox = factory->createCheckbox();
    
    delete factory;
    delete button;
    delete checkbox;
    return 0;
}