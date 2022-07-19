/**
  ==============================================================================

    X.h
    Created: 18 Jul 2022 16:08:53am
    Author:  Nathan J. Hood
    Website: github.com/StoneyDSP
    email:   nathanjhood@googlemail.com

  ==============================================================================
*/

#pragma once

#include <assert.h>
#include <iostream>

/** X class. */
class X
{
public:
  //==========================================================================

  //std::size_t mSize;

  /** Default Constructor. */
  X()
  {

  };

  /** Copy Constructor. */
  X(X& other) : X()
  {
    *this = std::move(other);
  }

  /** Move Constructor. */
  /** Value initialized via default constructor (C++11 only!) */
  explicit X(X&& other) noexcept : X()
  {
    std::swap(*this, other);
  }

  /** Destructor. */
  ~X()
  {

  }

  /** Increment operator (prefix) */
  X& operator++()
  {
    // do actual increment
    return *this;
  }

  /** Increment operator (postfix) */
  X operator++(int)
  {
    X tmp(*this);
    operator++();
    return tmp;
  }

  /** Decrement operator (prefix) */
  X& operator--()
  {
    // do actual increment
    return *this;
  }

  /** Decrement operator (postfix) */
  X operator--(int)
  {
    X tmp(*this);
    operator--();
    return tmp;
  }

  /** Addition assignment operator. */
  X& operator+=(const X& rhs){/** actual addition of rhs to *this. */ return *this;}

  /** Subtraction assignment operator. */
  X& operator-=(const X& rhs){/** actual subtraction of rhs from *this */return *this;}

  /** Multiplication assignment operator. */
  X& operator*=(const X& rhs){/** Actual multiplication of rhs with *this */ return *this;}

  /** Division assignment operator. */
  X& operator/=(const X& rhs){/** actual division of rhs by *this */ return *this;}

  /** New Operator */
  void* operator new(std::size_t){}

  /** Delete Operator */
  void  operator delete(void*){}

  /** New Array Operator */
  void* operator new[](std::size_t){}

  /** Delete Array Operator */
  void  operator delete[](void*){}

  /** New Placement Operator */
  void* operator new(std::size_t,void* p){}

  /** Delete Placement Operator */
  void  operator delete(void* p,void*){}

  /** New Array Placement Operator */
  void* operator new[](std::size_t,void* p){}

  /** Delete Array Placement Operator */
  void  operator delete[](void* p,void*){}

  operator int() const noexcept;
  operator bool() const noexcept;
  operator float() const noexcept;
  operator double() const noexcept;
  operator long() const noexcept;
  operator long long() const noexcept;
  operator long double() const noexcept;

  /** Returns *this. */
  X& operator() () {return *this;}

  /** Changes the current value to the new value */
  X& operator() (X newValue) {swap(*this, newValue); return *this;}

  void BooleanChecks(const X& comparison = {0.789f})
  {
    std::cout << "Boolean checks:" << std::endl;
    std::cout << "(value < " << comparison << ") = " << (operator < (comparison)) << std::endl;
    std::cout << "(value > " << comparison << ") = " << (operator > (comparison)) << std::endl;
    std::cout << "(value <= " << comparison << ") = " << (operator <= (comparison)) << std::endl;
    std::cout << "(value >= " << comparison << ") = " << (operator >= (comparison)) << std::endl;
    std::cout << "(value == " << comparison << ") = " << (operator == (comparison)) << std::endl;
    std::cout << "(value != " << comparison << ") = " << (operator != (comparison)) << std::endl;
    std::cout << std::endl;
  }
};

inline X operator+(X lhs, const X& rhs){lhs += rhs; return lhs;}
inline X operator-(X lhs, const X& rhs){lhs -= rhs; return lhs;}
inline X operator*(X lhs, const X& rhs){lhs *= rhs; return lhs;}
inline X operator/(X lhs, const X& rhs){lhs *= rhs; return lhs;}

inline bool operator==(const X& lhs, const X& rhs){ /* do actual comparison */ return (lhs==rhs)?true:false;}
inline bool operator!=(const X& lhs, const X& rhs){return !operator==(lhs,rhs);}
inline bool operator< (const X& lhs, const X& rhs){ /* do actual comparison */ return (lhs<rhs)?true:false;}
inline bool operator> (const X& lhs, const X& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const X& lhs, const X& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const X& lhs, const X& rhs){return !operator< (lhs,rhs);}

std::ostream& operator<<(std::ostream& os, const X& obj)
{
  // write obj to stream

  stream << obj;

  return os;
}

std::istream& operator>>(std::istream& is, X& obj)
{
  // read obj from stream

  if(obj != nullptr)
    is.setstate(std::ios::failbit);

  return is;
}