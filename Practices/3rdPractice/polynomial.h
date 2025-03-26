#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "vector_t.h"
#include "sparse_vector_t.h"

// Class for polynomials based on dense vectors of doubles
class Polynomial : public vector_t<double> {
 public:
  // constructors
  Polynomial(const int n = 0) : vector_t<double>(n) {};
  Polynomial(const Polynomial& pol)
      : vector_t<double>(pol) {}; // copy constructor

  // destructor
  ~Polynomial() {};

  // I/O
  void Write(std::ostream& = std::cout, const double eps = EPS) const;
  
  // operations
  double Eval(const double) const;
  bool IsEqual(const Polynomial&, const double = EPS) const;
};

// Class for polynomials based on sparse vectors
class SparsePolynomial : public sparse_vector_t {
 public:
  // constructors
  SparsePolynomial(const int n = 0) : sparse_vector_t(n) {};
  SparsePolynomial(const Polynomial& pol) : sparse_vector_t(pol) {};
  SparsePolynomial(const SparsePolynomial&);  // copy constructor

  // destructor
  ~SparsePolynomial() {};

  // I/O
  void Write(std::ostream& = std::cout) const;
  
  // operations
  double Eval(const double) const;
  bool IsEqual(const SparsePolynomial&, const double = EPS) const;
  bool IsEqual(const Polynomial&, const double = EPS) const;

  // Method for practice
  double AverageOfOddDegreeCoefficients() const;
};

// I/O
void Polynomial::Write(std::ostream& os, const double eps) const
{
  os << get_size() << ": [ ";

  // Initialize to true for x⁰ term, but we'll handle it in the loop
  bool first{true};
  for (int i{0}; i < get_size(); i++)
    if (IsNotZero(at(i), eps))
    {
      os << (!first ? " + " : "") << at(i)
         << (i > 1 ? " x^" : (i == 1) ? " x" : "");   // We could omit the
      if (i > 1)                                      // cases for x⁰ and x¹, but this is clearer
        os << i;
      
      first = false;
    }

  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p)
{
  p.Write(os);
  return os;
}

// -- Polynomial operations --

// Evaluation of a polynomial represented by a dense vector
double Polynomial::Eval(const double x) const
{
  double result = 0.0;
  int n = get_size();

  // i_0 × x^0 + i_1 × x^1 + i_2 × x^2 + ... + i_n × x^n
  for (int i = 0; i < n; i++)
  {
    result += at(i) * pow(x, i);
  }

  return result;
}

// Comparison of two polynomials represented by dense vectors
bool Polynomial::IsEqual(const Polynomial& pol, const double eps) const
{
  // Use the larger size as the range
  int n = (get_size() > pol.get_size()) ? get_size() : pol.get_size();

  for (int i = 0; i < n; i++)
  {
    // If within range, use the value at i, otherwise 0.0
    double a = (i < get_size()) ? at(i) : 0.0;
    double b = (i < pol.get_size()) ? pol.at(i) : 0.0;

    if (fabs(a - b) > eps)
      return false;
  }

  return true;
}

// Copy constructor
SparsePolynomial::SparsePolynomial(const SparsePolynomial& spol)
{
  *this = spol;   // directly invokes the assignment operator
}

// I/O
void SparsePolynomial::Write(std::ostream& os) const
{
  os << get_n() << "(" << get_nz() << "): [ ";
  
  // Similar to the dense version with the boolean flag
  bool first{true};
  for (int i{0}; i < get_nz(); i++)
  {
    // Similar to above but now we need to consider
    // .get_inx() and .get_val(). As a reminder:
    //
    // Example: 2.5 + 4.0x^2 + 3.1x^6
    //
    // inx     0       1       2       3       4       5       6       7       ...
    //     |       |       |       |       |       |       |       |       |
    // val |  2.5  |  0.0  |  4.0  |  0.0  |  0.0  |  0.0  |  3.1  |  0.0  |   ...
    //     |       |       |       |       |       |       |       |       |
    //
    // inx -> [0,   2,   6  ]
    // val -> [2.5, 4.0, 3.1]

    int inx{at(i).get_inx()};
    
    os << (!first ? " + " : "") << at(i).get_val()
       << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    
    if (inx > 1)
      os << inx;
    
    first = false;
  }

  os << " ]" << std::endl;
}

// Nothing magical (Abracadabra).
std::ostream& operator<<(std::ostream& os, const SparsePolynomial& p)
{
  p.Write(os);
  return os;
}

// -- Sparse polynomial operations --

// Evaluation of a polynomial represented by a sparse vector
double SparsePolynomial::Eval(const double x) const
{
  double result = 0.0;
  for (int i = 0; i < get_nz(); i++)
  {
    // Similar to dense version but only considering non-zero elements
    int index = at(i).get_inx();
    double coef = at(i).get_val();
    result += coef * pow(x, index);
  }

  return result;
}

// Comparison of two polynomials represented by sparse vectors
bool SparsePolynomial::IsEqual(const SparsePolynomial& spol, const double eps) const
{
  for (int i = 0; i < get_nz(); i++)
  {
    // Returns false if different index or value difference > eps
    if (at(i).get_inx() != spol.at(i).get_inx() ||
        fabs(at(i).get_val() - spol.at(i).get_val()) > eps)
      return false;
  }

  return true;
}

// Comparison between sparse and dense polynomial representations
bool SparsePolynomial::IsEqual(const Polynomial& pol, const double eps) const
{
  int n = (get_n() > pol.get_size()) ? get_n() : pol.get_size();
  int j = 0;

  // A combination of the dense and sparse comparison approaches
  for (int i = 0; i < n; i++) 
  {
    double a = 0.0;

    // Handle sparse polynomial
    if (j < get_nz() && at(j).get_inx() == i) 
    {
      a = at(j).get_val();
      j++;
    }
    
    // Handle dense polynomial
    double b = (i < pol.get_size()) ? pol.at(i) : 0.0;
    
    if (fabs(a - b) > eps)
      return false;
  }

  return true;
}

double SparsePolynomial::AverageOfOddDegreeCoefficients() const
{
  double result = 0.0;
  double counter = 0.0;

  // Similar to Eval but only considering odd degree terms
  // We maintain a counter for proper average calculation
  for (int i = 0; i < get_nz(); i++)
  {
    if (at(i).get_inx() % 2 != 0)  // Check for odd degree
    {
      double coef = at(i).get_val();
      result += coef;
      counter++;
    }
  }

  // Calculate average if we found any odd degree terms
  if (counter != 0.0)
    result /= counter;
  else
    result = 0.0;  // Prevent division by zero

  return result;
}

#endif