#ifndef SPARSE_VECTORT_H_
#define SPARSE_VECTORT_H_

#include <iostream>
#include <math.h>  // fabs

#include "vector_t.h"
#include "pair_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t;
typedef vector_t<pair_double_t> pair_vector_t;

class sparse_vector_t {
 public:
  // -- Constructors --
  
  sparse_vector_t(const int = 0);
  sparse_vector_t(const vector_t<double>&,
                 const double = EPS); // standard constructor
  sparse_vector_t(const sparse_vector_t&);  // copy constructor

  // -- Assignment operator --
  
  sparse_vector_t& operator=(const sparse_vector_t&);

  // -- Destructor --
  
  ~sparse_vector_t();
  
  // -- Getters --
  
  int get_nz(void) const;
  int get_n(void) const;

  // -- Getters & Setters --

  pair_double_t& at(const int);
  pair_double_t& operator[](const int);
  
  // -- Constant Getters --
  
  const pair_double_t& at(const int) const;
  const pair_double_t& operator[](const int) const;

  // -- I/O -- 

  void write(std::ostream& = std::cout) const;

 private:
  pair_vector_t pv_;  // values + indices
  int nz_;            // number of non-zero values = vector size
  int n_;             // size of original vector
};

bool IsNotZero(const double val, const double eps = EPS)
{
  return fabs(val) > eps;
}

sparse_vector_t::sparse_vector_t(const int n) : pv_(n), nz_(0), n_(n) {}


// 1st Attempt: Good! Oh crap, two passes...
sparse_vector_t::sparse_vector_t(const vector_t<double>& v, const double eps)
    : pv_(), nz_(0), n_(v.get_size())
{
  // First obvious step: scan the original vector to count
  // non-zero values to determine sparse vector size
  for (int i = 0; i < n_; i++)
  {
    if (IsNotZero(v.at(i), eps))
      nz_++;
  }

  pv_.resize(nz_);

  int j = 0;

  // Second pass: now that we have the sparse vector size,
  // we add the non-zero values at their corresponding positions
  for (int i = 0; i < n_; i++)
  {
    if (IsNotZero(v.at(i), eps))
    {
      pv_[j].set(v.at(i), i);
      j++;
    }
  }
}

// copy constructor
sparse_vector_t::sparse_vector_t(const sparse_vector_t& w) 
{
  *this = w;  // directly invokes assignment operator
}

// assignment operator
sparse_vector_t& sparse_vector_t::operator=(const sparse_vector_t& w)
{
  nz_ = w.get_nz();
  n_ = w.get_n();
  pv_ = w.pv_;

  return *this;
}

sparse_vector_t::~sparse_vector_t() {}

inline int sparse_vector_t::get_nz() const
{
  return nz_;
}

inline int sparse_vector_t::get_n() const
{
  return n_;
}

pair_double_t& sparse_vector_t::at(const int i)
{
  assert(i >= 0 && i < get_nz());
  return pv_[i];
}

pair_double_t& sparse_vector_t::operator[](const int i)
{
  return at(i);
}

const pair_double_t& sparse_vector_t::at(const int i) const
{
  assert(i >= 0 && i < get_nz());
  return pv_[i];
}

const pair_double_t& sparse_vector_t::operator[](const int i) const
{
  return at(i);
}

// I/O
void sparse_vector_t::write(std::ostream& os) const
{ 
  os << get_n() << "(" << get_nz() << "): [ ";
  
  for (int i = 0; i < get_nz(); i++)
    os << pv_[i] << " ";
    
  os << "]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const sparse_vector_t& sv) {
  sv.write(os);
  return os;
}

#endif