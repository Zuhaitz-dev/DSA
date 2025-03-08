/**
 * @file rational_t.hpp
 * @brief This header file defines the rational_t class for representing and manipulating rational numbers.
 *
 * The rational_t class provides functionality for performing arithmetic operations (addition, subtraction,
 * multiplication, division), comparisons, and input/output operations on rational numbers. It also includes
 * methods for calculating the square of a rational number using two different approaches.
 */

 #pragma once

 #include <iostream>
 #include <cassert>
 #include <cmath>
 
 #define EPSILON 1e-6 // Precision for floating-point comparisons.
 
 using namespace std;
 
 class rational_t
 {
  public:
   // Constructor and destructor.
   rational_t(const int = 0, const int = 1); // Default constructor with optional numerator and denominator.
   ~rational_t() {} // Destructor.
 
   // Getters for numerator and denominator.
   int get_num() const; // Returns the numerator.
   int get_den() const; // Returns the denominator.
 
   // Setters for numerator and denominator.
   void set_num(const int); // Sets the numerator.
   void set_den(const int); // Sets the denominator (ensures it is not zero).
 
   // Function to get the value of the rational number.
   double value(void) const; // Returns the floating-point value of the rational number.
 
   // Boolean functions. Check if the rational number is equal, greater, or less than another rational number.
   bool is_equal(const rational_t&, const double precision = EPSILON) const; // Checks equality.
   bool is_greater(const rational_t&, const double precision = EPSILON) const; // Checks if greater.
   bool is_less(const rational_t&, const double precision = EPSILON) const; // Checks if less.
   // bool is_equal_to_zero(const double precision = EPSILON) const; // Optional: Checks if equal to zero.
 
   // Arithmetic operations.
   rational_t add(const rational_t&); // Adds two rational numbers.
   rational_t substract(const rational_t&); // Subtracts two rational numbers.
   rational_t multiply(const rational_t&); // Multiplies two rational numbers.
   rational_t divide(const rational_t&); // Divides two rational numbers.
 
   // (a/b)^2 = (a^2 / b^2)
   rational_t squareOpt1(const rational_t&); // Squares the rational number (method 1).
   rational_t squareOpt2(const rational_t&); // Squares the rational number (method 2).
 
   // Functions to write and read the rational number (I/O).
   void write(ostream& = cout) const; // Writes the rational number to an output stream.
   void read(istream& = cin); // Reads the rational number from an input stream.
 
  private:
   // Attributes (numerator and denominator).
   int num_, den_; // Private members to store the numerator and denominator.
 };