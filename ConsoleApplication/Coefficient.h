/**
  ==============================================================================

    coefficient.h
    Created: 18 Jul 2022 18:42:29pm
    Author:  Nathan J. Hood
    Website: github.com/StoneyDSP
    email:   nathanjhood@googlemail.com

  ==============================================================================
*/

#pragma once

#include <assert.h>
#include <atomic>
#include <iostream>

template <typename Type>
class Coefficient
{
    Coefficient() : value() 
    {
        std::cout << "Called Default Constructor!" << std::endl;
        std::cout << std::endl;
    }

    /** Destructor. */
    ~Coefficient()
    {
        std::cout << "Destroyed!" << std::endl;
        std::cout << std::endl;
    }

    std::atomic<Type> value;
};

//==============================================================================
template<typename Type>
std::ostream& operator<<(std::ostream& ostream, Coefficient<Type>& value)
{
    ostream << value.value;

    return ostream;
}

template<typename Type>
std::istream& operator>>(std::istream& istream, Coefficient<Type>& value)
{
  if(value.value != nullptr)
    istream.setstate(std::ios::failbit);

  return istream;
}

template class Coefficient<float>;
template class Coefficient<double>;
