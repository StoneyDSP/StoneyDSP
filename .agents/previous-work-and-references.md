# Previous work and references

Below is a list of plugins created by me _before_ Nathan took the informed decision to centralise my DSP classes and concepts for reusability and distributability.

| Repository | Value to StoneyDSP | Initial disposition | URL |
| --- | --- | --- | --- |
| `Biquads` | Richest candidate: modern CMake/vcpkg structure, public modular headers, tests/pluginval, multimode biquads, bilinear transforms, precision switching, oversampling | Primary audit target | [https://github.com/nathanjhood/Biquads](https://github.com/nathanjhood/Biquads) |
| `AudioPlugin` | Mature JUCE plugin-template architecture: Processor/Parameters/Editor/Wrapper, APVTS, bypass, gain, smoothing, state | Product-template reference, not library source | [https://github.com/nathanjhood/AudioPlugin](https://github.com/nathanjhood/AudioPlugin) |
| `AudioPlugin-SVF` | TPT state-variable filter with smoothing, float/double processing, multiple modes, oversampling and dry/wet handling | Strong behavioural reference | [https://github.com/nathanjhood/AudioPlugin-SVF](https://github.com/nathanjhood/AudioPlugin-SVF) |
| `SVF1` | Smaller, clearer TPT-SVF implementation | Useful comparison/reference | [https://github.com/nathanjhood/SVF1](https://github.com/nathanjhood/SVF1) |
| `NonLinearFilters` | First- and second-order nonlinear filters plus oversampling | Strong DSP stress-test candidate | [https://github.com/nathanjhood/NonLinearFilters](https://github.com/nathanjhood/NonLinearFilters) |
| `BiLinearEQ` | First-order filter building blocks and bilinear-transform ideas | Useful algorithmic reference | [https://github.com/nathanjhood/BiLinearEQ](https://github.com/nathanjhood/BiLinearEQ) |
| `OrfanidisBiquad` | Explicit prototype for Orfanidis-style non-cramping peak EQ | Research/reference only until independently revalidated | [https://github.com/nathanjhood/OrfanidisBiquad](https://github.com/nathanjhood/OrfanidisBiquad) |
| `VicanekBiquads` | Matched biquads and first-order transforms, credited to Martin Vicanek | Potentially valuable, but provenance review required | [https://github.com/nathanjhood/VicanekBiquads](https://github.com/nathanjhood/VicanekBiquads) |

All of the above plugins are simple test beds and/or experiments, not intended to become mature products. Their internal DSP classes and methodologies as well as their architectures and tooling are useful references for what audio plugins _might_ be able to do when powered with the shared, centralised StoneyDSP library in due course.
