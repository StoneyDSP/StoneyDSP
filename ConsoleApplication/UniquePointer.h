/**
  ==============================================================================

    UniquePointer.h
    Created: 18 Jul 2022 18:42:29pm
    Author:  Nathan J. Hood
    Website: github.com/StoneyDSP
    email:   nathanjhood@googlemail.com

  ==============================================================================
*/

# pragma once

template<typename T>
class unique_ptr
{
    T* ptr;

public:
    //==========================================================================
    /** Default constructor. */
    unique_ptr() : ptr(nullptr) 
    {
        std::cout << "unique_ptr called its Default Constructor!" << std::endl;
        std::cout << std::endl;
    }

    explicit unique_ptr(T* source /*= nullptr*/) : ptr(source)
    {
        std::cout << "unique_ptr called its Initialized Constructor!" << std::endl;
    }

    /** Copy constructor. */
    unique_ptr(unique_ptr& source) : ptr(source.ptr)
    {
        //ptr = source.ptr;
        std::cout << "unique_ptr called its Copy Constructor!" << std::endl;
        std::cout << std::endl;
    }

    /** Move constructor. */
    unique_ptr(unique_ptr&& source) : ptr()  // note the rvalue reference
    {
        std::cout << "unique_ptr called its Copy Constructor!" << std::endl;
        std::cout << std::endl;

        ptr = source.ptr;
        source.ptr = nullptr;
    }

    /** Destructor. */
    ~unique_ptr()
    {
        std::cout << "unique_ptr called its Destructor!" << std::endl;
        std::cout << std::endl;

        delete ptr;
    }

    //==========================================================================
    T* operator->() const
    {
        return ptr;
    }

    T& operator*() const
    {
        return *ptr;
    }

    //==========================================================================
    /** Assignment operator [COPY]. */
    unique_ptr& operator=(unique_ptr& source)
    {

    }

    /** +Assignment operator [MOVE]. */
    unique_ptr& operator=(unique_ptr&& source)   // note the rvalue reference
    {
        if (this != &source)    // beware of self-assignment
        {
            delete ptr;         // release the old resource

            ptr = source.ptr;   // acquire the new resource
            source.ptr = nullptr;
        }
        return *this;
    }

    /** Assignment operator [UNIFIED]. */
    unique_ptr& operator=(unique_ptr source)   // note the missing reference
    {
        std::swap(ptr, source.ptr);
        return *this;
    }
};

//==============================================================================
template<typename T>
std::ostream& operator<<(std::ostream& ostream, unique_ptr<T>& source)
{
    ostream << source.operator->();

    return ostream;
}

template<typename T>
std::istream& operator>>(std::istream& istream, unique_ptr<T>& source)
{
  if(source.operator->() != nullptr)
    istream.setstate(std::ios::failbit);

  return istream;
}
