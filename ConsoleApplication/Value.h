/**
  ==============================================================================

    Value.h
    Created: 16 Jul 2022 12:58:03am
    Author:  Nathan J. Hood
    Website: github.com/StoneyDSP
    email:   nathanjhood@googlemail.com

  ==============================================================================
*/

#pragma once

#include <assert.h>
#include <iostream>

// Issues...
// 1. Ambiguous Constructor calls [X]
// 2. Boolean operator method copying [X]
// 3. Implicit conversion to avoid code duplication

template <typename Type>
class Value final
{
public:
    //==========================================================================
    /** Default Constructor. */
    explicit Value() : value()
    {
        std::cout << "Called Default Constructor!" << std::endl;
        std::cout << std::endl;

        assertion(); 
    }

    /** Initialized Constructor. */
    explicit Value(Type value) : value(value)//, valRef(value)
    { 
        std::cout << "Called Initialized Constructor!" << std::endl;
        std::cout << std::endl;

        assertion(); 
    }

    /** Copy Constructor. */
    explicit Value(Type& value) : value(value)//, valRef(value)
    {
        std::cout << "Called Copy Constructor!" << std::endl;
        std::cout << std::endl;

        assertion(); 
    }

    /** Move Constructor. */
    /** Value initialized via default constructor (C++11 only!) */
    explicit Value(Value&& other) noexcept : value()//, valRef(value)
    { 
        std::cout << "Called Move Constructor!" << std::endl;
        std::cout << std::endl;

        //swap(*this, other);

        value = std::move (other.value);
        assertion();
    }

    /** Destructor. */
    ~Value() 
    {
        // valPtr = nullptr; 
        // assert(valPtr == nullptr); 
        // delete valPtr;

        std::cout << "Destroyed!" << std::endl;
        std::cout << std::endl;
    }

    //==========================================================================
    /** [Unified] Assignment operator. */
    Value& operator= (Value newValue) noexcept
    {
        std::cout << "Called function: Value& operator= (Value newValue) = " << newValue << std::endl;
        swap(*this, newValue);
        return *this; 
    }

    /** [Copy] Assignment operator. */
    Value& operator= (Type newValue) noexcept
    {
        std::cout << "Called function: Value& operator= (Type newValue) = " << std::endl;
        swap(*this, newValue);
        return *this; 
    }

    /** [Move] Assignment operator. */
    Value& operator= (Value&& other) noexcept
    {
        std::cout << "Called function: Value& operator= (Type newValue) = " << std::endl;
        value = std::move (other.value);
        return *this;
    }

    void assertion() 
    { 
        // assert(valPtr != nullptr);
        std::cout << "Passed assertion check!" << std::endl;
        std::cout << std::endl;
    }

    void info()
    {
        std::cout << "Value info:" << std::endl;
        std::cout << "value = " << *this << std::endl;
        std::cout << "&value = " << &(*this) << std::endl;
        std::cout << std::endl;
    }

    void dataChecks()
    {
        std::cout << "Data checks:" << std::endl;
        get();
        addressOf();
        sizeOf();
        std::cout << std::endl;
    }

    // operator int() const noexcept;
    // operator bool() const noexcept;
    // operator float() const noexcept;
    // operator double() const noexcept;


protected:
    //==========================================================================
    friend void swap(Value& first, Value& second) // nothrow
    {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.value, second.value);

        std::cout << "Called friend void swap; Swapped class for class!" << std::endl;
    }

    friend void swap(Value& first, Type& second) // nothrow
    {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.value, second);

        std::cout << "Called friend void swap; Swapped by members!" << std::endl;
    }

