#ifdef STONEYDSP_GRAPHICS_H_INCLUDED
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of cpp file"
#endif

#include "stoneydsp_graphics.h"

#include <juce_audio_basics/juce_audio_basics.cpp>
#include <juce_audio_processors/juce_audio_processors.cpp>
#include <juce_graphics/juce_graphics.cpp>
#include <juce_gui_basics/juce_gui_basics.cpp>
#include <juce_gui_extra/juce_gui_extra.cpp>

#include "components/stoneydsp_AutoComponent.cpp"
