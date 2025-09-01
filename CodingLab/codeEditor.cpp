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
            case '-': result += "⁻"; break; // Handle negative numbers
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
    cout << "\n✅ Result: " << base << toSubscript(x) << endl;
}

/**
 * @brief Handles the user's choice to display superscript notation.
 * Prompts for a base and a superscript value.
 */
void handleSuperscript() {
    std::string base;
    int x;
    std::cout << "\nEnter the base value: ";
    std::cin >> base;
    std::cout << "Enter the superscript value (x): ";
    std::cin >> x;
    std::cout << "\n✅ Result: " << base << toSuperscript(x) << std::endl;
}

/**
 * @brief Handles the user's choice to display integral notation.
 * Prompts for limits and a function, then displays the format.
 */
void handleIntegration() {
    int lowerLimit, upperLimit;
    std::string functionStr;

    std::cout << "\nEnter the lower limit: ";
    std::cin >> lowerLimit;
    std::cout << "Enter the upper limit: ";
    std::cin >> upperLimit;
    std::cout << "Enter the function to integrate (e.g., x^2 + 2x): ";
    // Clear the input buffer before reading a line of text
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, functionStr);

    // Display using the integral symbol ∫ (U+222B)
    std::cout << "\n✅ Result: ∫" << toSuperscript(upperLimit) << toSubscript(lowerLimit)
              << " (" << functionStr << ") dx" << std::endl;
}

/**
 * @brief Displays the main menu to the user.
 */
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
        std::cin >> choice;

        // Basic input validation to check if the input is a number
        while (std::cin.fail()) {
            std::cout << " Invalid input. Please enter a number.\n\n";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
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