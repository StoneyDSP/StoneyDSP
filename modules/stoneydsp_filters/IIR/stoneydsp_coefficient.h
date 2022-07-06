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
    ~Coefficient();

    /** Returns the coefficient's current value. */
    SampleType get() const noexcept { return value; }

    /** Returns the coefficient's current value. */
    operator SampleType() const noexcept { return value; }

    /** Changes the coefficient's current value. */
    Coefficient& operator= (SampleType newValue);

protected:
    /** Override this method if you are interested in receiving callbacks
        when the parameter value changes.
    */
    void valueChanged(SampleType newValue);

private:
    //==============================================================================
    SampleType getValue() const;
    void setValue(SampleType newValue);

    std::atomic<SampleType> value;
};

} //namespace filters
} //namespace stoneydsp