public:
    //==========================================================================
    /** Returns a reference to the current value. */
    Value& get() 
    {
        std::cout << "Called function: Value& get() = " << *this << std::endl;

        return *this; 
    }

    /** Returns a reference to the current value. */
    Value& me() & 
    { 
        return *this; 
    }
    
    Value& me() && = delete;

    /** Returns the address-of the current value. */
    Value* addressOf() 
    {
        std::cout << "Called function: Type* addressOf() = " << &(*this) << std::endl;
        return &(*this);
    }

    /** Returns the size of the current value. */
    int sizeOf() 
    {
        std::cout << "Called function: int sizeOf() = " << sizeof(*this) << std::endl;
        return sizeof(*this);
    }

    // /** Returns the current value. */
    // operator Type() const noexcept
    // { 
    //     return value; 
    // }

    /** Returns *this. */
    Value& operator() () 
    {
        std::cout << "Called function: Value& operator() () = " << *this << std::endl;
        return *this;
    }

    /** Changes the current value to the new value */
    Value& operator() (Value newValue) 
    {
        std::cout << "Called function: Value& operator() (Value newValue) = " << newValue << std::endl;
        swap(*this, newValue);
        return *this; 
    }

    /** Changes the current value to the new value */
    Value& operator() (Type newValue) 
    {
        std::cout << "Called function: Value& operator() (Type newValue) = " << newValue << std::endl;
        swap(*this, newValue);
        return *this;
    }

    // /** Addition assignment operator. */
    // Value& operator+=(const Value& rhs)
    // {
    //     // actual addition of rhs to *this

    //     *this += rhs;

    //     return *this;
    // }

    /** Addition assignment operator. */
    Value& operator+=(const Type& rhs)
    {
        // actual addition of rhs to *this
        
        value += rhs;
        
        std::cout << "Called function: inline Value<Type> operator+(const Value<Type>& lhs, const Type& rhs) = " << *this << std::endl;
        std::cout << std::endl;

        return *this;
    }

    // Value& operator+(const Type& rhs)
    // {
    //     return operator+=(rhs);
    // }

    //==========================================================================
    /** [EQ] Returns "true" if the current value is EQUAL TO another value. */
    bool operator==(const Type& rhs) const 
    {
        //std::cout << "Called function: bool operator==(const Type& rhs) const = " << rhs << std::endl;

        /* do actual comparison with *this */
        return (value == rhs) ? true : false;
    }

    /** [NE] Returns "true" if the current value is NOT EQUAL to another value. */
    bool operator!=(const Type& rhs) const 
    {
        //std::cout << "Called function: bool operator!=(const Type& rhs) const = " << rhs << std::endl;

        return !(operator==(rhs));
    }

    /** [LT] Returns "true" if the current value is LESS THAN another value. */
    bool operator<(const Type& rhs) const 
    {
        //std::cout << "Called function: bool operator<(const Type& rhs) const = " << rhs << std::endl;

        /* do actual comparison with *this */
        return (value < rhs) ? true : false;
    }

    /** [GE] Returns "true" if the current value is GREATER THAN or EQUAL TO another value. */
    bool operator>=(const Type& rhs) const
    {
        //std::cout << "Called function: bool operator>=(const Type& rhs) const = " << rhs << std::endl;

        return !(operator<(rhs));
    }

    /** [GT] Returns "true" if the current value is GREATER THAN another value. */
    bool operator>(const Type& rhs) const 
    {
        //std::cout << "Called function: bool operator>(const Type& rhs) const = " << rhs << std::endl;

        /* do actual comparison with *this */
        return (value < rhs) ? false : true;
    }

    /** [LE] Returns "true" if the current value is LESS THAN or EQUAL TO another value. */
    bool operator<=(const Type& rhs) const
    {
        //std::cout << "Called function: bool operator<=(const Type& rhs) const = " << rhs << std::endl;

        return !(operator>(rhs));
    }

    void BooleanChecks(const Type& comparison = {0.789f})
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

    //==========================================================================
    /** Value object of type <Type>. */
    Type value;
};

/** Addition allocation operator. */
template<typename Type>
inline Value<Type> operator+(Value<Type> lhs, const Value<Type>& rhs)
{
    lhs.operator+=(rhs);
    std::cout << "Called function: inline Value<Type> operator+(Value<Type> lhs, const Value<Type>& rhs) = " << lhs << std::endl;
    return lhs;
}

/** Addition allocation operator. */
template<typename Type>
inline Value<Type> operator+(const Value<Type> lhs, const Type& rhs)
{
    lhs.operator+=(rhs);
    std::cout << "Called function: inline Value<Type> operator+(const Value<Type>& lhs, const Type& rhs) = " << lhs.value << std::endl;
    return lhs;
}

//==============================================================================
template<typename Type>
std::ostream& operator<<(std::ostream& ostream, Value<Type>& value)
{
    ostream << value.value;

    return ostream;
}

template<typename Type>
std::istream& operator>>(std::istream& istream, Value<Type>& value)
{
  if(value.get() != nullptr)
    istream.setstate(std::ios::failbit);

  return istream;
}

//==============================================================================
template class Value<int>;
template class Value<float>;
template class Value<double>;
template class Value<long double>;
