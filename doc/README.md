# Documentation map

Human-facing documentation is grouped by purpose:

- `architecture.md`: library purpose, component boundaries, public API model,
  product separation, and version contract.
- `consumer-integration.md`: CMake/vcpkg consumer contract, external
  validation, C API boundary, and JUCE integration direction.
- `portable-api.md`: C/C++ compatibility, ABI visibility, state ownership, and
  consumer validation rules.
- `dsp-development.md`: how discoveries from JSFX, Reaktor, legacy work, and
  research become portable, tested DSP primitives.
- `ui-bridge.md`: the native/web UI authority boundary and StoneyUI direction.
- `ci-release.md`: CI matrix intent, vcpkg cache discipline, and release
  validation.
- `project-workflow.md`: issue, project-board, branch, pull-request, validation,
  and public/private work-item conventions.
- `agent-workflows.md`: context rediscovery, repo-local skills, documentation
  generation, versioning, and worktree hygiene.
- `ai-statement.md`: how AI is used in the project and where human ownership
  remains.
- `analysis-tools.md`: relationships with the WebAudio analysis projects.
- `jsfx-workbench.md`: the separate REAPER JSFX workbench and its contribution
  to DSP exploration and development culture.
- `core.md`, `simd.md`, `dsp.md`, and `test.md`: component and validation
  documentation.
- `exports.md` and `presets.md`: package exports and CMake preset workflows.

Generated Doxygen output belongs under `build/doc/html/` and is not a source of
truth.
