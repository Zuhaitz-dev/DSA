#ifndef SLLPOLYNOMIAL_H_
#define SLLPOLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "pair_t.h"
#include "sll_t.h"
#include "vector_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t;  // Pair double
typedef sll_node_t<pair_double_t> SllPolyNode;  // Sll node for polynomial



// Class for polynomials based on singly linked lists of pairs
class SllPolynomial : public sll_t<pair_double_t>
{
 public:
    // constructors
    SllPolynomial(void) : sll_t() {};
    SllPolynomial(const vector_t<double>&, const double = EPS);

    // destructor
    ~SllPolynomial() {};

    // I/O
    void Write(std::ostream& = std::cout) const;
  
    // operations
    double Eval(const double) const;
    bool IsEqual(const SllPolynomial&, const double = EPS) const;
    void Sum(const SllPolynomial&, SllPolynomial&, const double = EPS);

    // Extra modification
    double WeirdSum(const double c, const int i) const;
};



bool
IsNotZero(const double val, const double eps = EPS)
{
    return fabs(val) > eps;
}



// constructor
SllPolynomial::SllPolynomial(const vector_t<double>& v, const double eps)
{
    // If we use size_t, we will get this warning:

    // warning: narrowing conversion of ‘(& v)->vector_t<double>::get_size()’
    // from ‘int’ to ‘size_t’ {aka ‘long unsigned int’} [-Wnarrowing]
    for (int i{v.get_size() - 1}; i >= 0; --i)
    {
        if (IsNotZero(v[i], eps))
        {
            SllPolyNode* node = new SllPolyNode(pair_double_t(v[i], i));
            sll_t<pair_double_t>::push_front(node);
        }
    }
}



// I/O
void
SllPolynomial::Write(std::ostream& os) const
{
    os << "[ ";
    bool first{true};

    SllPolyNode* aux{get_head()};

    while (aux != NULL)
    {
        int inx{aux->get_data().get_inx()};
        double val{aux->get_data().get_val()};
    
        if (val > 0)
            os << (!first ? " + " : "") << val;
        else
            os << (!first ? " - " : "-") << fabs(val);

        os << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    
        if (inx > 1)
            os << inx;
    
        first = false;
        aux = aux->get_next();
    }
    
    os << " ]" << std::endl;
}



std::ostream&
operator<<(std::ostream& os, const SllPolynomial& p) {
    p.Write(os);
    return os;
}



// -- OPERATIONS WITH POLYNOMIALS --

// NOTE: Tested, works fine.
double
SllPolynomial::Eval(const double x) const {
    double result{0.0};
    SllPolyNode* aux{get_head()};

    while (aux != NULL)
    {
        int inx{aux->get_data().get_inx()};
        double val{aux->get_data().get_val()};

        result += val * pow(x, inx);

        aux = aux->get_next();
    }
  
    return result;
}



// Compare two polynomials
bool
SllPolynomial::IsEqual(const SllPolynomial& sllpol, const double eps) const
{
    bool differents = false;
    
    SllPolyNode* aux1{get_head()};
    SllPolyNode* aux2{sllpol.get_head()};

    while (aux1 != NULL && aux2 != NULL)
    {
        // Let's get the exponents
        int inx1{aux1->get_data().get_inx()};
        int inx2{aux2->get_data().get_inx()};

        if (inx1 != inx2)
            return differents;
        
        // Now let's check the coefficients
        double val1{aux1->get_data().get_val()};
        double val2{aux2->get_data().get_val()};

        if (fabs(val1 - val2) > eps)
            return differents;

        // Let's move to the next one
        aux1 = aux1->get_next();
        aux2 = aux2->get_next();
    }

    return !differents;
}



// Generate a new polynomial that is the sum of two polynomials
void
SllPolynomial::Sum(const SllPolynomial& sllpol, SllPolynomial& sllpolsum, const double eps)
{
    SllPolyNode* aux1{get_head()};
    SllPolyNode* aux2{sllpol.get_head()};
    SllPolyNode* nodeSum{};

    while (aux1 != nullptr && aux2 != nullptr)
    {
        int inx1{aux1->get_data().get_inx()};
        int inx2{aux2->get_data().get_inx()};

        double val1{aux1->get_data().get_val()};
        double val2{aux2->get_data().get_val()};

        if (inx1 == inx2)
        {
            double sumVal = val1 + val2;
            if (fabs(sumVal) > eps)
            {
                nodeSum = new SllPolyNode(pair_double_t(sumVal, inx1));
                sllpolsum.push_front(nodeSum);
            }
            aux1 = aux1->get_next();
            aux2 = aux2->get_next();
        }
        else if (inx1 > inx2)
        {
            nodeSum = new SllPolyNode(pair_double_t(val2, inx2));
            sllpolsum.push_front(nodeSum);
            aux2 = aux2->get_next();
        }
        else  // inx1 < inx2
        {
            nodeSum = new SllPolyNode(pair_double_t(val1, inx1));
            sllpolsum.push_front(nodeSum);
            aux1 = aux1->get_next();
        }
    }

    // **Append** the remaining nodes from aux1
    while (aux1 != nullptr)
    {
        int inx1{aux1->get_data().get_inx()};
        double val1{aux1->get_data().get_val()};
        nodeSum = new SllPolyNode(pair_double_t(val1, inx1));
        sllpolsum.push_front(nodeSum);
        aux1 = aux1->get_next();
    }

    // **Append** the remaining nodes from aux2
    while (aux2 != nullptr)
    {
        int inx2{aux2->get_data().get_inx()};
        double val2{aux2->get_data().get_val()};
        nodeSum = new SllPolyNode(pair_double_t(val2, inx2));
        sllpolsum.push_front(nodeSum);
        aux2 = aux2->get_next();
    }
}



// Extra modification
// This function is similar to the Eval function, but
// it only sums the monomials with a coefficient greater than c
// and an exponent less than or equal to i
double  SllPolynomial::WeirdSum(const double c, const int i) const
{
    double result{0.0};
    SllPolyNode* aux{get_head()};

    while (aux != NULL)
    {
        int inx {aux->get_data().get_inx()};
        double val{aux->get_data().get_val()};

        if (inx <= i && val > c)
        {
            result += val;
            // Could be another way to do it, depends on the criteria 
            //result += pow(val, inx);
        }
        else if (inx > i)
        {
            break;
        }

        aux = aux->get_next();
    }

    return result;
}



#endif  // SLLPOLYNOMIAL_H_
