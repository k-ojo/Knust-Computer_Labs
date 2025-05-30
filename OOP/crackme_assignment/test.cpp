#include <iostream>
#include <string>

std::string password = "";

int main(int ac, char** av) {
    if (ac < 2) {
        std::cerr << "Password is required (Usage: " << av[0] << " [password])" << std::endl;
        return 1;
    }

    if (ac == 2) {
        std::string input = av[1];
        if (input == password) {
            std::cout << "Access granted!" << std::endl;
        } else {
            std::cerr << "Access denied!" << std::endl;
            return 1;
        }
    }

    if (ac > 2) {
        std::cerr << "Too many arguments (Usage: " << av[0] << " [password])" << std::endl;
        return 1;
    }

    return 0;
}