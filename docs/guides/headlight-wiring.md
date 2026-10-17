# Headlight Wiring

Tapping the bulb feeds inside the headlight so the controller can sense what the
headlight is doing, and wiring the rings to the controller outputs.

## The goal

Create a positive (+) and negative (−) feed from each of these bulb circuits
inside the headlight unit:

- Main beam
- Driving lights
- Indicator

**The sidelight feed is deliberately not used.** That way you can switch your
sidelights on at dusk without changing the intensity of the halo rings — they
stay at day level.

## Important notes

- Make your joins as small and as neat as possible.
- Where possible, keep all cables routed away from the lights.
- **Do not let cables foul the reflector housing.** The beam-adjustment motors
  will strip their gears trying to move against a trapped cable.

## Wiring the feeds

**1. Build a 3-into-1 earth splitter.** Each feed to the controller is a + / −
pair, so splitting a single common earth into the three feeds the controller
inputs need is fine.

**2. Tap the existing earth.** Cut the black earth cable coming from the
junction area in the light — it's the one that already splits into several
earths for the bulbs. Join your new earth splitter cable to it, and route the
three earths through the headlight and out through a hole in the bottom of the
headlight case, above where the controller box will sit underneath.

**3. Tap each bulb feed.** Cut into the coloured wire for each bulb feed and
join a length of wire, routed along the same path as the earths.

> Colour-code or label these wires. You will not remember which is which later,
> and getting main beam and indicator swapped makes for some very confusing
> behaviour.

Once the three feeds are done you'll have something like this:

![Headlight feed wiring](../images/build/headlight-feed-wiring.jpg)

## What you should end up with

**Six new pairs of wires.** Positive and negative feeds *from*:

- Indicator
- Main beam
- Driving lights

Positive and negative feeds *to*:

- Inner ring
- Middle ring
- Outer ring

Leave enough wire on all six feeds to locate the controller where you want it,
and enough slack to remove the headlight later without unpicking everything.

## Controller wiring — v2.1 (green boards)

![v2.1 wiring diagram](../images/controller/wiring-v21-green.jpg)

## Controller wiring — v2.2 (black boards)

![v2.2 wiring diagram](../images/controller/wiring-v22-black.jpg)

> ⚠️ **v2.1 and v2.2 are wired differently.**
>
> The board revision required a fresh routing of the positive and negative
> tracks. As a result **the polarity on V-IN (power input from the PSU) is
> different, and the connector handing is reversed.**
>
> Take care to ensure the positive is in the correct side of the connector, per
> the diagram for your board. This bites hardest if you are upgrading a v2.1
> installation to v2.2 and reuse the existing loom.

Identify your board by colour: **green = v2.1, black = v2.2.**

## Next

- [Power supplies](power-supply.md) — getting a clean regulated feed to the controllers
- [Troubleshooting](troubleshooting.md) — if a ring won't light

---

*Originally documented on the Project Halo wiki and jabawoki.com.*
