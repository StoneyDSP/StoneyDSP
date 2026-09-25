# Nonlinear feedback reference

## Distinguish positions

These are not equivalent:

- filter -> clipper;
- clipper -> filter;
- clipper inside feedback;
- nonlinear state/integrator update;
- slew limiter after an otherwise implicit solve.

Model the position that corresponds to the hypothesis being tested.

## Soft rail

A useful smooth finite-swing function is:

`y = x / sqrt(1 + (x/rail)^2)`

Use separate positive and negative rail magnitudes if asymmetry is needed.

Its derivative with respect to x is:

`dy/dx = 1 / (1 + (x/rail)^2)^(3/2)`

The derivative is needed only when solving an implicit equation with Newton-Raphson or similar methods.

## Newton-Raphson

For an implicit current-sample equation `F(v)=0`, iterate:

`v <- v - F(v)/F'(v)`

Use a linear closed-loop estimate as the initial guess when available.
Keep iteration count small and deterministic for realtime DSP.
Test convergence near rails and under extreme feedback settings.

## Slew

An explicit slew limiter is a rate constraint on state/output change, for example:

`delta = clamp(target - previous, -maxDelta, +maxDelta)`

`state = previous + delta`

Do not mistake this for emergent high-frequency limitation from finite loop gain. They can coexist and produce similar-looking scope behaviour.

When diagnosing a model, temporarily disable or raise the explicit slew limit to determine how much edge softening is coming from the feedback/bandwidth system alone.
