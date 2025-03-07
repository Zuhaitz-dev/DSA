/**
 * @file main.cpp
 * @brief This file demonstrates the usage of the rational_t, vector_t, and matrix_t classes.
 *
 * The program performs arithmetic operations on rational numbers, calculates the scalar product of vectors,
 * and multiplies matrices. It also includes functionality to extract the diagonal of a matrix.
 */

 #include <iostream>
 #include <cmath>
 
 // Include necessary header files, grouped and separated.
 #include "rational_t.hpp"
 #include "vector_t.hpp"
 #include "matrix_t.hpp"
 
 using namespace std;
 
 int main()
 {
   // Create two objects of the rational_t class for FASE I operations.
   rational_t a(1, 2), b(3);
 
   // FASE I: Arithmetic operations with rational objects.
   cout << "a + b: ";
   (a + b).write();
   
   cout << "b - a: ";
   (b - a).write();
   
   cout << "a * b: ";
   (a * b).write();
   
   cout << "a / b: ";
   (a / b).write();
   
   cout << endl;
   
   // FASE II: Reading and using vectors, and calculating the scalar product.
   
   // Work with vectors of double.
   // Read the size and elements of vector v.
   vector_t<double> v, w;
   v.read();
   // Display the contents of vector v.
   v.write();
   
   // Read and display vector w.
   w.read();
   w.write();
   
   // Calculate and display the scalar product of vectors of double.
   cout << "Scalar product of vector_t<double>: " << scal_prod(v, w) << endl << endl;
   
   // Work with vectors of rational_t.
   vector_t<rational_t> x, y;
   // Read and display vectors x and y.
   x.read();
   x.write();
   
   y.read();
   y.write();
   
   // Calculate and display the scalar product for vectors of rational_t.
   cout << "Scalar product of vector_t<rational_t>: " << scal_prod(x, y) << endl << endl;
   
   // FASE III: Matrix multiplication.
   matrix_t<double> A, B, C;
   
   // Read and display matrices A and B.
   A.read();
   A.write();
   
   B.read();
   B.write();
   
   // Perform the multiplication of matrices A and B.
   C.multiply(A, B);
   cout << "Multiplication of matrices A and B: " << endl;
   C.write();
 
   // ---------------------------------------------------------//
 
   // Now test the new get_diagonal method.
   vector_t<double> d1;
   d1 = C.get_diagonal();
   cout << "Diagonal of matrix C:\n";
   d1.write();
 
   // Also with B:
   vector_t<double> d2;
   d2 = B.get_diagonal();
   cout << "Diagonal of matrix B:\n";
   d2.write();
 
   // ---------------------------------------------------------//
 
   return 0;
 }