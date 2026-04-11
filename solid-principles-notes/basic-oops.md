## 1. Abstraction
    Hiding unnecessary details, showing only essential features.
    class Car {
    public:
        void start() { cout << "Car started\n"; }
    };

## 2. Encapsulation
    Wrapping data + methods together and restricting direct access.
    class BankAccount {
    private:
        int balance;
    public:
        void deposit(int amount) { balance += amount; }
        int getBalance() { return balance; }
    };

## 3. Inheritance
    One class acquires properties of another (reusability).
    class Animal {
    public:
        void eat() { cout << "Eating\n"; }
    };
    class Dog : public Animal {
    public:
        void bark() { cout << "Barking\n"; }
    };

## 4. Polymorphism
    Same function behaves differently based on context.
    
    ### 1. Function Overloading (Compile-Time Polymorphism)
        class Math {
        public:
            int add(int a, int b) { return a + b; }
            int add(int a, int b, int c) { return a + b + c; }
        };
    ### 2. Method Overriding (Run-Time Polymorphism)
        class Animal {
        public:
            virtual void sound() { cout << "Animal sound\n"; }
        };

        class Dog : public Animal {
        public:
            void sound() override { cout << "Bark\n"; }
        };

## 5. Use of "Virtual" Functions?
    Virtual decides Run-Time Polymorphism

    a. Wrong Example: 
        class Animal {
        public:
            void sound() { cout << "Animal sound\n"; }
        };
        class Dog : public Animal {
        public:
            void sound() { cout << "Bark\n"; }
        };
        int main() {
            Animal* obj = new Dog();
            obj->sound();   // ❗ What will this print? // Animal sound
        }
    b. Correct Example: 
        class Animal {
        public:
            virtual void sound() { cout << "Animal sound\n"; }
        };
        class Dog : public Animal {
        public:
            void sound() override { cout << "Bark\n"; }
        };
        int main() {
            Animal* obj = new Dog();
            obj->sound();   // ✅ Correct behavior // Bark
        }

## 6. Access Specifiers in C++
    Note: If you don't declare it's protected in class
    Note: If you don't declare it's public in struct
    1. public:
        class Car {
        public:
            int speed;
        };
        int main() {
            Car c;
            c.speed = 100;   // ✅ allowed
        }
    2. protected:
        class BankAccount {
        private:
            int balance;
        public:
            void setBalance(int b) { balance = b; }
        };
        int main() {
            BankAccount b;
            // b.balance = 1000; ❌ NOT allowed
            b.setBalance(1000);  // ✅ allowed via method
        }
    3. private:
        class BankAccount {
        private:
            int balance;
        public:
            void setBalance(int b) { balance = b; }
        };
        int main() {
            BankAccount b;
            // b.balance = 1000; ❌ NOT allowed
            b.setBalance(1000);  // ✅ allowed via method
        }

## 7. Base Class Pointer to a Derived Class Object
    1. Without use of "virtual"
        class Animal {
        public:
            void eat() { cout << "Eating\n"; }
        };

        class Dog : public Animal {
        public:
            void bark() { cout << "Barking\n"; }
        };

        int main() {
            Animal* obj = new Dog();  // ✅ valid
            obj->eat();   // ✅ allowed
            // obj->bark(); ❌ NOT allowed
        }
    2. use of "virtual"
        class Animal {
        public:
            virtual void sound() { cout << "Animal sound\n"; }
        };

        class Dog : public Animal {
        public:
            void sound() override { cout << "Bark\n"; }
        };

        int main() {
            Animal* obj = new Dog();
            obj->sound();  // ✅ Bark (runtime polymorphism)
        }

## 8. . (dot) versus -> (arrow)
    1. using .
        class Car {
        public:
            int speed;
        };

        int main() {
            Car c;
            c.speed = 100;

            cout << "Speed: " << c.speed << endl;  // ✅ print using dot
        }
    2. using ->
        class Car {
        public:
            int speed;
        };

        int main() {
            Car* c = new Car();
            c->speed = 120;

            cout << "Speed: " << c->speed << endl;  // ✅ print using arrow
        }

## 9. Other Small terms
    1. Static: Is allocated once for the entire lifetime of the program rather than on each function call. 
    2. Const: Value cannot be modified after initialization
    3. Friend fn: Can access private members
    4. Association: General Relationship Aggregation: Weak Relationship Composition: Strong Relationship

## 10. SOLID Principles (The "correct" way of writing code)
    S (Single Class Single Job, if you find a reason to change it change it!)
    O (Open for Inheritance, Closed for Too Much Modifications, Pass it in params)
    L (Base Class should have common methods which will be used in relevant derived Class)
    I (LSP & ISP Similar: ISP Says "base class should be small")
    D (Depends on a common Interface)
