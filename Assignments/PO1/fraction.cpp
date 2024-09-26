#include "Fraction.h"
#include <iostream>
#include <stdexcept>

// Constructor with validation for denominator
Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
    if (den == 0) {
        throw std::invalid_argument("Denominator cannot be zero.");
    }
    reduce(); // Reduce the fraction to its simplest form
}

/**
 * Private : gcd
 *
 * Description:
 *      This function calculates the greatest common divisor (GCD) of two integers.
 * Params:
 *      - a (int): First integer
 *      - b (int): Second integer
 * Returns:
 *      - int: The greatest common divisor of a and b
 */
int Fraction::gcd(int a, int b) const {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * Private : lcm
 *
 * Description:
 *      This function calculates the least common multiple (LCM) of two integers.
 * Params:
 *      - a (int): First integer
 *      - b (int): Second integer
 * Returns:
 *      - int: The least common multiple of a and b
 */
int Fraction::lcm(int a, int b) const {
    return (a * b) / gcd(a, b);  // lcm = (a * b) / gcd(a, b)
}

/**
 * Private : reduce
 *
 * Description:
 *      Simplifies the fraction by dividing both numerator and denominator by their greatest common divisor (GCD).
 */
void Fraction::reduce() {
    int divisor = gcd(numerator, denominator); // Find GCD
    numerator /= divisor; // Simplify numerator
    denominator /= divisor; // Simplify denominator

    // If the denominator is negative, move the sign to the numerator
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

/**
 * Public : operator+
 *
 * Description:
 *      Adds two fractions by finding the least common denominator (LCD) and adjusting numerators before summing.
 * Params:
 *      - other (const Fraction&): The second fraction to add
 * Returns:
 *      - Fraction: The result of the addition
 */
Fraction Fraction::operator+(const Fraction& other) const {
    int commonDenominator = lcm(denominator, other.denominator); // Find common denominator
    int numerator1 = numerator * (commonDenominator / denominator); // Adjust numerators
    int numerator2 = other.numerator * (commonDenominator / other.denominator);
    int resultNumerator = numerator1 + numerator2; // Add numerators

    return Fraction(resultNumerator, commonDenominator); // Return result
}

/**
 * Public : operator-
 *
 * Description:
 *      Subtracts one fraction from another by using the least common denominator (LCD).
 * Params:
 *      - other (const Fraction&): The second fraction to subtract
 * Returns:
 *      - Fraction: The result of the subtraction
 */
Fraction Fraction::operator-(const Fraction& other) const {
    int commonDenominator = lcm(denominator, other.denominator); // Find common denominator
    int numerator1 = numerator * (commonDenominator / denominator); // Adjust numerators
    int numerator2 = other.numerator * (commonDenominator / other.denominator);
    int resultNumerator = numerator1 - numerator2; // Subtract numerators

    return Fraction(resultNumerator, commonDenominator); // Return result
}

/**
 * Public : operator*
 *
 * Description:
 *      Multiplies two fractions by multiplying numerators and denominators directly.
 * Params:
 *      - other (const Fraction&): The second fraction to multiply
 * Returns:
 *      - Fraction: The result of the multiplication
 */
Fraction Fraction::operator*(const Fraction& other) const {
    int resultNumerator = numerator * other.numerator; // Multiply numerators
    int resultDenominator = denominator * other.denominator; // Multiply denominators

    return Fraction(resultNumerator, resultDenominator); // Return result
}

/**
 * Public : operator/
 *
 * Description:
 *      Divides two fractions by multiplying by the reciprocal of the second fraction.
 * Params:
 *      - other (const Fraction&): The second fraction to divide by
 * Returns:
 *      - Fraction: The result of the division
 */
Fraction Fraction::operator/(const Fraction& other) const {
    int resultNumerator = numerator * other.denominator; // Multiply by the reciprocal's numerator
    int resultDenominator = denominator * other.numerator; // Multiply by the reciprocal's denominator

    return Fraction(resultNumerator, resultDenominator); // Return result
}

/**
 * Public : operator==
 *
 * Description:
 *      Compares two fractions for equality by checking if their numerators and denominators are the same.
 * Params:
 *      - other (const Fraction&): The second fraction to compare
 * Returns:
 *      - bool: True if the fractions are equal, false otherwise
 */
bool Fraction::operator==(const Fraction& other) const {
    return numerator == other.numerator && denominator == other.denominator; // Compare numerators and denominators
}

/**
 * Friend : operator<<
 *
 * Description:
 *      Overloads the output stream operator to display fractions in "numerator/denominator" format.
 * Params:
 *      - os (std::ostream&): The output stream
 *      - frac (const Fraction&): The fraction to print
 * Returns:
 *      - std::ostream&: The output stream after insertion
 */
std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    os << frac.numerator << "/" << frac.denominator; // Print the fraction
    return os;
}
