# Controller Troubleshooting

## Symptom: one LED ring doesn't work

The most common fault reported on v2.x controllers. It is almost always a
**broken via** — a plated through-hole that doesn't connect the bottom and upper
layers of the board. The fix is to bridge it manually.

### 1. Check polarity first

Before assuming a board fault, confirm the ring is wired the right way round.
Each output connector has a defined positive side — see the
[wiring diagrams](headlight-wiring.md) for your board revision, and remember
that **v2.1 (green) and v2.2 (black) have different polarity and connector
handing**.

### 2. Bridge the suspect vias

There are specific points on the board that need to be soldered **on both
sides**. These should already connect the bottom and upper layers, but on some
controllers that connection is broken.

For this you need some wire — the legs cut off a couple of resistors or any
other through-hole component work perfectly.

1. Push the resistor leg through the hole you want to bridge.
2. Solder it on **both** sides of the board.
3. Snip the wire flush.

Repeat for each of the marked points.

### 3. Solder the outputs

Finally, solder the output pads on both sides of the board. The outputs are the
multiple holes at each output position.

This step isn't strictly necessary, but it's good practice to make a connection
through at least one hole at every output. Two is better.

### Result

With every marked connection bridged on both sides, the dead ring comes back.

---

## Other failure modes

**Board completely dead.** Check the in-line fuse on that headlight run, then
the PSU output. If the PSU has spiked, the input regulator to the
microcontroller may be blown — this is a visibly identifiable failure, and it is
what the recommended **2 A in-line fuse per headlight run** is there to prevent.
See [power supplies](power-supply.md).

**Controller runs hot / fails after a while.** Almost always too much input
voltage. The excess is dissipated as heat. Re-tune the PSU per the
[voltage tuning procedure](power-supply.md#tuning-the-voltage) — you want about
1 V dropped across the controller, never more than 1.5 V.

**Rings flicker.** Check the PWM timer prescaler settings if you've reflashed
the firmware; the default Arduino PWM frequency is low enough to be visible. See
[firmware notes](../firmware.md#pwm-setup).

**Rings don't dim at all.** The in-line regulator boxes supplied with the rings
haven't been removed. Cut them off — see
[ring installation](ring-installation.md#step-1--remove-the-in-line-regulators).

**Rings bounce between modes while indicating.** The indicator debounce and
lockout timers exist to prevent exactly this. If you've modified
`INDICATOR_DEBOUNCEDELAY` or `INDICATOR_LOCKOUTDELAY`, put them back.

---

> The original wiki guide included 19 step-by-step photographs of the via
> bridging process. Those images were hosted on the Project Halo wiki, which is
> no longer online and was not captured by the Internet Archive.

*Originally documented on the Project Halo wiki.*
