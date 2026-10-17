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

The text of every guide is complete.

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
