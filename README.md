# <p align="center">StoneyDSP</p>

<p align="center">The StoneyDSP audio, graphics, and web library for JUCE.</p>

<div align="center">

| Latest release: | [v.0.0.1-rc](https://github.com/StoneyDSP/StoneyDSP/tree/v0.0.1-rc) |
| :-: | :-: |
| Latest development: | Formats: |
[![windows-latest](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/windows-latest.yaml/badge.svg?branch=development&event=push)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/windows-latest.yaml) | VST3, Standalone |
[![ubuntu-latest](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/ubuntu-latest.yaml/badge.svg?branch=development&event=push)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/ubuntu-latest.yaml) | LV2, VST3, Standalone |
[![macos-latest](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/macos-latest.yaml/badge.svg?branch=development&event=push)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/macos-latest.yaml) | AU, VST3, Standalone |
[![macos-arm-latest](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/macos-arm-latest.yaml/badge.svg?branch=development&event=push)](https://github.com/StoneyDSP/StoneyDSP/actions/workflows/macos-arm-latest.yaml) | AU, VST3, Standalone |

<hr>

[![StoneyDSP](https://raw.githubusercontent.com/StoneyDSP/StoneyDSP/production/extras/Icons/images/w_icon__384x256.png)](https://www.stoneydsp.com)

<hr>

</div>

| <p>Hi! I'm <a href="https://github.com/nathanjhood">Nathan</a> (aka StoneyDSP).</p>  |
| :-: |
| |
| <p align="center"><i><b>I am making a C++ library extension for the [JUCE](https://github.com/juce-framework/JUCE) framework for building audio and graphical software applications.</b></i></p> |
| <p align="left">You may use this library to build your own audio software with on <a href="https://github.com/StoneyDSP/StoneyDSP?tab=License-1-ov-file">MIT license</a>. You must also respect the <a href="https://github.com/juce-framework/JUCE?tab=License-1-ov-file">JUCE license system</a>.</p> |
| |
| <p align="left">The primary goal here is/will be to provide some additional DSP (digital signal processing) classes, utilities, and functions of specific interests; the StoneyDSP library aims to be relatively approachable to builders with firm backgrounds in patching together new ideas from modular pieces of software or hardware, by using familiar conventions and abstractions and aiming to provide a low cognitive overhead.</p> |
| |
| <p align="left">StoneyDSP is *not* an audio plugin manufacturer or vendor explicitly, but aims to provide a useful set of coding tools that can be used to create interesting audio and graphical effects with, specifically targeting the JUCE application framework. </p> |
| |
| <p align="left">To this end, JUCE is the standard that the StoneyDSP library must follow closely; in order to guarantee a solid and familiar interface, our codebase intentionally mimics the JUCE project in lots of places, taking JUCE as our leading example. This also helps us minimize our own dependencies on JUCE itself, thus keeping our project as lightweight and portable as possible (we aim to be buildable without even needing to link with ```juce_core```, ideally). </p> |
| |
| <p align="left">Familiar base functionality aside, builders will find useable, modular DSP classes with interfaces reminiscent of the many popular "rack" modular environments, accompanied by strong documentation and plenty working examples. Being that StoneyDSP is not affiliated with JUCE itself in any way, we are also afforded all the scope we like for investigating various ideas that JUCE itself might not support directly.</p> |
| <p align="center"><i><b>...we are seeking to ease the flow of creativity within the creation of audio software itself...</b></i></p> |
| <p align="left">We are still in the early days of construction, so please consider bookmarking and keeping on eye on development!</p> |
| |
| <p align="left">This is something that I am working on during my free time, so progress may be sporadic; however, I/we already have a *lot* of plugins, instruments, and interesting DSP up and running behind the scenes, and even more in working prototypes and breadboards. There are also various other types of software and tooling currently under construction that will likely appeal to visitors of this project.</p> |
| <p align="center"><i><b>...in other words, plenty of reasons to stay tuned!</b></i></p> |
| <p align="left">Meanwhile, a small selection of older audio plugins are available as source code under permissive open-source licenses, much of which shall be re-contextualized to make use of the StoneyDSP audio and graphics libraries in due course, and may be found here:</p> |
| |
| [![Biquads](https://github-readme-stats.vercel.app/api/pin/?username=nathanjhood\&repo=Biquads\&theme=transparent)](https://github.com/StoneyDSP/Biquads) [![OrfanidisBiquad](https://github-readme-stats.vercel.app/api/pin/?username=nathanjhood\&repo=OrfanidisBiquad\&theme=transparent)](https://github.com/StoneyDSP/OrfanidisBiquad) |
| |
| [![NonLinearFilters](https://github-readme-stats.vercel.app/api/pin/?username=nathanjhood\&repo=NonLinearFilters\&theme=transparent)](https://github.com/nathanjhood/NonLinearFilters) [![BiLinearEQ](https://github-readme-stats.vercel.app/api/pin/?username=nathanjhood\&repo=BiLinearEQ\&theme=transparent)](https://github.com/nathanjhood/BiLinearEQ) |
| |
| [![AudioPlugin-SVF](https://github-readme-stats.vercel.app/api/pin/?username=nathanjhood\&repo=AudioPlugin-SVF\&theme=transparent)](https://github.com/nathanjhood/AudioPlugin-SVF) [![AudioPlugin](https://github-readme-stats.vercel.app/api/pin/?username=nathanjhood\&repo=AudioPlugin\&theme=transparent)](https://github.com/nathanjhood/AudioPlugin) |
| <p>*we = just <a href="https://github.com/nathanjhood">me</a>, for now! </p> |

<small>

The StoneyDSP Library

Copyright (C) 2024 Nathan J. Hood <nathanjhood@googlemail.com>

THIS SOURCE CODE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED
WARRANTY. IN NO EVENT WILL THE AUTHOR BE HELD LIABLE FOR ANY DAMAGES
ARISING FROM THE USE OF THIS SOFTWARE.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
  claim that you wrote the original source code. If you use this source code
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

For more information, visit the website:
[www.stoneydsp.com](https://www.stoneydsp.com)

FULL STONEYDSP TERMS:
- [STONEYDSP END-USER LICENSE AGREEMENT](https://www.stoneydsp.com/licence)
- [STONEYDSP PRIVACY POLICY](https://www.stoneydsp.com/privacy-policy)

</small>
