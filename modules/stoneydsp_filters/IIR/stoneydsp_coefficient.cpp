/*
  ==============================================================================

    Coefficient.cpp
    Created: 6 Jul 2022 12:58:03am
    Author:  Nathan J. Hood
    Website: github.com/StoneyDSP
    email:   nathanjhood@googlemail.com

  ==============================================================================
*/

namespace stoneydsp
{
namespace filters
{

template <typename SampleType>
Coefficient<SampleType>::Coefficient(SampleType init) : value(init)
{
}

template <typename SampleType>
Coefficient<SampleType>::Coefficient(const Coefficient& other) : value(other.get())
{
}

template <typename SampleType>
Coefficient<SampleType>::~Coefficient()
{
    static_assert (std::atomic<SampleType>::is_always_lock_free,
        "This class can only be used for lock-free types");
}

template <typename SampleType>
SampleType Coefficient<SampleType>::getValue() const
{ 
    return value;
}

template <typename SampleType>
void Coefficient<SampleType>::setValue(SampleType newValue)
{ 
    value = newValue; 
    valueChanged(get()); 
}

template <typename SampleType>
void Coefficient<SampleType>::valueChanged(SampleType) 
{
}

template <typename SampleType>
Coefficient<SampleType>& Coefficient<SampleType>::operator= (SampleType newValue)
{
    if (value != newValue)
        setValue(newValue);

    return *this;
}

template class Coefficient<float>;
template class Coefficient<double>;

} //namespace filters
} //namespace stoneydsp
