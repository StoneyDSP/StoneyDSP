/*
  ==============================================================================

    AudioSample.h
    Created: 16 Jul 2022 12:58:03am
    Author:  Nathan J. Hood
    Website: github.com/StoneyDSP
    email:   nathanjhood@googlemail.com

  ==============================================================================
*/

#pragma once

template <typename SampleType>
class AudioSample
{
public:
    //==========================================================================
    /** Default Constructor. */
    AudioSample() : value()
    {} = default;

    /** Initialized Constructor. */
    AudioSample(Type initValue) : value(initValue)
    {}

    /** Copy Constructor. */
    AudioSample(const AudioSample& initValue) : value(initValue)
    {}

    /** Move Constructor. Value initialized via default constructor (C++11 only) */
    AudioSample(AudioSample&& initValue) noexcept : value() 
    {
        swap(*this, initValue); 
    }

    /** Deconstructor. */
    ~AudioSample()
    {}

    //==========================================================================
    /** Swap method. */
    void swap (AudioSample a, AudioSample b)
    {
        AudioSample c(a);
        a = b;
        b = c;
    }

    //==========================================================================
    /** Returns a reference to the current value. */
    AudioSample& get() const noexcept 
    { 
        return value; 
    }

    /** Returns *this. */
    AudioSample& operator() () 
    { 
        return *this; 
    }

    /** Changes the coefficient's current value. */
    AudioSample& operator() (SampleType newValue) 
    { 
        swap(*this, newValue); 
        return *this; 
    }

    //==========================================================================
    /** Changes the coefficient's current value. */
    AudioSample& operator= (SampleType newValue) const noexcept 
    { 
        swap(*this, newValue); 
        return *this; 
    }

    /** Adds a number to the current value, returning the new value. */
    AudioSample operator+ (const SampleType& amountToAdd) const noexcept 
    { 
        return *this + amountToAdd;
    }

    /** Adds a number to the current value, returning the new current value. */
    AudioSample& operator+= (const SampleType& amountToAdd) const noexcept 
    { 
        operator+(amountToAdd); 
        return *this;  
    }

    /** Subtracts a number from the current value, returning the new value. */
    AudioSample operator- (const SampleType& amountToSub) noexcept 
    { 
        return value - amountToSub; 
    }

    /** Subtracts a number from the current value, returning the new current value. */
    AudioSample& operator-= (const SampleType& amountToSub) const noexcept 
    { 
        operator-(amountToSub); 
        return *this; 
    }

    /** Multiplies the current value by a number, returning the new value. */
    AudioSample operator* (const SampleType& amountToMul) noexcept 
    { 
        return value * amountToMul; 
    }

    /** Multiplies the current value by a number, returning the new value. */
    AudioSample& operator*= (const SampleType& amountToMul) const noexcept 
    { 
        operator* (amountToMul); 
        return *this; 
    }

    /** Divides the current value by a number, returning the new value. */
    AudioSample operator/ (const SampleType& amountToDiv) noexcept 
    { 
        return value / amountToDiv; 
    }

    /** Divides the current value by a number, returning the new value. */
    AudioSample& operator/= (const SampleType& amountToDiv) noexcept 
    { 
        operator/ (amountToDiv); 
        return *this; 
    }

    /** Modulos the current value by a number, returning the new value. */
    AudioSample operator% (const SampleType& amountToMod) noexcept 
    { 
        return value % amountToMod; 
    }

    /** Modulos the current value by a number, returning the new value. */
    AudioSample& operator%= (const SampleType& amountToMod) noexcept 
    { 
        operator% (amountToMod);
        return *this; 
    }

    //==========================================================================
    /* Returns "true" if the current value is equal to another value. */
    bool operator==(const SampleType& valueToCompare) const noexcept 
    { 
        return *this == valueToCompare; 
    }

    /** Returns "true" if the current value is not equal to another value. */
    bool operator!=(const SampleType& valueToCompare) noexcept 
    { 
        return !operator==(valueToCompare); 
    }

    /** Returns "true" if the current value is less than another value. */
    bool operator< (const SampleType& valueToCompare) const noexcept 
    { 
        return *this < valueToCompare; 
    }

    /** Returns "true" if the current value is greater than another value. */
    bool operator> (const SampleType& valueToCompare) noexcept 
    { 
        return !operator<=(valueToCompare); 
    }

    /** Returns "true" if the current value is less than or equal to another value. */
    bool operator<=(const SampleType& valueToCompare) noexcept 
    { 
        return !operator>(valueToCompare); 
    }

    /** Returns "true" if the current value is greater than or equal to another value. */
    bool operator>=(const SampleType& valueToCompare) noexcept 
    { 
        return !operator<(valueToCompare); 
    }

private:
    //==========================================================================
    SampleType value;
};

template class AudioSample<float>;
template class AudioSample<double>;
