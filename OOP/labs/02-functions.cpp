#include <iostream>
#include <string>

inline int sum(int n){
    return (n * (n + 1) / 2);
}

inline int add(int a, int b){
    return (a + b);
}

inline int add(int a, int b, int c){
    return (a + b + c);
}

inline float add(float a, float b){
    return (a + b);
}

inline std::string add(std::string a, int b){
    return (a + std::to_string(b));
}

inline std::string add(std::string a, std::string b){
    return (a + b);
}

int main(void){

    //1.
    int n;
    std::cout << "Enter an integer (n) to calculate" << std::endl;
    std::cin >> n;
    std::cout << "The sum is : "<< sum(n) << std::endl;

    //2.
    std::cout << "Added integers: " << add(4, 6) << std::endl;
    std::cout << "Added integers: " << add(4, 6, 7) << std::endl;
    std::cout << "Added floats: " << add(5.0f, 6.0f) << std::endl;
    std::cout << "Added integers: " << add("The answer is: ", 6) << std::endl;
    std::cout << "Added integers: " << add("Hello ", "World") << std::endl;

    //3.
    /**
     * made all the defined functions inline becase they are short calculations
     */


}