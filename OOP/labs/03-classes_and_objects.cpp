#include <iostream>

class Quadrilateral{
    int x;
    int y;

    public:
    //2. constructor
    Quadrilateral(){
        x = 1;
        y = 1;
    }

    //3. destructor
    ~Quadrilateral(){
        std::cout << "Nothing to delete" << std::endl;
    }

    //1. a
    void set_values(int X, int Y){
        x = X;
        y = Y;
    }
    int area(){
        return (x * y);
    }
};

int main(void){
    //4. 
    Quadrilateral square, rectangle;

    //5.
    square.set_values(10, 10);

    //6.
    rectangle.set_values(5, 10);

    //7.
    std::cout << "Area of square: " << square.area() << std::endl;
    std::cout << "Area of rectangle: " << rectangle.area() << std::endl;

    return (0);
}