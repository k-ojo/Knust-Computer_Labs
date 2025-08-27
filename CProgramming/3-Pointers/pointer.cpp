#include <iostream>

void pointerExample(int **param) {
    **param = 20;
}

/**
 * 
 */
class Example {
public:
    int var;
    std::string name;
};

int main() {

    int var = 10;
    int *param = &var;
    int **ptrparam = &param;

    Example *ptr = new Example();

    ptr->var = 5;
    ptr->name = "Example Object";

    void (*ptrfunc)(int **) = pointerExample;

    std::cout << "Before pointerExample: " << ptr << std::endl;

    // Call the function with value
    pointerExample(&param);

    std::cout << "After pointerExample: " << **ptrparam << std::endl;


    return 0;
}

