# Calculation of density in the smoothed-particle hydrodynamics method using MPI and OpenACC

## Directory Structure

- `doc/` - compact documentation and report.
- `sph.py` - python sequential implementation.
- `plot.py` - python heat map creator.
- `src/` - source code.
    - `main` - entry point.
    - `grid` - density calculation.
    - `input` - read csv data from file.
    - `output` - write csv output to file.
    - `script.sh` - scrum script.
- `data/` - output and input data.

## Description

Given the positions and densities of particles, we build a 2d heat map of their densities using a gaussian kernel:

ρ ⋅ exp (-α ⋅(x - x_grid_ij)² + (y - y_grid_ij)² + (z - z_grid_ij)²)

We build a 2d grid of size nx × nz with coordinates:

x_grid_ij = (-R ⋅ i / (nx - 1) ⋅ 2 ⋅ R)

y_grid_ij = 0

z_grid_ij = (-R ⋅ j / (ny - 1) ⋅ 2 ⋅ R)

## Results

![Alt text](img/graph1000.png?raw=true "1")
