#include<iostream>
using namespace std;

class Shape {
public : 
    Shape() {
        cout << "Constructor called !!";

    }
    virtual void calculateArea() const {
        cout << "base class calculate Area !!" << endl;
    }
    virtual ~Shape() {
        cout << "Base class destructor called !!" << endl;
    }
};

class Rectangle : public Shape {
private:
    int length;
    int breadth;
public :
    Rectangle (int l, int b) {
        length = l;
        breadth = b;
        cout << "Constructor called for Rectangle" << endl;
    }
    virtual ~Rectangle() {
        cout << "Rectangle Destructor called" << endl;
    }
    void calculateArea() const override {
        cout << "Area is : " << length * breadth << endl;
    }
};
class Circle : public Shape {
private :
    int radius;
public :
    Circle(int r ) {
        radius = r;
        cout << "Constructor for Circle called" << endl;
    }
    virtual ~Circle() {
        cout << "Circle Destructor called" << endl;
    }
    void calculateArea() const override {
        cout << "Area is : " << 3.14 * radius * radius << endl;
    }

};

class Singleton
{
    static Singleton& getInstance() {
        //Thread safe in C++11+
        static Singleton instance;
        return instance;
    }

    // Delete copy instructor and assignment operator
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private :
    Singleton() {}
};

int main() {
    Shape *shape1 = new Circle(5);
    Shape *shape2 = new Rectangle(3, 5);

    shape1->calculateArea();
    shape2->calculateArea();
    return 0;
}