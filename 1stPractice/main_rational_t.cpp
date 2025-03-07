/**
 * @file main_rational_t.cpp
 * @brief This C++ file demonstrates the usage of the rational_t class for performing arithmetic operations and comparisons on rational numbers.
 *
 * This file provides a comprehensive example of how to create, manipulate, and compare rational numbers using the rational_t class.
 * It includes examples of addition, subtraction, multiplication, division, and comparison operations, as well as methods for
 * reading and writing rational numbers.
 */

 #include <iostream>
 #include <cmath>
 
 #include "rational_t.hpp"
 
 using namespace std;
 
 int main()
 {
   // Creation of objects.
   rational_t a(1, 2), b(3), c;
 
   // Print the value of the objects.
   cout << "a.value()= " << a.value() << endl;
   cout << "b.value()= " << b.value() << endl;
   cout << "c.value()= " << c.value() << endl;
 
   // Write the objects (a, b).
   cout << "a: ";
   a.write();
   cout << "b: ";
   b.write();
 
   // Read the object (c).
   c.read();
   cout << "c: ";
   c.write();
 
   // PART II.
   // Creation of objects to be compared.
   rational_t x(2, 3), y(1, 3);
   
   // Write the objects (x, y).
   x.write();
   y.write();
   
   // Comparison of objects (Applying ternary operators).
   cout << "x == y? " << (x.is_equal(y) ? "true" : "false") << endl;
   cout << "x < y? " << (x.is_greater(y) ? "true" : "false") << endl;
   cout << "x > y? " << (x.is_less(y) ? "true" : "false") << endl;
   // cout << "x == 0? " << (x.is_equal_to_zero() ? "true" : "false") << endl;
 
   // FASE III
   cout << "a + b: ";
   a.add(b).write();
   
   cout << "b - a: ";
   b.substract(a).write();
 
   cout << "a * b: ";
   a.multiply(b).write();
   
   cout << "a / b: ";
   a.divide(b).write();
 
   // Same results but different methods.
   cout << "a^2 (option1): ";
   a.squareOpt1(a).write();
 
   cout << "a^2 (option2): ";
   a.squareOpt2(a).write();
 
   cout << "c^2 (option1): ";
   c.squareOpt1(c).write();
   
   return 0;
 }