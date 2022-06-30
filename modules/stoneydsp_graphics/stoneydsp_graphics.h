
/** BEGIN_JUCE_MODULE_DECLARATION

    ID:             stoneydsp_graphics
    vendor:         stoneydsp
    version:        0.1.1
    name:           StoneyDSP Graphics-based classes
    description:    Lightweight Graphics-based classes
    website:        github.com/StoneyDSP
    license:        GPL/Commercial
    minimumCppStandard: 14
    dependencies: juce_audio_basics, juce_audio_processors, juce_graphics, juce_gui_basics, juce_gui_extra
    OSXFrameworks: CoreAudio CoreMIDI AudioToolbox
    iOSFrameworks: AudioToolbox

    END_JUCE_MODULE_DECLARATION
*/

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <../JUCE/modules/juce_audio_processors/juce_audio_processors.h>
#include <../JUCE/modules/juce_graphics/juce_graphics.h>
#include <../JUCE/modules/juce_gui_basics/juce_gui_basics.h>
#include <../JUCE/modules/juce_gui_extra/juce_gui_extra.h>

#define STONEYDSP_GRAPHICS_H_INCLUDED

#include <components/stoneydsp_AutoComponent.h>
