#include <iostream>
#define MAX_NAME_LENGTH 50

class Colour {
    char name[MAX_NAME_LENGTH];
public:
    void showColour() const{
        std::cout << "Colour: " << name << std::endl;
    }
};

class Hex: public Colour {
    std::string red;
    std::string green;
    std::string blue;
public:
    void showColour() const {
        Colour::showColour();
        std::cout << "Hex Colour: " << red << ", " << green << ", " << blue << std::endl;
    }

    Hex addColour(const Hex& other) const{
        Hex result;
        // Assuming red, green, and blue are in hexadecimal format
        result.red = this->red + other.red;
        result.green = this->green + other.green;
        result.blue = this->blue + other.blue;
        return result;
    }

};

class RGB: public Colour {
    int red;
    int green;
    int blue;
public:
    void showColour() const {
        Colour::showColour();
        std::cout << "RGB Colour: " << red << ", " << green << ", " << blue << std::endl;
    }

    RGB addColour(const RGB& other) const{
        RGB result;
        result.red = this->red + other.red;
        result.green = this->green + other.green;
        result.blue = this->blue + other.blue;
        return result;
    }
};