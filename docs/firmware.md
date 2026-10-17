# Firmware

[`HaloProductionV2.ino`](../HaloProductionV2.ino) — the production sketch, as
shipped on the v2.x controllers.

Written for an ATmega running the Arduino core. It is deliberately simple: no
interrupts in anger, no libraries, one tight loop.

## Pin map

The pin numbers are Arduino pin numbers; the bracketed figures are the physical
pin numbers on the controller's ATmega.

| Variable | Arduino pin | Chip pin | Timer | Function |
|---|---|---|---|---|
| `led1` | 10 | 14 | Timer 1 | OUT1 — inner ring |
| `led2` | 3 | 1 | Timer 2 | OUT2 — middle ring |
| `led3` | 6 | 10 | Timer 0 | OUT3 — outer ring |
| `led4` | 9 | 13 | Timer 1 | OUT4 — spare output (v2 expansion) |
| `input1` | 17 | 26 | — | IN1 — indicator |
| `input2` | 16 | 25 | — | IN2 — main beam |
| `input3` | 15 | 24 | — | IN3 — driving lights |
| `input4` | 14 | 23 | — | IN4 — spare input (v2 expansion) |

Pins 0 and 1 carry the jumpers, and double as the serial lines if needed.

Inputs are fed through opto-isolators, so they are **active low**: a lit bulb
pulls the input `LOW`.

## PWM setup

`setup()` sets the prescaler on all three timers to `0x01`, which raises the PWM
frequency well above the default. This matters: at the default Arduino PWM
frequency the rings visibly flicker, especially in peripheral vision and on
camera.

```c
TCCR2B = TCCR2B & 0b11111000 | 0x01;
TCCR1B = TCCR1B & 0b11111000 | 0x01;
TCCR0B = TCCR0B & 0b11111000 | 0x01;
```

## Brightness levels

Brightness is an 8-bit PWM duty value, 0–255.

| Value | Duty |
|---|---|
| 25 | 10 % |
| 50 | 20 % |
| 100 | 40 % |
| 125 | 50 % |
| 175 | 70 % |
| 200 | 80 % |
| 255 | 100 % |

As shipped in this version:

| Variable | Value | Duty | Used for |
|---|---|---|---|
| `dayLevel` | 175 | 70 % | Day mode, all rings |
| `nightLevelInner` / `Middle` / `Outer` | 100 | 40 % | Night mode |
| `signalOuter` | 50 | 20 % | Indicator mode, inner and outer rings |
| `signalCentre` | 0 | off | Indicator mode, middle ring |
| `leddelay` | 6 | 6 ms/step | Start-up fade speed |

These are the tuning knobs. Change them and reflash if you want a different
look — but keep indicator mode clearly dimmer than the others, that's the whole
point of it.

## Timing

A software tick in `msTimers()` decrements the timers every `TIMER_TICK` (10 ms),
driven off `millis()`.

| Constant | Value | Real time |
|---|---|---|
| `TIMER_TICK` | 10 | 10 ms per tick |
| `INDICATOR_DEBOUNCEDELAY` | 25 | 250 ms |
| `INDICATOR_LOCKOUTDELAY` | 150 | 1.5 s |

> Note: the in-code comments on both indicator constants say "100ms". They are
> wrong — at a 10 ms tick the real values are 250 ms and 1.5 s. The comments
> were never updated when the values were tuned.

**Debounce** rejects electrical noise: a change on the indicator input must hold
for 250 ms before it is accepted as a real state change.

**Lockout** handles the flashing: once the indicator is seen as on, the
controller stays in indicator mode until the input has been continuously off for
1.5 s. This spans the gap between flashes, so the rings don't bounce in and out
of indicator mode on every blink.

## Mode priority

`Running()` evaluates in this order, so earlier cases win:

1. **Main beam** — `mainBeam == LOW` and no indicator → all rings hard on
   (`digitalWrite HIGH`, full brightness, no PWM)
2. **Day** — driving lights input `HIGH` (i.e. lights off) and no indicator →
   all rings at `dayLevel`
3. **Night** — otherwise, no indicator → rings at their night levels
4. **Indicator** — `IndicatorState == true` → inner and outer at `signalOuter`,
   middle off

## Structure

```
loop()
 └─ launch(1)          // one-shot start-up fade, then init indicator state
 └─ while(1)
     ├─ msTimers()        // tick the 10ms software timers
     ├─ DebounceIndicator()  // update debounced IndicatorState
     └─ Running()         // apply the right mode to the outputs
```

`loop()` never returns — the `while(1)` means the start-up sweep runs exactly
once per power-up, which is the intended behaviour.

## Revision history

**Development versions**

| | |
|---|---|
| V1–V2 | Experimental, no indicator function |
| V3 | Production, all functions OK |
| V4–V6 | Experimental, adding debounce |
| V7 | Production, added indicator debounce routine and 10 ms timer |
| V8 | Production, `IndicatorState` now set correctly on start-up |
| V9 | Production, increased brightness levels, added brightness key |

**Production versions**

| | |
|---|---|
| V1 | Updated pinouts for new hardware, brightness tweaks |
| V2 | Sorted pin mappings, adjusted timers for the faster chip — **this file** |

## Building

Open in the Arduino IDE, select the board matching your controller's ATmega and
clock, and upload via ISP. The `#include` lines use the old spaced form
(`#include < avr/io.h >`); modern toolchains accept it, but tidy it to
`#include <avr/io.h>` if your setup complains.

`avr/io.h` and `avr/interrupt.h` are included but the sketch no longer uses a
hardware ISR — the timing is done in software off `millis()`. They are harmless
leftovers from the V4–V7 debounce experiments.
