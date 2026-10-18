# Sources and Provenance

This repository was reassembled in 2026 from material that was scattered across
three places, two of which no longer exist.

## Where the content came from

**`projects.jabawoki.com`** — the original MediaWiki that hosted the project
documentation. The site is offline. The pages here were recovered from
Internet Archive captures of the wiki:

| Page | Source |
|---|---|
| [controller.md](docs/controller.md) | `DRL_Controller_Information` |
| [parts-list.md](docs/parts-list.md) | `Parts_List` |
| [tools.md](docs/tools.md) | `Tools_Required` |
| [vehicle-applications.md](docs/vehicle-applications.md) | `Vehicle_Applications` |
| [guides/headlight-splitting.md](docs/guides/headlight-splitting.md) | `Headlight_splitting` |
| [guides/troubleshooting.md](docs/guides/troubleshooting.md) | `Controller_Troubleshooting` |

**`jabawoki.com`** — the project pages on the main site, recovered from a local
archive of the WordPress installation:

| Page | Source |
|---|---|
| [guides/bumper-removal.md](docs/guides/bumper-removal.md) | `/projects/project-halo/bumper-removal/` |
| [guides/headlight-wiring.md](docs/guides/headlight-wiring.md) | `/projects/project-halo/headlight-wiring/` |
| [guides/ring-installation.md](docs/guides/ring-installation.md) | `/projects/project-halo/installation-of-the-rings/` |
| [guides/power-supply.md](docs/guides/power-supply.md) | `/projects/project-halo/power-supplies/` |
| [guides/diy-delay-off-relay.md](docs/guides/diy-delay-off-relay.md) | `/projects/project-halo/make-your-own-12v-10s-off-relay/` |

**`alfaowner.com`** — the [build thread](https://www.alfaowner.com/threads/project-halo-the-159-brera-spider-halo-drl-project.314184/),
78 pages, started 2013. The project's actual history. Schematics, PCB layouts,
power diagrams and build photographs were recovered from thread attachments.

**Jay's local project archive** — the original working directory, which
survived on local storage and supplied material that existed nowhere online:

| Path | Source |
|---|---|
| [hardware/designspark/](hardware/designspark/) | DesignSpark `.sch`/`.pcb`/`.prj`, from `Halo Production V2` (15 Oct 2013) |
| [hardware/gerbers/](hardware/gerbers/) | Gerber + Excellon plot set, same revision |
| [hardware/schematic.pdf](hardware/schematic.pdf), [pcb-layout.pdf](hardware/pcb-layout.pdf), [3d-render.pdf](hardware/3d-render.pdf) | Exported design documents |
| [hardware/bom.xlsx](hardware/bom.xlsx) → [bom.md](docs/bom.md) | DesignSpark-generated bill of materials with RS/Farnell part numbers |
| [firmware/development/](firmware/development/) | The eight development sketches, V1–V7 |
| [docs/images/originals/](docs/images/originals/) | 16 camera-original photographs |

The local tree held several copies of the hardware design at different dates
(July, August and October 2013). Only the newest — `Halo Production V2` — was
imported, to avoid shipping conflicting versions of the same board.

**The fork** — [`nindidooo/ProjectHaloUK`](https://github.com/nindidooo/ProjectHaloUK)
carries one post-handover commit by Matt Brown (Aug 2019). Not merged, but
analysed in [firmware-history.md](docs/firmware-history.md).

**YouTube** — the nine Project Halo videos on
[@JayAbbott_UK](https://www.youtube.com/@JayAbbott_UK), indexed in
[videos.md](docs/videos.md). All nine were confirmed live via the oEmbed API.

**This repository** — `HaloProductionV2.ino` was already here, committed in
2018. [firmware.md](docs/firmware.md) is new, written by reading the sketch.

## What is missing

Some images could not be recovered and are noted inline where they're absent:

- **The 19 controller troubleshooting photographs.** These were hosted on the
  project wiki. The Internet Archive captured the wiki's HTML but not its
  `/images/` directory, so they are gone.
- **The four Alfa eLearn bumper removal diagrams.** Same cause. These are Alfa
  Romeo copyright material in any case.
- **Various headlight splitting step photographs**, for the same reason.
- **The LED ring / in-line regulator diagram** referenced in
  [controller.md](docs/controller.md). This was an alfaowner.com attachment
  (ID 171605). The forum's image CDN has since reassigned that ID and now
  serves an unrelated image for it, so the original is unrecoverable.

The text of every guide is complete.

## A note on forum attachment IDs

Images recovered from the alfaowner.com thread were fetched by numeric
attachment ID. **The CDN reuses IDs** — a number that once pointed at a
schematic can now return something entirely unrelated. Every image sourced that
way was therefore checked visually before being committed, and several were
rejected. If you add more, verify them by eye; do not trust the ID.

## Deliberately excluded

`Potential buyers.xlsx` was present in the local archive. It contains customer
contact details and is not published here.

## Editorial changes

The source material was written between 2013 and 2016, as wiki pages and forum
posts, for people actively buying controllers. In reassembling it:

- Forum BBCode in the old README was removed.
- Dead supplier links were replaced with part descriptions and part numbers.
  RS and Durite part numbers are preserved where they were given.
- Prices are left at their 2014 values and labelled as such.
- Safety notes that were scattered through forum posts — the 2 A per-headlight
  fuse, the over-voltage failure mode — were pulled into the relevant guides.
- Cross-references between guides were added; the original wiki had these,
  the WordPress pages mostly didn't.
- [firmware.md](docs/firmware.md) is entirely new. Where the sketch's own
  comments contradict its constants, the discrepancy is flagged rather than
  silently corrected.

Nothing in the technical content was invented. Where the original was silent,
this archive is silent.
