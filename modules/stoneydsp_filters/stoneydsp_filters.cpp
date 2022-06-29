#ifdef STONEYDSP_FILTERS_H_INCLUDED
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of cpp file"
#endif

#include "stoneydsp_filters.h"

#include "IIR/stoneydsp_2nd_Order_Coefficients.cpp"
#include "IIR/stoneydsp_2nd_Order_Transforms.cpp"
#include "IIR/stoneydsp_2nd_Order_Filter.cpp"
