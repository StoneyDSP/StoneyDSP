
/** BEGIN_JUCE_MODULE_DECLARATION

    ID:             stoneydsp_filters
    vendor:         stoneydsp
    version:        0.1.1
    name:           StoneyDSP Filter classes
    description:    Lightweight filter parts as classes
    website:        github.com/StoneyDSP
    license:        Proprietary

    dependencies:   juce_audio_basics, juce_audio_processors, juce_dsp

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

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

#include "IIR/stoneydsp_1st_Order_Coefficients.h"
#include "IIR/stoneydsp_1st_Order_Transforms.h"
#include "IIR/stoneydsp_1st_Order_Filters.h"
#include "IIR/stoneydsp_2nd_Order_Coefficients.h"
#include "IIR/stoneydsp_2nd_Order_Transforms.h"
#include "IIR/stoneydsp_2nd_Order_Filters.h"
#include "IIR/stoneydsp_coefficient.h"
#include "IIR/stoneydsp_Matched_Biquads.h"
