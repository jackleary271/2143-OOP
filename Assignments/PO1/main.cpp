/*****************************************************************************
*
*  Author:           Jack Leary
*  Personal Email:   jackleary645@gmail.com
*  School Email:     jeleary0604@my.msutexas.edu
*  Label:            PO1
*  Title:            Fraction Class
*  Course:           2143 OOP
*  Semester:         Fall 2024
*
*****************************************************************************/

#include "Fraction.h"
#include <iostream>

/**
 * getFractionInput
 *
 * Description:
 *      Prompts the user to input a fraction by entering the numerator and
 *      denominator. Validates that the denominator is not zero before
 *      creating a Fraction object.
 *
 * Params:
 *      - Fraction& frac: Reference to a Fraction object that will be populated
 *        with the user's input values.
 *
 * Returns:
 *      - None (void function).
 */

void getFractionInput(Fraction& frac) {
    int numerator;      // Variable to store the numerator of the fraction
    int denominator;    // Variable to store the denominator of the fraction

    // Prompt user for a fraction
    std::cout << "Enter the numerator and denominator (e.g., 1 2 for 1/2): ";
    std::cin >> numerator >> denominator;

    // Validate the denominator to prevent division by zero
    while (denominator == 0) {
        std::cout << "Denominator cannot be zero. Please enter again: ";
        std::cin >> denominator;  // Re-prompt for a valid denominator
    }

    // Create the fraction using user input
    frac = Fraction(numerator, denominator);
}

int main() {
    Fraction frac1;     // Fraction variable for the first input
    Fraction frac2;     // Fraction variable for the second input
    Fraction result;    // Fraction variable to store the result of operations

    // Addition
    std::cout << "Addition:\n";
    getFractionInput(frac1);    // Get user input for the first fraction
    getFractionInput(frac2);    // Get user input for the second fraction
    result = frac1 + frac2;     // Perform addition of the fractions
    std::cout << frac1 << " + " << frac2 << " = " << result << std::endl;
    std::cout << std::endl;     // Print a newline for separation

    // Subtraction
    std::cout << "Subtraction:\n";
    getFractionInput(frac1);    // Get user input for the first fraction
    getFractionInput(frac2);    // Get user input for the second fraction
    result = frac1 - frac2;     // Perform subtraction of the fractions
    std::cout << frac1 << " - " << frac2 << " = " << result << std::endl;
    std::cout << std::endl;     // Print a newline for separation

    // Multiplication
    std::cout << "Multiplication:\n";
    getFractionInput(frac1);    // Get user input for the first fraction
    getFractionInput(frac2);    // Get user input for the second fraction
    result = frac1 * frac2;     // Perform multiplication of the fractions
    std::cout << frac1 << " * " << frac2 << " = " << result << std::endl;
    std::cout << std::endl;     // Print a newline for separation

    // Division
    std::cout << "Division:\n";
    getFractionInput(frac1);    // Get user input for the first fraction
    getFractionInput(frac2);    // Get user input for the second fraction
    result = frac1 / frac2;     // Perform division of the fractions
    std::cout << frac1 << " / " << frac2 << " = " << result << std::endl;
    std::cout << std::endl;     // Print a newline for separation

    // Comparison
    std::cout << "Comparison:\n";
    getFractionInput(frac1);        // Get user input for the first fraction
    getFractionInput(frac2);        // Get user input for the second fraction
    bool isEqual = frac1 == frac2;  // Check if the fractions are equal
    std::cout << frac1 << " == " << frac2 << " is " << (isEqual ? "true" : "false") << std::endl;
    std::cout << std::endl;         // Print a newline for separation

    return 0;
}
