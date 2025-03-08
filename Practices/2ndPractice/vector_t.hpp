/**
 * @file vector_t.hpp
 * @brief This file defines the vector_t template class for representing and manipulating dynamic arrays.
 *
 * The vector_t class provides functionality for resizing, accessing elements, and performing input/output
 * operations on a dynamic array. It also includes a specialized function for calculating the scalar product
 * of two vectors, with a specific implementation for vectors of rational numbers.
 */

 #pragma once

 #include <iostream>
 #include <cassert>
 
 using namespace std;
 
 template<class T>
 class vector_t
 {
  public:
   // Constructor and destructor.
   vector_t(const int = 0);
   vector_t(const vector_t<T>& other);
   vector_t<T>& operator=(const vector_t<T>& other);
   ~vector_t();
 
   // Method to resize the vector.
   void resize(const int);
 
   // Getter methods to access elements and size.
   T get_val(const int) const;
   int get_size(void) const;
 
   // Setter method to modify elements.
   void set_val(const int, const T);
 
   // Element access with index validation.
   T& at(const int);
   T& operator[](const int);
 
   // Const versions for safe element access.
   const T& at(const int) const;
   const T& operator[](const int) const;
 
   // Input/output methods: write and read the vector.
   void write(ostream& = cout) const;
   void read(istream& = cin);
 
  private:
   T *v_;  // Pointer to the dynamic array.
   int sz_;  // Size of the vector.
 
   // Internal methods for construction and destruction of the vector.
   void build(void);
   void destroy(void);
 };
 
 // Implementation of the vector_t class.
 
 // Constructor with size parameter.
 template<class T>
 vector_t<T>::vector_t(const int n)
 { 
   sz_ = n;
   build();
 }
 


 // Copy constructor.
 template<class T>
 vector_t<T>::vector_t(const vector_t<T>& other)
   : sz_(other.sz_), v_(other.sz_ ? new T[other.sz_] : nullptr)
 {
   for (int i = 0; i < sz_; ++i)
     v_[i] = other.v_[i];
 }
 


 // Assignment operator.
 template<class T>
 vector_t<T>& vector_t<T>::operator=(const vector_t<T>& other)
 {
   if (this != &other) {
     delete [] v_;
     sz_ = other.sz_;
     v_ = (sz_ ? new T[sz_] : nullptr);
     for (int i = 0; i < sz_; ++i)
       v_[i] = other.v_[i];
   }
   return *this;
 }

 

 // Destructor.
 template<class T>
 vector_t<T>::~vector_t()
 {
   destroy();
 }
 


 // Internal method to build the vector.
 template<class T>
 void
 vector_t<T>::build()
 {
   v_ = NULL;
   if (sz_ != 0) {
     v_ = new T[sz_];
     assert(v_ != NULL);
   }
 }
 


 // Internal method to destroy the vector.
 template<class T>
 void
 vector_t<T>::destroy()
 {
   if (v_ != NULL) {
     delete[] v_;
     v_ = NULL;
   }
   sz_ = 0;
 }
 


 // Method to resize the vector.
 template<class T>
 void
 vector_t<T>::resize(const int n)
 {
   destroy();
   sz_ = n;
   build();
 }
 


 // Getter method to access an element by index.
 template<class T>
 inline
 T
 vector_t<T>::get_val(const int i) const
 {
   assert(i >= 0 && i < get_size());
   return v_[i];
 }
 


 // Getter method to access the size of the vector.
 template<class T>
 inline
 int
 vector_t<T>::get_size() const
 {
   return sz_;
 }
 


 // Setter method to modify an element by index.
 template<class T>
 void
 vector_t<T>::set_val(const int i, const T d)
 {
   assert(i >= 0 && i < get_size());
   v_[i] = d;
 }
 


 // Element access with index validation.
 template<class T>
 T&
 vector_t<T>::at(const int i)
 {
   assert(i >= 0 && i < get_size());
   return v_[i];
 }
 


 // Overloaded operator for element access.
 template<class T>
 T&
 vector_t<T>::operator[](const int i)
 {
   return at(i);
 }
 


 // Const version of element access with index validation.
 template<class T>
 const T&
 vector_t<T>::at(const int i) const
 {
   assert(i >= 0 && i < get_size());
   return v_[i];
 }
 


 // Const version of overloaded operator for element access.
 template<class T>
 const T&
 vector_t<T>::operator[](const int i) const
 {
   return at(i);
 }
 


 // Method to write the vector to an output stream.
 template<class T>
 void
 vector_t<T>::write(ostream& os) const
 { 
   os << get_size() << ":\t";
   for (int i = 0; i < get_size(); i++)
     os << at(i) << "\t";
   os << endl;
 }
 


 // Method to read the vector from an input stream.
 template<class T>
 void
 vector_t<T>::read(istream& is)
 {
   is >> sz_;
   resize(sz_);
   for (int i = 0; i < sz_; ++i)
     is >> at(i);
 }
 


 // Functions for scalar product.

 // Generic version for any type T.
 template<class T>
 T
 scal_prod(const vector_t<T>& v, const vector_t<T>& w)
 {
   assert(v.get_size() == w.get_size());
   T result = v.get_val(0) * w.get_val(0);
   for (int i = 1; i < v.get_size(); ++i)
   {
     result = result + (v.get_val(i) * w.get_val(i));
   }
   return result;
 }
 


 // Specialized version for vector_t<rational_t> that uses value() for conversion.
 double
 scal_prod(const vector_t<rational_t>& v, const vector_t<rational_t>& w)
 {
   assert(v.get_size() == w.get_size());
   double result = v.get_val(0).value() * w.get_val(0).value();
   for (int i = 1; i < v.get_size(); ++i)
   {
     result = result + (v.get_val(i).value() * w.get_val(i).value());
   }
   return result;
 }