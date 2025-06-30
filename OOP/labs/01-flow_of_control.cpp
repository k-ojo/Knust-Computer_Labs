#include <iostream>

int main() {
    float hight = 0.0f, weight = 0.0f, bmi = 0.0f;
    std::cout << "Enter your height in meters: ";
    std::cin >> hight;
    std::cout << "Enter your weight in kilograms: ";
    std::cin >> weight;

    if (hight <= 0 || weight <= 0) {
        std::cout << "Height and weight must be positive numbers." << std::endl;
        return 1; // Exit with an error code
    }

    bmi = weight / (hight * hight);
    std::cout << "Your BMI is: " << bmi << std::endl;

    if (bmi < 18.5) {
        std::cout << "You are underweight." << std::endl;
    } else if (bmi < 24.9) {
        std::cout << "You have a normal weight." << std::endl;
    } else if (bmi < 29.9) {
        std::cout << "You are overweight." << std::endl;
    } else {
        std::cout << "You are obese." << std::endl;
    }

    return 0; // Exit successfully
}
// This program calculates the Body Mass Index (BMI) based on user input for height and weight.
// It also provides a classification based on the calculated BMI.
// The program checks for valid input and handles cases where height or weight is not positive.
// The BMI categories are:
// - Underweight: BMI < 18.5
// - Normal weight: 18.5 <= BMI < 24.9
// - Overweight: 24.9 <= BMI < 29.9
// - Obese: BMI >= 30
// The program uses the C++17 standard for compilation.
