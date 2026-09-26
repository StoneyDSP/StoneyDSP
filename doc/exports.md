# Export and visibility contract

`STONEYDSP_EXPORTS` is a build-time definition for the library itself. It
selects export behaviour when producing a shared library; consumers must not
define it when importing that library.

The definition is applied by the StoneyDSP target construction, not by a
consumer's ad-hoc compiler flags. The installed target propagates the matching
static/shared consumer contract.

## Declaration-level visibility

Visibility is deliberately opt-in:

- use `STONEYDSP_PUBLIC_FUNCTION` for C-facing public functions;
- use `STONEYDSP_API` on the deliberately public C++ declarations;
- preserve `STONEYDSP_STATIC` behaviour for static consumers;
- avoid broad class-level export annotations when member-level annotations are
  the chosen public model.

Do not remove export annotations globally to make one compiler happy. Diagnose
whether the error is caused by a declaration kind, duplicate annotation,
template instantiation, compile-definition propagation, or a real missing
symbol. Apply the smallest repair that retains the intended public surface.

## Evidence required

For shared-library changes, verify:

1. the library builds with its export definition;
2. the installed target imports correctly from an external consumer;
3. a static consumer does not request DLL imports;
4. a shared consumer links and runs;
5. symbol inspection agrees with the intentional declaration set.

The detailed compatibility model is in [Portable public API](portable-api.md).
