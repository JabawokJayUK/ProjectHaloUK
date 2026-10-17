# Vehicle Applications

## The target cars

The controllers were designed for:

- **Alfa Romeo 159** (saloon and Sportwagon)
- **Alfa Romeo Brera**
- **Alfa Romeo Spider**

All three use the same triple circular headlight design, which needs **three
different ring sizes per headlight**:

| Lens position | Ring |
|---|---|
| Inner | 95 mm |
| Middle | 90 mm |
| Outer | 85 mm |

Six rings and two controllers per car — one controller per headlight, each
driving three rings.

## Other vehicles

It is technically possible to use these controllers on **any vehicle that can
take aftermarket DRL rings**, with one caveat: the rings being driven must be
measurable for voltage and current so the controller can be configured
accordingly. Where the rings are the same type the units were designed for, no
measurement is needed.

### 2 or 4 ring vehicles

A single controller can run **up to 4 rings**. The v2 hardware added a fourth
output and a fourth input precisely for this — one controller taking main beam,
driving lights and two indicator triggers, driving four rings.

Available ring sizes:

- 72 mm
- 85 mm
- 90 mm
- 95 mm
- 100 mm

If these sizes fit your vehicle, the controllers will suit it.

### Other Alfas

The 147, 156 and GT were all identified as viable: the controller units can run
one, two or three rings each. It would need the firmware modes adjusting for the
ring count, and the headlights measuring to pick the right ring sizes and set
the power loads correctly.

## Compatibility notes

**Factory-fit Xenons** — yes, these work.

**Aftermarket HID kits, LEDs and other lighting mods** — yes, these work.

**Automatic headlight function** — yes. Mode switching is controlled by sensing
the bulb feeds inside the headlight, so it makes no difference whether the lights
were switched on by hand or automatically.

**Expected life** — the LED rings are quoted at 20,000 hours, though that figure
is the manufacturer's, not a measured one. Everything electrically viable was
done to give the LEDs optimum, safe, stable conditions, fully isolated and
protected from the car's electrical system.

---

*Originally documented on the Project Halo wiki.*
