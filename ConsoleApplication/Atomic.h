
#pragma once

#ifndef ATOMIC_H_INCLUDED
#define ATOMIC_H_INCLUDED

#include <atomic>
#include <iostream>

class Atomic
{
public:
    /** Default constructor. */
    Atomic() : value() {}
    /** Initialized constructor. */
    Atomic(float initialValue) {}
    /** Copy constructor. */
    Atomic(Atomic& initialValue) {}
    /** Move constructor. */
    Atomic(Atomic&& initialValue) {}
    /** Destructor. */
    ~Atomic() {}

    // /** Increment operator (prefix) */
    // Atomic& operator++() { return *this; }
    // /** Decrement operator (prefix) */
    // Atomic& operator--() { return *this; }
    // /** Increment operator (postfix) */
    // Atomic operator++(int) { Atomic tmp (value); operator++(); return tmp; }
    // /** Decrement operator (postfix) */
    // Atomic operator--(int) { Atomic tmp (value); operator--(); return tmp; }

    /** Addition assignment operator. */ 
    Atomic& operator+=(const Atomic& rhs) { return *this; }
    /** Subtraction assignment operator. */
    Atomic& operator-=(const Atomic& rhs) { return *this; }
    /** Multiplication assignment operator. */
    Atomic& operator*=(const Atomic& rhs) { return *this; }
    /** Division assignment operator. */
    Atomic& operator/=(const Atomic& rhs) { return *this; }

    friend std::ostream& operator<<(std::ostream& ostream, Atomic& source);
    friend std::istream& operator>>(std::istream& istream, Atomic& source);

private:
    std::atomic<float> value;
};

inline Atomic operator+(Atomic lhs, const Atomic& rhs){lhs += rhs; return lhs;}
inline Atomic operator-(Atomic lhs, const Atomic& rhs){lhs -= rhs; return lhs;}
inline Atomic operator*(Atomic lhs, const Atomic& rhs){lhs *= rhs; return lhs;}
inline Atomic operator/(Atomic lhs, const Atomic& rhs){lhs *= rhs; return lhs;}

inline bool operator==(const Atomic& lhs, const Atomic& rhs){return(lhs==rhs)?true:false;}
inline bool operator!=(const Atomic& lhs, const Atomic& rhs){return !operator==(lhs,rhs);}
inline bool operator< (const Atomic& lhs, const Atomic& rhs){return (lhs<rhs)?true:false;}
inline bool operator> (const Atomic& lhs, const Atomic& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const Atomic& lhs, const Atomic& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const Atomic& lhs, const Atomic& rhs){return !operator< (lhs,rhs);}


//==============================================================================
std::ostream& operator<<(std::ostream& ostream, Atomic& source)
{
    ostream << source.value;

    return ostream;
}

std::istream& operator>>(std::istream& istream, Atomic& source)
{
  if(source.value)
    istream.setstate(std::ios::failbit);

  return istream;
}

#endif // ATOMIC_H_INCLUDED
