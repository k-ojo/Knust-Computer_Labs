#include <iostream>
#include <string>


int add(int a, int b){
    return (a, b);
}
int subtract(int a, int b){
    return (a - b);
}

int multiply(int a, int b){
    return (a * b);
}

int divide(int a, int b){
    if (b == 0){
        std::cerr << "Cannot divide by zero" << std::endl;
        return (-1);
    }
    return (a / b);
}

class Student{
    std::string Name;
    int ID;

    public:

    void setName(std::string name){
        Name = name;
    }
    void setID(int id){
        ID = id;
    }

    std::string getName(){
        return Name;
    }

    int getID(){
        return ID;
    }

    void showInfo(){
        std::cout << "Name: " << Name << std::endl;
        std::cout << "ID: " << ID << std::endl;
    }

};

int main(void){

    //1-4
    Student *students[100];
    std::string name;

    int count = 0;
    int option = 0;

    do{
        std::cout << "Enter student name: " << std::endl;
        std::cin >> name;

        students[count] = new Student;
        students[count]->setName(name);
        students[count]->setID(count);
        count++;

        std::cout << "Do you want to add more? (Enter 1 for yes and 0 for no)";
        std::cin >> option;

    }while (count < 100 && (option != 0));

    for (int i = 0; i < count; i++){
        students[i]->showInfo();
    }

    //5

    int (*operation)(int, int);
    int a, b, op;

    do{
        std::cout << "Enter first operand: ";
        std::cin >> a;

        std::cout << "Enter second operand: ";
        std::cin >> b;

        std::cout << "Choose and operation" << std::endl;
        std::cout << "1. add\n2. substact\n3. multiply\n4. Divide" << std::endl;
        std::cout << "Enter option (1-4): ";
        std::cin >> op;

        switch (op)
        {
        case 1:
            /* code */
            operation = add;
            break;
        case 2:
            /* code */
            operation = subtract;
            break;
        case 3:
            /* code */
            operation = multiply;
            break;
        case 4:
            /* code */
            operation = divide;
            break;
        
        default:
            operation = add;
            break;
        }

        int answer = operation(a, b);
        std::cout << "Answer is: " << answer <<std::endl;
        
        std::cout << "Continue? (Enter 1 for yes and 0 for no)";
        std::cin >> option;

    }while (option != 0);

}