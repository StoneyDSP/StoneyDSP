
/** BEGIN_JUCE_MODULE_DECLARATION

    ID:             stoneydsp_filters
    vendor:         stoneydsp
    version:        0.1.1
    name:           StoneyDSP Filter classes
    description:    Lightweight filter parts as classes
    website:        github.com/StoneyDSP
    license:        Proprietary

    dependencies:   

    END_JUCE_MODULE_DECLARATION
*/

#pragma once

#define STONEYDSP_FILTERS_H_INCLUDED

#include <assert.h>
#include <atomic>
#include <cmath>
#include <vector>

#undef Complex
#undef Factor
#undef check

#include "IIR/stoneydsp_2nd_Order_Coefficients.h"
#include "IIR/stoneydsp_2nd_Order_Transforms.h"
#include "IIR/stoneydsp_2nd_Order_Filter.h"
