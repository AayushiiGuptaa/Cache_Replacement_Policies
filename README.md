# Cache Replacement Policy Simulator

## Overview

This project simulates a cache memory system and compares different cache replacement policies.

Implemented policies:

- LRU (Least Recently Used)
- FIFO (First In First Out)
- Random
- Adaptive (LRU/FIFO)

The simulator executes multiple memory access traces and records cache statistics.

---

## Project Structure

```
BRANCH_PREDICTOR_PROJECT/

src/
    main.cpp
    cache.cpp
    cache.h
    ReplacementPolicy.h
    LRUPolicy.cpp
    LRUPolicy.h
    FIFOPolicy.cpp
    FIFOPolicy.h
    RandomPolicy.cpp
    RandomPolicy.h
    Adaptive.cpp
    Adaptive.h

traces/
    sequential.txt
    random.txt
    looping.txt
    matrix.txt

scripts/
    plots.py

results/
    results.csv
```

---

## Compilation

Compile using:

```bash
g++ src/*.cpp -o simulator -std=c++17
```

---

## Run

```
./simulator
```

Simulation results will be stored in

```
results/results.csv
```

---

## Generate Graphs

Run

```bash
cd scripts
python plots.py
```

Generated graphs will be saved in the `results` directory.

---

## Output

For every trace and policy, the simulator records

- Hits
- Misses
- Hit Rate

---

## Future Work

- Set Associative Cache
- Multi-level Cache
- ARC Replacement Policy
- Belady's Optimal Policy
- Hardware Performance Counters