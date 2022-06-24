
/** BEGIN_JUCE_MODULE_DECLARATION

    ID:             stoneydsp_filters
    vendor:         stoneydsp
    version:        0.1.1
    name:           StoneyDSP Filter classes
    description:    Lightweight filter parts as classes
    website:        github.com/StoneyDSP
    license:        Proprietary
    minimumCppStandard: 14

    dependencies:   

    END_JUCE_MODULE_DECLARATION
*/

#pragma once

#define STONEYDSP_FILTERS_H_INCLUDED

#include <cmath>
#include <vector>

#include "biquads/stoneydsp_Biquad_Calcs.h"
#include "biquads/stoneydsp_Transforms.h"
