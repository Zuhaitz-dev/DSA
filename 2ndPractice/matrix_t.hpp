/**
 * @file matrix_t.hpp
 * @brief This file defines the matrix_t template class for representing and manipulating matrices.
 *
 * The matrix_t class provides functionality for matrix operations such as resizing, element access,
 * matrix multiplication, and input/output operations. It also includes a method to extract the
 * diagonal elements of a square matrix. The class uses a linear vector to store matrix elements
 * in row-major order.
 */

#pragma once

#include <iostream>
#include <cassert>
#include "vector_t.hpp"

using namespace std;

template<class T>
class matrix_t
{
 public:
  // Constructor and destructor.
  matrix_t(const int = 0, const int = 0);
  ~matrix_t();
  
  // Method to resize the matrix.
  void resize(const int, const int);
  
  // Getters for the number of rows (m) and columns (n).
  int get_m(void) const;
  int get_n(void) const;
  
  // Element access with index validation.
  T& at(const int, const int);
  T& operator()(const int, const int);
  
  // Const versions for element access.
  const T& at(const int, const int) const;
  const T& operator()(const int, const int) const;
  
  // Matrix multiplication operation.
  void multiply(const matrix_t<T>&, const matrix_t<T>&);
  
  // Methods for writing and reading matrices.
  void write(ostream& = cout) const;
  void read(istream& = cin);
  
  // Method to get the main diagonal of the matrix.
  vector_t<T> get_diagonal(void) const;

 private:
  int m_, n_;    // m_ = number of rows, n_ = number of columns.
  vector_t<T> v_;  // Stores all elements in a linear vector.
  
  // Internal function to calculate the linear position from indices (i, j).
  int pos(const int, const int) const;
};

// Constructor implementation.
template<class T>
matrix_t<T>::matrix_t(const int m, const int n)
{ 
  m_ = m;
  n_ = n;
  v_.resize(m_ * n_);
}



// Destructor implementation.
template<class T>
matrix_t<T>::~matrix_t()
{}



// Method to resize the matrix.
template<class T>
void
matrix_t<T>::resize(const int m, const int n)
{
  assert(m > 0 && n > 0); // Ensure dimensions are positive.
  m_ = m;
  n_ = n;
  v_.resize(m_ * n_);
}



// Getter for the number of rows (m).
template<class T>
inline
int
matrix_t<T>::get_m() const
{
  return m_;
}



// Getter for the number of columns (n).
template<class T>
inline
int
matrix_t<T>::get_n() const
{
  return n_;
}



// Element access with index validation.
template<class T>
T& 
matrix_t<T>::at(const int i, const int j)
{
  // Ensure indices are within valid range (rows and columns start at 1).
  assert(i > 0 && i <= get_m());
  assert(j > 0 && j <= get_n());
  return v_[pos(i, j)];
}



// Overloaded operator for element access.
template<class T>
T& 
matrix_t<T>::operator()(const int i, const int j)
{
  return at(i, j);
}



// Const version of element access with index validation.
template<class T>
const T& 
matrix_t<T>::at(const int i, const int j) const
{
  assert(i > 0 && i <= get_m());
  assert(j > 0 && j <= get_n());
  return v_[pos(i, j)];
}



// Const version of overloaded operator for element access.
template<class T>
const T& 
matrix_t<T>::operator()(const int i, const int j) const
{
  return at(i, j);
}



// Method to write the matrix to an output stream.
template<class T>
void 
matrix_t<T>::write(ostream& os) const
{ 
  // Write the dimensions and elements of the matrix in tabular format.
  os << get_m() << "x" << get_n() << endl;
  for (int i = 1; i <= get_m(); ++i) {
    for (int j = 1; j <= get_n(); ++j)
      os << at(i, j) << "\t";
    os << endl;
  }
  os << endl;
}



// Method to read the matrix from an input stream.
template<class T>
void 
matrix_t<T>::read(istream& is)
{
  // Read the dimensions and then all elements.
  is >> m_ >> n_;
  resize(m_, n_);
  for (int i = 1; i <= get_m(); ++i)
    for (int j = 1; j <= get_n(); ++j)
      is >> at(i, j);
}



// Internal function to calculate the linear position from indices (i, j).
template<class T>
inline 
int 
matrix_t<T>::pos(const int i, const int j) const
{
  // Convert the pair (i, j) into a linear position, assuming row-major order.
  assert(i > 0 && i <= get_m());
  assert(j > 0 && j <= get_n());
  return (i - 1) * get_n() + (j - 1);
}



// Matrix multiplication operation.
template<class T>
void
matrix_t<T>::multiply(const matrix_t<T>& A, const matrix_t<T>& B)
{
  // Ensure the number of columns in A equals the number of rows in B.
  assert(A.get_n() == B.get_m());
  int m = A.get_m();
  int n = A.get_n(); // Also equal to B.get_m()
  int p = B.get_n();
  // Resize the result matrix.
  resize(m, p);
  // Multiply A and B using the operations =, +, and *.
  for (int i = 1; i <= m; ++i)
  {
    for (int j = 1; j <= p; ++j)
    {
      T sum = A(i, 1) * B(1, j);
      for (int k = 2; k <= n; ++k)
      {
        sum = sum + (A(i, k) * B(k, j));
      }
      at(i, j) = sum;
    }
  }
}



// Method to get the main diagonal of the matrix.
template<class T>
vector_t<T> 
matrix_t<T>::get_diagonal(void) const
{
  // Ensure the matrix is square.
  assert(get_m() == get_n());
  int diagonal_size = (get_m() < get_n()) ? get_m() : get_n();
  vector_t<T> diag(diagonal_size); // Vector of size equal to the minimum of m and n.
  for (int i = 1; i <= diagonal_size; ++i)
  {
    // Since the diagonal starts at 1, access with at(i, i).
    // But since the vector starts at 0, subtract 1.
    diag[i - 1] = at(i, i);
  }
  return diag;
}