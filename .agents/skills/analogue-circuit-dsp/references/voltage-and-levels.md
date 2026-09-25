# Voltage and level reference

## Universal model coordinate

Default convention:

- `24 Vpk = 0 dBFS reference`
- `x = V / 24`
- `V = 24x`
- `dBFS = 20*log10(|V|/24)`
- `V = 24*10^(dBFS/20)`

This calibration is a ruler, not a limiter.

Examples:

- 24 V -> 0 dBFS -> x=1
- 30 V -> +1.938 dBFS -> x=1.25
- 18 V -> -2.499 dBFS -> x=0.75
- 12 V -> -6.021 dBFS -> x=0.5
- 6 V -> -12.041 dBFS -> x=0.25

## Bits

Use binary gain units:

- one bit upward doubles voltage;
- one bit downward halves voltage;
- one bit = 6.020599913 dB amplitude ratio.

From the 24 V full-scale reference:

- 0 bits down -> 24 V
- 1 bit down -> 12 V
- 2 bits down -> 6 V
- 3 bits down -> 3 V
- 24 bits down -> about 1.4305 uV

The 24-bit-down point is a useful reference-floor marker, not literal silence.

## Headroom and noise are independent

Never derive circuit noise floor from supply voltage.
Never derive usable signal swing directly from supply voltage unless the circuit evidence supports it.

Track separately:

- positive supply rail;
- negative supply rail;
- positive usable output swing;
- negative usable output swing;
- nominal signal level;
- absolute noise RMS/peak model;
- clipping/soft-saturation onset.

A higher-voltage circuit generally has more potential voltage headroom relative to the same signal reference, but it does not automatically become quieter.

## Floating-point host behaviour

Allow internal normalized samples beyond +/-1 when the host supports floating point. Treat 0 dBFS as a reference mark in the modelling coordinate system until an actual fixed-range delivery or converter boundary is modelled.
