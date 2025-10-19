# Numerics 0 – Solutions (WS25/26)

Programming and written solutions for the Numerics 0 weekly sheets (Übungsblätter).
Lightweight collaboration setup for a 2–3 person team, with optional PRs and a simple CI build.

## Repository layout

```
num-sol-ws2526/
├─ hdnum/                         # submodule
├─ src/                           # CMake "top-level" lives here
│  ├─ CMakeLists.txt              # builds all ubN targets
│  ├─ ub1/
│  │  ├─ CMakeLists.txt           # defines ub targets
│  │  └─ ub1_task1.cpp
│  ├─ ub2/
│  │  └─ CMakeLists.txt
│  └─ ...
├─ theory/
│  ├─ ub1/
│  └─ ub2/
├─ .github/workflows/
│  └─ build.yml                   # CI (set working-directory: src)
└─ .gitignore
```

## Prerequisites

* Git (with submodule support)
* CMake ≥ 3.16
* C++ compiler (g++/clang++)
* Optional: GMP dev package (only if enabling high precision):

  ```bash
  sudo apt update && sudo apt install -y libgmp-dev
  ```
* Optional: Quarto CLI (only for rendering `.qmd` to PDF on your machine)


## Getting Started (for teammates)

### First-time clone (with submodule)

```bash
git clone --recurse-submodules https://github.com/igor-dimi/num-sol-ws2526.git
cd num-sol-ws2526
```

If you already cloned without submodules:

```bash
git submodule update --init --recursive
```

### Configure & Build

Configure once per build directory (or when changing options/CMake):

```bash
cd src/
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
# add -DHDNUM_USE_GMP=ON if you installed libgmp-dev and want high precision
```

Then build (repeat as you edit source files):

```bash
cmake --build build -j
```

Executables land under:

```
build/bin/ub1/..., build/bin/ub2/...
```

### Weekly structure

* Programming sources for week N: `src/ubN/`
* Written sources (QMD, optional PDFs/scans) for week N: `theory/ubN/`

### Lightweight collaboration workflow

* Main branch stays working (compiled locally before pushing).
* Use per-week branches; PRs are optional.

### Sync main

```bash
git checkout main
git pull --ff-only
git submodule update --init --recursive
```

### Create your branch for a week

Branch naming: `ub<Nr>_<yourname>` (e.g., `ub1_malte` or `ub2_igor`)

```bash
git checkout -b ub1_igor
# edit src/ub1/... and/or theory/ub1/...
cd src/
cmake --build build -j    # build locally before pushing
git add -A
git commit -m "ub1: implement task1; add notes"
git push -u origin ub1_igor
```

### Sync routinely

Before starting new work or merging:

```
git checkout main
git pull --ff-only
git submodule update --init --recursive
```

and update your branch on top of the latest main (optional but tidy):

```
git checkout ub1_<yourname>
git rebase origin/main
# resolve any conflicts → git add <files> → git rebase --continue
```

### Merging

* Small, low-risk changes: push/merge to `main` directly (or open a PR and self-merge).
* If both touched the same files or a change is risky: open a PR and request a quick review.

## Continuous Integration (CI)

* GitHub Actions builds on every **push** to `main` and on **pull requests**.
* CI does not block merges in this lightweight setup; it warns if `main` breaks.
* Workflow: `.github/workflows/build.yml`

  * Installs `cmake`, `g++`, `libgmp-dev`
  * Configures and builds the repo

## HDNUM submodule

* The library is header-only; no linking needed unless enabling GMP.

* To update the submodule to the recorded commit after pulling:

  ```bash
  git submodule update --init --recursive
  ```

* Do not modify files inside `hdnum/`. If you need changes, fork and repoint the submodule (not expected for this course).

## Optional: GMP (high precision)

Enable at configure time (persists in the build dir):

```bash
# cd src/
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DHDNUM_USE_GMP=ON
cmake --build build -j
```

## Submission packaging (outside this repo)

* Files are synced to a file-sharing root (Seafile) using a small `Makefile` from the course notes repo.
* In the share, a separate script renders `.qmd` → `.pdf` (incremental) and zips all PDFs + sources as:

```
Heinrich_BlattNN_Dimitrov_Herzog_Chae.zip
```

(We keep rendering/zipping outside this repo to keep the Git history clean.)

## .gitignore (suggested)

```
build/
*.o
*.a
*.exe
*.dat
.DS_Store
theory/**/*.pdf
```

## Conventions

* Branch names: `ub<N>_<name>` (e.g., `ub3_igor`, `ub3_malte`)
* Commit messages: concise and informative:

  * `ub1: add RK4 step + plot`
  * `ub2: fix Newton residual; add notes.qmd`
* Keep code and write-ups for a week in their respective `ubN` folders.
* Don’t commit large binaries or generated PDFs.

