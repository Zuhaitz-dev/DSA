#ifndef PAIRT_H_
#define PAIRT_H_

#include <iostream>

// Definition of the pair_t class template
template<class T> 
class pair_t
{
 public:
  // -- Constructors --
  
  // Default constructor: initializes 'val_' with T's default constructor and 'inx_' to -1
  pair_t(void); 
  // Parameterized constructor: initializes 'val_' with given value and 'inx_' with given integer
  pair_t(T, int);

  // -- Destructor --
  ~pair_t(void);

  // -- Getters & Setters --
  
  // Returns the stored value
  T get_val(void) const;
  // Returns the stored index
  int get_inx(void) const;
  // Sets both value and index
  void set(T, int);

  // -- I/O Methods --
  
  // Reads a pair from input stream (defaults to std::cin)
  std::istream& read(std::istream& is = std::cin);
  // Writes the formatted pair to output stream (defaults to std::cout)
  std::ostream& write(std::ostream& os = std::cout) const;

 private:
  T val_;     // Stores the value of type T
  int inx_;   // Stores the associated index
};

// Default constructor: initializes 'val_' using its default constructor and 'inx_' to -1
template<class T> 
pair_t<T>::pair_t() : val_(), inx_(-1) {}

// Parameterized constructor: initializes 'val_' and 'inx_' with given values
template<class T> 
pair_t<T>::pair_t(T val, int inx) : val_(val), inx_(inx) {}

// Destructor: no additional resource cleanup needed
template<class T> 
pair_t<T>::~pair_t() {}

// set method: updates the pair's value and index
template<class T> 
void pair_t<T>::set(T val, int inx) {
  val_ = val;
  inx_ = inx;
}

// get_inx method: returns the currently stored index
template<class T> 
int pair_t<T>::get_inx() const {
  return inx_;
}

// get_val method: returns the currently stored value
template<class T> 
T pair_t<T>::get_val() const {
  return val_;
}

// read method: reads from input stream first the integer (index) then the value
template<class T> 
std::istream& pair_t<T>::read(std::istream& is) {
  return is >> inx_ >> val_;
}

// write method: writes the pair in the format (index:value)
template<class T> 
std::ostream& pair_t<T>::write(std::ostream& os) const {
  return os << "(" << inx_ << ":" << val_ << ")";
}

// Overload of << operator to allow direct output of pair_t
template<class T> 
std::ostream& operator<<(std::ostream& os, const pair_t<T>& p) {
  p.write(os);  // Calls write to format the output
  return os;
}

#endif