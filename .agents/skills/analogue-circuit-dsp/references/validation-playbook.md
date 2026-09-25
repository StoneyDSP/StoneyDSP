# Validation playbook

## First establish the reference

For every block, define the expected ideal or linear response before adding finite/nonlinear behaviour.

Useful monitor states:

- Ideal
- Finite
- Residual = Finite - Ideal

## Static tests

- unity/zero-gain null;
- gain at nominal operating points;
- frequency response at low/mid/high control positions;
- boost/cut symmetry where expected;
- polarity;
- DC response;
- maximum/minimum control endpoints.

## Dynamic tests

- impulse and impulse train;
- step response;
- sine sweep;
- saw/pulse for edge and slew behaviour;
- parameter automation at several speeds;
- mute/unmute transitions;
- sample-rate changes.

## Nonlinear tests

- THD versus level;
- THD versus frequency;
- multitone/IMD;
- single source versus multiple sources at matched total level;
- asymmetric positive/negative drive;
- rail approach and recovery;
- residual spectrum.

## Stateful / feedback tests

- inspect response after silence;
- inspect recovery from overload;
- test DC accumulation/trapping;
- verify solver stability near rails;
- compare with slew/rate limiting disabled when diagnosing overlapping mechanisms.

## Real programme material

After analytical validation, use real drums, bass, vocals, mixes, or other relevant programme material. Prefer changes that are subtle at nominal settings and become legible under controlled stress rather than obvious coloration at all times.

## Regression discipline

When a revision is known-good:

- freeze it;
- branch experiments from it;
- compare the new revision against the frozen reference;
- do not silently change multiple model assumptions at once.
