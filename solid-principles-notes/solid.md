### 1. Single Responsibility Principle (SRP) “Do one thing, do it well”
    -> If a class has a reason to split / change, change it. All it needs is a single reason. 
    class UserRepository {
    public:
        void saveToDB() { /* DB logic */ }
    };

    class EmailService {
    public:
        void sendEmail() { /* Email logic */ }
    };

### 2. Open/Closed Principle (OCP) “Add new features without touching old code”
    -> Any Software should be Open for extension, Closed for modification. 
    class Shape {
    public:
        virtual double area() = 0;
    };

    class Circle : public Shape {
    public:
        double r;
        double area() override { return 3.14 * r * r; }
    };

    class Rectangle : public Shape {
    public:
        double l, b;
        double area() override { return l * b; }
    };   

### 3. Liskov Substitution Principle (LSP) “Child should behave like a true parent”
    -> Derived Class should be replacement for Base class, without breaking Base class behaviour. 
    class Bird {};

    class FlyingBird : public Bird {
    public:
        virtual void fly() {}
    };

    class Sparrow : public FlyingBird {};

    class Penguin : public Bird {};  // no fly

### 4. Interface Segregation Principle (ISP) "Keep interfaces small and specific" 
    -> Don't Force overrides in Derived class 
    class Printer {
    public:
        virtual void print() = 0;
    };

    class Scanner {
    public:
        virtual void scan() = 0;
    };

    class SimplePrinter : public Printer {
    public:
        void print() override {}
    };
    
    class SimpleScanner: public Scanner {
    public:
        void print() override {}
    }

### 5. Dependency Inversion Principle (DIP) “Depend on interface, not implementation”
    -> High Level Modules should be Interface : Class (Abstraction), not concrete class
    class InputDevice{
        virtual void input() = 0;
    };

    class Keyboard : public InputDevice{
        void input() override{}
    };

    class Computer {
    private: 
        InputDevice* device;
    public: 
        Computer(InputDevice* d) : device(d){}
    };