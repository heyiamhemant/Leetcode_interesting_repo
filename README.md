# Leetcode_interesting_repo

A personal collection of LeetCode solutions, paired with a gamified web tracker that turns the practice into an RPG adventure.

## Contents

- **`/` (root)** — Solutions to ~336 LeetCode problems in Python and C++, organized one file per problem.
- **`DSA_Dojo.html`** — V1 of the tracker: a single-file HTML app that visualizes the entire problem set as a forest-themed dungeon journey.
- **`v2/`** — V2 of the tracker: a cinematic Dark Souls-inspired rebuild with Dark Souls scene imagery, parallax pathway, animated fireflies, collapsible bento dashboard, and full mobile/Safari support.
- **`screenshots/`** — Preview captures from V1.

## Live Sites

- **V1 (Forest):** [heyiamhemant.github.io/DSA_Dojo/](https://heyiamhemant.github.io/DSA_Dojo/)
- **V2 (Dark Souls):** [heyiamhemant.github.io/DSA_Dojo/v2/](https://heyiamhemant.github.io/DSA_Dojo/v2/)

## Preview (V1)

| Dashboard | Quest Board |
|:-:|:-:|
| ![Dashboard](screenshots/dashboard.png) | ![Quest Board](screenshots/quest-board.png) |

| Bestiary | Dungeon Pathway |
|:-:|:-:|
| ![Bestiary](screenshots/bestiary.png) | ![Pathway](screenshots/pathway.png) |

## Features

### Core Game Loop
- **Dungeon Pathway** — A branching map that visualizes progression through DSA topics. V1 is a forest theme; V2 is a Dark Souls-style codex atlas with stone-seal keeps, animated fireflies, torch sconces, and per-topic Dark Souls scene art behind every node.
- **Quest Board** — A spaced-repetition engine that generates daily quests. It prioritizes overdue reviews over new problems, gates difficulty progression (no Hard problems until you've built a foundation in Easy and Medium), and supports a "minimum reviews" setting so the early days aren't dominated by unlocks.
- **Bestiary** — A filterable, sortable view of all tracked problems with difficulty, topic, confidence level, last reviewed date, and next due date. V2 cards each carry a Dark Souls scene image keyed to the problem's topic.
- **Boss Raids** — A separate System Design section with its own encounter tracking.

### Progress & Stats
- **XP & Leveling** — Earn XP scaled by difficulty and confidence. Level up through ranks from Wanderer to Mythic Champion.
- **Slime / Drake / Demon Tiers** — Easy / Medium / Hard problems are rendered as 🟢 Slimes, 🐉 Drakes, 👹 Demons throughout the UI (hero powerbars, quest cards, bestiary, realms tooltips, dashboard subtitle).
- **Power Levels** — Per-difficulty power bars showing how many of each tier you've slain.
- **Realms of Conquest (V2)** — Each topic gets a card with lifetime conquest %, 180-day momentum, tier breakdowns, conquered/alert badges, and a sortable toolbar.
- **Streak Tracking** — Consecutive review days earn XP multipliers. Milestone rewards at 3, 7, 14, 30, and 60-day streaks.
- **180-day Heatmap** — Month-labeled timeline of review activity with custom hover tooltips.
- **Chronicle of Battle** — 14-day analytics view (reviews per day, XP earned per day) with click-to-inspect bars.

### UX
- **Dashboard tabs (V2)** — Three tabs (Overview / Progress / Realms) with collapsible `<details>` panels whose open/closed state persists in `localStorage`.
- **Mobile-first** — Hamburger drawer nav, single-column card grids, every text element clamped/word-broken to prevent overflow.
- **Safari-tested** — All multi-layer card backgrounds use literal `background-image` strings (no CSS-variable indirection that Safari fumbles), `-webkit-backdrop-filter` prefixes everywhere, quoted relative URLs.
- **Export / Import** — Save and restore all progress as JSON.
- **Light & Dark Mode** — Full theme support.

## Run Locally

No build step. Everything is static.

```bash
git clone https://github.com/heyiamhemant/Leetcode_interesting_repo.git
cd Leetcode_interesting_repo

# V1
open DSA_Dojo.html

# V2
open v2/index.html
```

## Tech

- V1: single-file HTML (~330 KB) with inline CSS + JS + embedded problem data.
- V2: split into `v2/index.html` (UI + render layer) + `v2/dojo-core.js` (game logic, spaced-repetition algorithm, XP curves, problem data) + `v2/assets/` (Dark Souls scene art for personal use).
- Persistence: `localStorage` (with optional File System Access API hooks for Chromium-based browsers to keep a JSON file synced).
- No frameworks, no build, no server.

## Credits

Dark Souls scene imagery is fan-curated from the Dark Souls Fandom Wiki for personal/educational use.
