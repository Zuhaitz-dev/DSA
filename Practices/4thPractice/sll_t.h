#ifndef SLLT_H_
#define SLLT_H_

#include <iostream>
#include <cassert>

#include "sll_node_t.h"



// Class for a singly linked list
// Because it is a template class, we can work with any datatype
template <class T> class sll_t
{
 public:
    // constructor
    sll_t(void) : head_(NULL) {}

    // destructor
    ~sll_t(void);

    // getters
    sll_node_t<T>* get_head(void) const { return head_; };
  
    bool empty(void) const;

    // operations
    void push_front(sll_node_t<T>*);
    sll_node_t<T>* pop_front(void);

    void insert_after(sll_node_t<T>*, sll_node_t<T>*);
    sll_node_t<T>* erase_after(sll_node_t<T>*);

    sll_node_t<T>* search(const T&) const;

    // I/O
    std::ostream& write(std::ostream& = std::cout) const;

 private:
    sll_node_t<T>* head_;
};



// destructor
template <class T>
sll_t<T>::~sll_t(void)
{
    while (!empty())
    {
        sll_node_t<T>* aux = head_;
        head_ = head_->get_next();
        delete aux;
    }
}



// Check if the list is empty
template <class T> bool
sll_t<T>::empty(void) const
{
  return head_ == NULL;
}

// -- OPERATIONS --

template <class T> void
sll_t<T>::push_front(sll_node_t<T>* n)
{
    assert(n != NULL);

    n->set_next(head_);
    head_ = n;
}



template <class T> sll_node_t<T>*
sll_t<T>::pop_front(void)
{ 
    assert(!empty());
    sll_node_t<T>* aux = head_;
    head_ = head_->get_next();
    aux->set_next(NULL);

    return aux;
}



template <class T> void
sll_t<T>::insert_after(sll_node_t<T>* prev, sll_node_t<T>* n)
{
    assert(prev != NULL && n != NULL);

    n->set_next(prev->get_next());
    prev->set_next(n);
}



template <class T>
sll_node_t<T>* sll_t<T>::erase_after(sll_node_t<T>* prev)
{ 
    assert(!empty());
    assert(prev != NULL);
    sll_node_t<T>* aux = prev->get_next();
  
    assert(aux != NULL);
    prev->set_next(aux->get_next());
    aux->set_next(NULL);

    return aux;
}



template <class T> sll_node_t<T>*
sll_t<T>::search(const T& d) const
{
    sll_node_t<T>* aux = head_;
    
    while ((aux != NULL) && (aux->get_data() != d))
        aux = aux->get_next();
    
    return aux;
}

// I/O
template <class T>
std::ostream& sll_t<T>::write(std::ostream& os) const
{
    sll_node_t<T>* aux = head_;

    while (aux != NULL)
    {
        aux->write(os);
        aux = aux->get_next();
    }
  
    return os;
}



#endif  // SLLT_H_
