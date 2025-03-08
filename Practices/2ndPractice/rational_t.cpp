/**
 * @file rational_t.cpp
 * @brief This file implements the rational_t class for representing and manipulating rational numbers.
 *
 * The rational_t class provides functionality for performing arithmetic operations (addition, subtraction,
 * multiplication, division), comparisons, and input/output operations on rational numbers. It also includes
 * methods for calculating the opposite and reciprocal of a rational number.
 */

 #include "rational_t.hpp"
 #include <cmath>
 
 // Constructor: initializes the rational number, ensuring the denominator is not zero.
 rational_t::rational_t(const int n, const int d)
 {
   assert(d != 0); // Ensures the denominator is valid.
   num_ = n;
   den_ = d;
 }
 


 // Returns the stored numerator.
 inline
 int
 rational_t::get_num() const
 {
   return num_;
 }
 


 // Returns the stored denominator.
 inline
 int
 rational_t::get_den() const
 {
   return den_;
 }
 


 // Assigns a new value to the numerator.
 void
 rational_t::set_num(const int n)
 {
   num_ = n;
 }
 


 // Assigns a new value to the denominator, validating it with assert.
 void
 rational_t::set_den(const int d)
 {
   assert(d != 0); // Prevents assigning a zero denominator.
   den_ = d;
 }
 


 // Calculates the floating-point value of the rational number.
 inline
 double
 rational_t::value() const
 { 
   // Converts to double to ensure real division.
   return double(get_num()) / get_den();
 }
 


 // Returns the opposite of the rational number (multiplies the numerator by -1).
 rational_t
 rational_t::opposite() const
 { 
   // Creates a new rational with the negated numerator.
   return rational_t((-1) * get_num(), get_den());
 }
 


 // Returns the reciprocal of the rational number (swaps numerator and denominator).
 rational_t
 rational_t::reciprocal() const
 { 
   return rational_t(get_den(), get_num());
 }

 

 // Checks if two rational numbers are equal, considering a given precision.
 // |a - b| < precision
 bool
 rational_t::is_equal(const rational_t& r, const double precision) const
 { 
   // Uses fabs to compare the absolute difference with the precision.
   return fabs(value() - r.value()) < precision;
 }
 


 // Checks if the current rational number is greater than another, with a given precision.
 // |a - b| > precision
 bool
 rational_t::is_greater(const rational_t& r, const double precision) const
 {
   // If the difference is greater than the precision, it is considered greater.
   return (value() - r.value()) > precision;
 }
 


 // Checks if the current rational number is less than another.
 bool
 rational_t::is_less(const rational_t& r, const double precision) const
 {
   // Reuses is_greater to invert the comparison.
   return r.is_greater(*this, precision);
 }
 


 // Adds two rational numbers.
 // Uses the formula: a / b + c / d = (a * d + b * c) / (b * d)
 rational_t
 rational_t::add(const rational_t& r) const
 {
   return rational_t(get_num() * r.get_den() + get_den() * r.get_num(), 
                     get_den() * r.get_den());
 }
 


 // Subtracts two rational numbers.
 // Implements subtraction by adding the opposite of the second operand.
 rational_t
 rational_t::substract(const rational_t& r) const
 {
   return add(r.opposite());
 }
 


 // Multiplies two rational numbers.
 // Formula: (a / b) * (c / d) = (a * c) / (b * d)
 rational_t
 rational_t::multiply(const rational_t& r) const
 {
   return rational_t(get_num() * r.get_num(), get_den() * r.get_den());
 }
 


 // Divides two rational numbers.
 // Performs division by multiplying by the reciprocal of the divisor.
 rational_t
 rational_t::divide(const rational_t& r) const
 {
   return multiply(r.reciprocal());
 }
 


 // Overloads the + operator for rational numbers.
 rational_t
 operator+(const rational_t& a, const rational_t& b)
 {
   return a.add(b);
 }
 


 // Overloads the - operator for rational numbers.
 rational_t
 operator-(const rational_t& a, const rational_t& b)
 {
   return a.substract(b);
 }
 


 // Overloads the * operator for rational numbers.
 rational_t
 operator*(const rational_t& a, const rational_t& b)
 {
   return a.multiply(b);
 }
 


 // Overloads the / operator for rational numbers.
 rational_t
 operator/(const rational_t& a, const rational_t& b)
 {
   return a.divide(b);
 }
 


 // Writes the rational number to the output stream in the format: num/den=value.
 void
 rational_t::write(ostream& os) const
 {
   os << get_num() << "/" << get_den() << "=" << value() << endl;
 }
 


 // Reads the numerator and denominator from the input stream.
 // Validates that the denominator is not zero.
 void
 rational_t::read(istream& is)
 {
   is >> num_ >> den_;
   assert(den_ != 0); // Ensures the denominator is valid.
 }
 


 // Overloads the << operator: allows sending the object to an output stream.
 ostream& 
 operator<<(ostream& os, const rational_t& r)
 {
   r.write(os);
   return os;
 }
 


 // Overloads the >> operator: allows reading the object from an input stream.
 istream&
 operator>>(istream& is, rational_t& r)
 {
   r.read(is);
   return is;
 }