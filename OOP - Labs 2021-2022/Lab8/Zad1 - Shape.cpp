#include <iostream>

using namespace std;

class Shape {
public:
    Shape(){}
    virtual void draw() {
        cout << "Drawing a shape.\n";
    }
};
class Rectangle:public Shape{
public:
    Rectangle(){}
    void draw(){
        cout<<"Drawing a rectangle.\n";
    }
};
int main() {
    Shape* shape;
    shape->Shape::draw();
    shape = new Rectangle;
    shape->draw();
    return 0;
}
