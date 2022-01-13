ρ ⋅ exp (-α ⋅(x - x_grid_ij)² + (y - y_grid_ij)² + (z - z_grid_ij)²)

We build a 2d grid of size nx × nz with coordinates:

x_grid_ij = (-R ⋅ i / (nx - 1) ⋅ 2 ⋅ R)
y_grid_ij = 0
z_grid_ij = (-R ⋅ j / (ny - 1) ⋅ 2 ⋅ R)
