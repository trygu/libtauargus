# tauargus — core

The **core** module is the solver-independent engine of the τ-ARGUS rewrite: the
statistical-disclosure-control (SDC) data model, Argus / JJ file I/O, and the
entry points that drive each optimisation step.

It is a **static C++ library**. It does not talk to any solver directly — the
linear-programming backend lives in [`../csp`](../csp) and the
mixed-integer backend in [`../crp`](../crp). Core exposes a C++ object API
(`TauArgus` and its supporting classes in `src/TauArgus.h`) that the Python
binding (`python/cpp/bind_core.cpp` in the top-level repo) wraps with pybind11.

## Contents

- **Data model** — `PTable`/`PTableCont` (response & table containers),
  `DataCell`, `Variable`, `Code`/`SubCodeList`, `Properties`.
- **File I/O** — `JJFormat` (the binary `.jj` optimisation format), `AMPL`
  (HiGHS/AMPL LP export), `CSV`.
- **Engine** — `TauArgus` (table/code setup, safety & suppression,
  protection levels), `Ghmiter` (iterative rounding), `Hitas` (HiGHS-based
  secondary data handling).

The legacy Windows COM server, VB6 code, and SWIG/JNI wrappers that used to
ship here are gone; all bindings to the new stack are generated with
pybind11 instead of SWIG.

## Build

Core is built as part of the superbuild in the top-level repo:

```bash
cmake -S native -B native/build \
      -DHighs_DIR=$(brew --prefix)/lib/cmake/Highs
cmake --build native/build
```

Building it standalone (it has no external dependencies):

```bash
cmake -S native/core -B native/core/build
cmake --build native/core/build
```

Produces `libtauargus_core.a` and installs the public headers from `src/`.

## License

This fork is distributed under **EUPL-1.2**; see [LICENCE](LICENCE).
Original upstream EUPL 1.1 and copyright notices are retained. The later-version
permission in Article 5 of EUPL 1.1 is explained in [NOTICE.txt](NOTICE.txt).
