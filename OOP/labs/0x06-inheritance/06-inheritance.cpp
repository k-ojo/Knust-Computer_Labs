#include <iostream>

class CPolygon {
protected:
    int width, height;

public:
    void set_values(int a, int b) {
        width = a;
        height = b;
    }
};

class CRectangle : public CPolygon {
public:
    int area() {
        return width * height;
    }
};

class CTriangle : public CPolygon {
public:
    int area() {
        return (width * height) / 2;
    }
};


int main() {

    CRectangle rect;
    CTriangle trgl;

    rect.set_values(10, 5);
    trgl.set_values(10, 5);

    std::cout << "Area of rectangle: " << rect.area() << std::endl;
    std::cout << "Area of triangle: " << trgl.area() << std::endl;
    return 0;

}