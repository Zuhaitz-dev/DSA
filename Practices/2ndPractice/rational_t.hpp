/**
 * @file rational_t.hpp
 * @brief This file defines the rational_t class for representing and manipulating rational numbers.
 *
 * The rational_t class provides functionality for performing arithmetic operations (addition, subtraction,
 * multiplication, division), comparisons, and input/output operations on rational numbers. It also includes
 * methods for calculating the opposite and reciprocal of a rational number.
 */

 #pragma once

 #include <iostream>
 #include <cassert>
 #include <cmath>
 
 // Definition of an epsilon for floating-point comparisons.
 #define EPSILON 1e-6
 
 using namespace std;
 
 class rational_t
 {
  public:
   // Default and parameterized constructor.
   rational_t(const int = 0, const int = 1);
   ~rational_t() {}
 
   // Getter methods.
   int get_num() const;  // Returns the numerator.
   int get_den() const;  // Returns the denominator.
 
   // Setter methods.
   void set_num(const int);  // Assigns a new numerator.
   void set_den(const int);  // Assigns a new denominator (ensures it is not zero).
 
   // Arithmetic operations.
   double value(void) const;       // Calculates the real (double) value of the rational number.
   rational_t opposite(void) const;  // Returns the opposite of the rational number.
   rational_t reciprocal(void) const;  // Returns the reciprocal (swaps numerator and denominator).
 
   // Comparison methods: uses EPSILON for tolerance in comparisons.
   bool is_equal(const rational_t&, const double precision = EPSILON) const;
   bool is_greater(const rational_t&, const double precision = EPSILON) const;
   bool is_less(const rational_t&, const double precision = EPSILON) const;
 
   // Binary operations.
   rational_t add(const rational_t&) const;
   rational_t substract(const rational_t&) const;
   rational_t multiply(const rational_t&) const;
   rational_t divide(const rational_t&) const;
 
   // Input/output methods.
   void write(ostream& os = cout) const;
   void read(istream& is = cin);
 
  private:
   // Attributes: numerator and denominator.
   int num_, den_;
 };
 
 // Overloads for input/output operators to facilitate interaction with streams.
 ostream& operator<<(ostream& os, const rational_t&);
 istream& operator>>(istream& is, rational_t&);
 
 // Overloads for arithmetic operators for rational_t.
 rational_t operator+(const rational_t&, const rational_t&);
 rational_t operator-(const rational_t&, const rational_t&);
 rational_t operator*(const rational_t&, const rational_t&);
 rational_t operator/(const rational_t&, const rational_t&);