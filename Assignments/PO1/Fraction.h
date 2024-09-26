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

#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

/**
 * Class Fraction
 *
 * Description:
 *      This class represents a fraction with a numerator and denominator and provides
 *      basic operations like addition, subtraction, multiplication, and division of fractions.
 *      It automatically reduces fractions to their simplest form upon creation and operation.
 *
 * Public Methods:
 *      - Fraction(int num, int den): Constructor to initialize the fraction
 *      - Fraction operator+(const Fraction& other) const: Adds two fractions
 *      - Fraction operator-(const Fraction& other) const: Subtracts one fraction from another
 *      - Fraction operator*(const Fraction& other) const: Multiplies two fractions
 *      - Fraction operator/(const Fraction& other) const: Divides one fraction by another
 *      - bool operator==(const Fraction& other) const: Compares two fractions for equality
 *
 * Private Methods:
 *      - int gcd(int a, int b) const: Calculates the greatest common divisor (GCD) of two integers
 *      - int lcm(int a, int b) const: Calculates the least common multiple (LCM) of two integers
 *      - void reduce(): Reduces the fraction to its simplest form by dividing by the GCD
 *
 * Usage:
 *      Fraction frac1(1, 2); // Create a fraction 1/2
 *      Fraction frac2(3, 4); // Create a fraction 3/4
 *      Fraction result = frac1 + frac2; // Add fractions
 *      std::cout << result; // Output result
 */

class Fraction {
private:
    int numerator;   // The numerator of the fraction
    int denominator; // The denominator of the fraction

    // Private helper methods
    int gcd(int a, int b) const; // Calculates the greatest common divisor (GCD)
    int lcm(int a, int b) const; // Calculates the least common multiple (LCM)
    void reduce(); // Reduces the fraction by dividing by the GCD

public:
    /**
     * Public : Fraction
     *
     * Description:
     *      Constructor for the Fraction class.
     * Params:
     *      - num (int): Numerator
     *      - den (int): Denominator (must be non-zero)
     * Returns:
     *      - A Fraction object with the given numerator and denominator
     */
    Fraction(int num = 0, int den = 1);

    // Operator overloads
    Fraction operator+(const Fraction& other) const; // Overload for addition
    Fraction operator-(const Fraction& other) const; // Overload for subtraction
    Fraction operator*(const Fraction& other) const; // Overload for multiplication
    Fraction operator/(const Fraction& other) const; // Overload for division
    bool operator==(const Fraction& other) const;    // Overload for equality comparison

    // Friend function for output stream operator overload (<<)
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);
};

#endif
