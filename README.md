# Leetcode_interesting_repo

A personal collection of LeetCode solutions, paired with two gamified web trackers that turn the practice into an RPG adventure.

## Contents

- **`/` (root)** — Solutions to ~336 LeetCode problems in Python and C++, organized one file per problem.
- **`DSA_Dojo.html`** — Local copy of the V1 tracker (forest theme, single-file HTML). Mirrored from [DSA_Dojo_legacy](https://github.com/heyiamhemant/DSA_Dojo_legacy).
- **`screenshots/`** — Preview captures from V1 and V2.

## Trackers (separate repos)

| Version | Repo | Live Site | Theme |
|---|---|---|---|
| **V2 (current)** | [github.com/heyiamhemant/DSA_Dojo](https://github.com/heyiamhemant/DSA_Dojo) | [heyiamhemant.github.io/DSA_Dojo/](https://heyiamhemant.github.io/DSA_Dojo/) | Cinematic Dark Souls |
| **V1 (legacy)** | [github.com/heyiamhemant/DSA_Dojo_legacy](https://github.com/heyiamhemant/DSA_Dojo_legacy) | [heyiamhemant.github.io/DSA_Dojo_legacy/](https://heyiamhemant.github.io/DSA_Dojo_legacy/) | Forest |

V2 features a cinematic rebuild with parallax pathway, animated fireflies, collapsible bento dashboard, Slime/Drake/Demon tier nomenclature, full Safari/mobile support, and per-topic Dark Souls scene art. V1 is the original forest-themed single-file build, kept around for posterity.

## Preview (V1 — Forest)

| Dashboard | Quest Board |
|:-:|:-:|
| ![Dashboard](screenshots/dashboard.png) | ![Quest Board](screenshots/quest-board.png) |

| Bestiary | Dungeon Pathway |
|:-:|:-:|
| ![Bestiary](screenshots/bestiary.png) | ![Pathway](screenshots/pathway.png) |

## Preview (V2 — Dark Souls)

| Title Screen | Dashboard |
|:-:|:-:|
| ![Intro](screenshots/intro_v2.png) | ![Dashboard V2](screenshots/dashboard_v2.png) |

| Realms of Conquest | Dungeon Pathway |
|:-:|:-:|
| ![Realms V2](screenshots/realms_v2.png) | ![Pathway V2](screenshots/pathway_v2.png) |

| Quest Board | Bestiary |
|:-:|:-:|
| ![Quest Board V2](screenshots/quest_board_v2.png) | ![Bestiary V2](screenshots/bestiary_v2.png) |

| Boss Raids |
|:-:|
| ![Boss Raids V2](screenshots/boss_raids_v2.png) |

## Run Locally

No build step. Everything is static.

```bash
# Solutions live here.
git clone https://github.com/heyiamhemant/Leetcode_interesting_repo.git
cd Leetcode_interesting_repo

# Open the included V1 tracker (or pull from the V1 repo for the canonical copy).
open DSA_Dojo.html

# For V2 (cinematic), use its own repo since it has assets/ and dojo-core.js.
git clone https://github.com/heyiamhemant/DSA_Dojo.git
open DSA_Dojo/index.html
```

## Credits

Dark Souls scene imagery (used in V2) is fan-curated from the Dark Souls Fandom Wiki for personal/educational use only.
