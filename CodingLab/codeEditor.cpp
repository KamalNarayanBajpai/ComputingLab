#include <iostream>
#include <string>
#include <limits> // Required for clearing the input buffer
using namespace std;
/**
 * @brief Converts an integer into a string of Unicode superscript characters.
 * @param n The integer to convert.
 * @return A std::string containing the superscript representation.
 */
std::string toSuperscript(int n) {
    std::string numStr = std::to_string(n);
    std::string result = "";
    for (char c : numStr) {
        switch (c) {
            case '0': result += "⁰"; break;
            case '1': result += "¹"; break;
            case '2': result += "²"; break;
            case '3': result += "³"; break;
            case '4': result += "⁴"; break;
            case '5': result += "⁵"; break;
            case '6': result += "⁶"; break;
            case '7': result += "⁷"; break;
            case '8': result += "⁸"; break;
            case '9': result += "⁹"; break;
            case '-': result += "⁻"; break; 
        }
    }
    return result;
}

string toSubscript(int n) {
    std::string numStr = std::to_string(n);
    std::string result = "";
    for (char c : numStr) {
        switch (c) {
            case '0': result += "₀"; break;
            case '1': result += "₁"; break;
            case '2': result += "₂"; break;
            case '3': result += "₃"; break;
            case '4': result += "₄"; break;
            case '5': result += "₅"; break;
            case '6': result += "₆"; break;
            case '7': result += "₇"; break;
            case '8': result += "₈"; break;
            case '9': result += "₉"; break;
            case '-': result += "₋"; break; // Handle negative numbers
        }
    }
    return result;
}
void handleSubscript() {
    string base;
    int x;
    cout << "\nEnter the base value: ";
    cin >> base;
    cout << "Enter the subscript value (x): ";
    cin >> x;
    cout << "\n Result: " << base << toSubscript(x) << endl;
}
void handleSuperscript() {
    std::string base;
    int x;
    std::cout << "\nEnter the base value: ";
    std::cin >> base;
    std::cout << "Enter the superscript value (x): ";
    std::cin >> x;
    std::cout << "\n✅ Result: " << base << toSuperscript(x) << std::endl;
}

void handleIntegration() {
    int lowerLimit, upperLimit;
    std::string functionStr;

    cout << "\nEnter the lower limit: ";
    cin >> lowerLimit;
    cout << "Enter the upper limit: ";
    cin >> upperLimit;
    cout << "Enter the function to integrate (e.g., x^2 + 2x): ";
    
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, functionStr);

    cout << "\n Result: ∫" << toSuperscript(upperLimit) << toSubscript(lowerLimit)
              << " (" << functionStr << ") dx" << std::endl;
}

void displayMenu() {
    std::cout << "=== Mathematical Formatter ===\n";
    std::cout << "1. Display in Subscript Form (baseₓ)\n";
    std::cout << "2. Display in Superscript Form (baseˣ)\n";
    std::cout << "3. Display in Integration Form (∫)\n";
    std::cout << "4. Exit Program\n";
    std::cout << "==============================\n";
    std::cout << "Enter your choice (1-4): ";
}

int main() {
    int choice = 0;
    do {
        displayMenu();
        cin >> choice;
        while (std::cin.fail()) {
            std::cout << " Invalid input. Please enter a number.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayMenu();
            std::cin >> choice;
        }

        switch (choice) {
            case 1:
                handleSubscript();
                break;
            case 2:
                handleSuperscript();
                break;
            case 3:
                handleIntegration();
                break;
            case 4:
                std::cout << "\nExited program. \n";
                break;
            default:
                std::cout << "\n Invalid choice. Please enter a number between 1 and 4.\n";
                break;
        }

        if (choice != 4) {
            std::cout << "\n----------------------------------------\n\n";
        }

    } while (choice != 4);
    return 0;
}