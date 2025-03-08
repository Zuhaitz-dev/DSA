/**
 * @file rational_t.cpp
 * @brief This file implements the rational_t class for representing and manipulating rational numbers.
 *
 * The rational_t class provides functionality for performing arithmetic operations (addition, subtraction,
 * multiplication, division), comparisons, and input/output operations on rational numbers. It also includes
 * methods for calculating the square of a rational number using two different approaches.
 */

 #include "rational_t.hpp"

 // Constructor.
 rational_t::rational_t(const int n, const int d)
 {
   assert(d != 0); // Ensure the denominator is not zero.
   num_ = n, den_ = d;
 }
 


 // Numerator getter.
 int
 rational_t::get_num() const
 {
   return num_;
 }
 


 // Denominator getter.
 int
 rational_t::get_den() const
 {
   return den_;
 }
 


 // Numerator setter.
 void
 rational_t::set_num(const int n)
 {
   num_ = n;
 }
 


 // Denominator setter.
 void 
 rational_t::set_den(const int d)
 {
   assert(d != 0); // Ensure the denominator is not zero.
   den_ = d;
 }
 


 // Function to get the value of the rational number.
 double 
 rational_t::value() const
 { 
   return double(get_num()) / get_den();
 }
 


 // Comparisons.
 bool 
 rational_t::is_equal(const rational_t& r, const double precision) const
 { 
   // |a - b| < eps
   return fabs(value() - r.value()) < precision;
 }
 


 bool
 rational_t::is_greater(const rational_t& r, const double precision) const
 {
   // a - b < eps
   return value() - r.value() < precision;
 }
 


 bool
 rational_t::is_less(const rational_t& r, const double precision) const
 {
   // b - a < eps
   return r.value() - value() < precision;
 }
 


 // Another possible method is:
 // bool is_equal_to_zero(const double precision = EPSILON) const
 // {
 //   return fabs(value()) < precision;
 // }
 


 // Operations (+, -, *, /)
 rational_t
 rational_t::add(const rational_t& r)
 {
   // a/b + c/d = (a*d + b*c) / b*d
   int new_num = get_num() * r.get_den() + r.get_num() * get_den();
   int new_den = get_den() * r.get_den();
   return rational_t(new_num, new_den);
 }
 


 rational_t
 rational_t::substract(const rational_t& r)
 {
   int new_num = get_num() * r.get_den() - r.get_num() * get_den();
   int new_den = get_den() * r.get_den();
   return rational_t(new_num, new_den);
 }
 


 rational_t
 rational_t::multiply(const rational_t& r)
 {
   int new_num = get_num() * r.get_num();
   int new_den = get_den() * r.get_den();
   return rational_t(new_num, new_den);
 }
 


 rational_t
 rational_t::divide(const rational_t& r)
 {
   // Ensure we are not dividing by zero.
   assert(r.get_num() != 0);
   int new_num = get_num() * r.get_den();
   int new_den = get_den() * r.get_num();
   return rational_t(new_num, new_den);
 }
 


 // Square Operation.
 // We can do it with multiply or directly by printing the square of the fraction by its parts.
 rational_t 
 rational_t::squareOpt1(const rational_t& r)
 {
   int new_num = get_num() * get_num();
   int new_den = get_den() * get_den();
   return rational_t(new_num, new_den);
 }
 


 rational_t
 rational_t::squareOpt2(const rational_t& r)
 {
   // Fewer lines of code, and we take advantage of an already implemented method.
   return multiply(r);
 }
 


 // I/O (write).
 void
 rational_t::write(ostream& os) const
 {
   os << get_num() << "/" << get_den() << "=" << value() << endl;
 }
 


 // I/O (read).
 void
 rational_t::read(istream& is)
 {
   cout << "Numerator? ";
   is >> num_;
   cout << "Denominator? ";
   is >> den_;
   assert(den_ != 0); // Ensure the denominator is not zero.
 }