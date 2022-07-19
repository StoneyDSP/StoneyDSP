
#pragma once

template <typename X>
class Operators
{

};


/** [EQ] Returns "true" if the current value is EQUAL TO another value. */
template <typename X>
inline bool operator==(const X& lhs, const X& rhs){return (lhs == rhs) ? true : false;}

/** [NE] Returns "true" if the current value is NOT EQUAL to another value. */
template <typename X>
inline bool operator!=(const X& lhs, const X& rhs){return !operator==(lhs,rhs);}

/** [LT] Returns "true" if the current value is LESS THAN another value. */
template <typename X>
inline bool operator< (const X& lhs, const X& rhs){return (lhs < rhs) ? true : false;}

/** Returns "true" if the current value is GREATER THAN or EQUAL TO another value. */
template <typename X>
inline bool operator> (const X& lhs, const X& rhs){return  operator< (rhs,lhs);}

/** Returns "true" if the current value is GREATER THAN another value. */
template <typename X>
inline bool operator<=(const X& lhs, const X& rhs){return !operator> (lhs,rhs);}

/** Returns "true" if the current value is LESS THAN or EQUAL TO another value. */
template <typename X>
inline bool operator>=(const X& lhs, const X& rhs){return !operator< (lhs,rhs);}

//==========================================================================
/** Swap method. */
template <typename X>
void swap (X& bValue) noexcept
{
    auto& aValue = *this;

    X cValue = std::move(aValue);
    aValue = std::move(bValue);
    bValue = std::move(cValue);
}

/** Swap method. */
template <typename X>
void swap(X& aValue, X& bValue) noexcept 
{
    X cValue = std::move(aValue);
    aValue      = std::move(bValue);
    bValue      = std::move(cValue);
}

/** Swap method. */
template <typename X>
void swap(X& aValue, X& bValue, X& cValue) noexcept 
{
    cValue = std::move(aValue);
    aValue = std::move(bValue);
    bValue = std::move(cValue);
}