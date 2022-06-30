
/** BEGIN_JUCE_MODULE_DECLARATION

    ID:             stoneydsp_maths
    vendor:         stoneydsp
    version:        0.1.1
    name:           StoneyDSP Maths-based classes
    description:    Lightweight Maths-based classes
    website:        github.com/StoneyDSP
    license:        Proprietary

    dependencies:   

    END_JUCE_MODULE_DECLARATION
*/

#pragma once

#define STONEYDSP_MATHS_H_INCLUDED

#include <atomic>
#include <cmath>

#undef Complex
#undef Factor
#undef check

#include "math/stoneydsp_Constants.h"
#include "math/stoneydsp_Conversion.h"
#include "math/stoneydsp_MathMod.h"
#include "math/stoneydsp_Operators.h"
