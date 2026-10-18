# Firmware Development History

`HaloProductionV2.ino` in the repo root is the sketch that shipped. This page
covers the eight development sketches that came before it, preserved in
[`firmware/development/`](../firmware/development/).

They are here as project history. **Don't flash them** — the pin assignments
changed between the breadboard prototypes and the production boards, so an early
sketch on a v2.x controller will drive the wrong pins.

## The two numbering schemes

The sketch header lists revisions under two headings, which is confusing until
you realise they're separate series:

**Development versions (V1–V9)** — written against prototype hardware, an
Arduino board with the rings wired to pins 9, 10 and 11.

**Production versions (V1–V2)** — rewritten for the custom PCB, where the rings
moved to pins 10, 3 and 6, and the inputs came in through optocouplers.

So "Production V2" is not "development V2 again". It's the second revision of
the production line, and it's the one in the repo root.

## Development series

| Sketch | Status | What changed |
|---|---|---|
| `HaloV1.ino` | Experimental | First working sketch. Three rings on pins 9/10/11, main beam on an interrupt. No indicator support. |
| `HaloV2.ino` | Experimental | Dropped the interrupt, polled the inputs instead. Added day/night levels and a `leds[]` array. |
| `HaloV3.ino` | **Production** | First version described as fully working — all functions OK. Added the ASCII-art header. |
| `HaloV4.ino` | Experimental | First attempt at indicator debouncing. |
| `HaloV5.ino` | Experimental | Second debounce attempt. |
| `HaloV5_1.ino` | Experimental | Variant of V5. Header documents the five operating modes for the first time. |
| `HaloV6.ino` | Experimental | Third debounce attempt. |
| `HaloV7.ino` | **Production** | Debouncing finally working, built on a 10 ms timer tick. The design that carried through to production. |

V8 and V9 are named in the revision history but aren't in the recovered tree.
V8 fixed `IndicatorState` not being initialised correctly at startup; V9
increased the brightness levels and added the brightness key — both of those
changes are present in the production sketch.

Three attempts at debouncing (V4, V5, V6) before V7 got it right. Contact bounce
on a car's indicator circuit is noisier than it looks.

## The five modes

Documented in the `HaloV5_1` header and unchanged through to production:

| Mode | Behaviour |
|---|---|
| 1 | Boot sequence — fade 0% → 100% → 80%, inner ring to outer, once |
| 2 | Daytime — all rings at the day level |
| 3 | Night — all rings dimmed |
| 4 | Signal — outer and inner rings dimmed, middle ring off |
| 5 | Main beam — all rings at full power |

Modes 3, 4 and 5 are selected by a signal on each of the three optocouplers.
Note the wording changed between versions: `HaloV7` says "+12 signal on each of
the 3 opto's", the production sketch says "a HIGH signal" — same thing, the
optocoupler isolates the 12 V side.

## Brightness levels

Both the development and production sketches use raw 8-bit PWM values. The
header carries a conversion key:

| Value | Duty |
|---|---|
| 25 | 10% |
| 50 | 20% |
| 100 | 40% |
| 150 | 60% |
| 175 | 70% |
| 200 | 80% |
| 255 | 100% |

The production sketch ships with `dayLevel = 175` (70%) and night levels of 100
(40%).

## The fork

The repo has one fork, [`nindidooo/ProjectHaloUK`](https://github.com/nindidooo/ProjectHaloUK),
which carries a single commit by Matt Brown from August 2019 — after the project
was handed over. It is not merged here, but it's a real piece of the project's
afterlife and worth recording.

Most of that diff is line-ending churn (the whole file was rewritten with CRLF),
but four changes are genuine:

- **Indicator behaviour replaced.** The production sketch dims the outer and
  inner rings and turns the middle one off during a signal. The fork turns all
  three rings fully off instead, and comments out the original dimming block.
- **Fade-back-on added.** A `resetAfterInd` flag triggers a full fade-up ramp
  when the indicator releases, rather than snapping back to level.
- **`dayLevel` raised** from 175 (70%) to 200 (80%).
- **`signalInner` added** and `signalCentre` raised from 0 to 50, though the
  block using them is commented out.

The fade-back-on runs inside the main loop with `delay()` calls, so the
controller is unresponsive for the duration of the ramp. Worth understanding
before adopting it.
