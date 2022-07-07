/*
  ==============================================================================

    Coefficient.h
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
class Coefficient
{
public:
    Coefficient(SampleType init);
    Coefficient(const Coefficient& other) noexcept;
    ~Coefficient();

    //==========================================================================
    /** Returns the coefficient's current value. */
    SampleType get() const noexcept { return value; }

    /** Returns the coefficient's current value. */
    operator SampleType() const noexcept { return value; }

    //==========================================================================
    /** Changes the coefficient's current value. */
    Coefficient& operator= (SampleType newValue);

    /** Atomically adds a number from the coefficient value, returning the new value. */
    Coefficient& operator+= (SampleType amountToAdd) noexcept { return value += amountToAdd; }

    /** Atomically subtracts a number from the coefficient value, returning the new value. */
    Coefficient& operator-= (SampleType amountToSub) noexcept { return value -= amountToSub; }

    /** Atomically multiplies the coefficient by a number, returning the new value. */
    Coefficient& operator*= (SampleType amountToMul) noexcept { return value *= amountToMul; }

    /** Atomically divides the coefficient by a number, returning the new value. */
    Coefficient& operator/= (SampleType amountToDiv) noexcept { return value /= amountToDiv; }

    /** Atomically increments this value, returning the new value. */
    Coefficient& operator++() noexcept { return ++value; }

    /** Atomically decrements this value, returning the new value. */
    Coefficient& operator--() noexcept { return --value; }

    /** Atomically inverts this value, returning the new value. */
    Coefficient& operator-() noexcept { return -value; };

protected:
    //==========================================================================
    /** Override this method if you are interested in receiving callbacks
        when the value changes.
    */
    void valueChanged(SampleType newValue);

private:
    //==========================================================================
    SampleType getValue() const;
    void setValue(SampleType newValue);

    //==========================================================================
    std::atomic<SampleType> value;
};

} //namespace filters
} //namespace stoneydsp
