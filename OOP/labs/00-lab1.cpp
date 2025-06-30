#include <iostream>
#include <string>

int main() {
    // Print a hello world message to the console
    std::cout << "Hello, World!" << std::endl;  //1.
    
    //2. a. - g.
    int number = 17785;
    std::string text = "Welcome to thjis class";
    float myfloat = -56.1427f;
    std::string str2 = "5262778y";
    int int1 = 5, int2 = 5, in3 = 5;
    bool isTrue = true;
    char str[10];

    //3.
    int age = 0;
    int year = 2025;
    std::cout << "Enter your age"<< std::endl;
    std::cin >> age;
    std::cout << "\nYour year of birth is likey " << year - age<< std::endl;  //3.

    
    //4. a. - c.
    int marks[] = {67, 71, 54, 43, 82, 90};  //4.
    marks[2] = 75;
    int AppliedElectricity = marks[4];  //4.

    // Return 0 to indicate successful execution
    return 0;
}